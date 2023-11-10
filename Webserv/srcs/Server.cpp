/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/10 19:13:11 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(const Server& src) { *this = src; }

Server::Server(std::vector<Configuration>* c) {
	_max_sk = -1;
	_confs = c;
}

Server&	Server::operator=( Server const & src )
{
	_confs = src.get_confs();
	return (*this);
}

Server::~Server() {}

std::vector<Configuration>	*Server::get_confs(void) const {return (_confs);}

void	Server::start(void)
{
	FD_ZERO(&_master_set);
	for (std::vector<Configuration>::iterator it = _confs.begin() ; it != _confs.end(); ++it)
	{
		get_listen_sk(it);
		bind_addr(it);
		_max_sk = _listen_sk;
		FD_SET(_listen_sk, &_master_set);
	}
	//end_server = false;
	do
	{
		memcpy(&_working_set, &_master_set, sizeof(_master_set));
		if (select_available_sk() == false)
			break;
		for (int i = 0; i <= _max_sk && _sk_ready > 0; ++i)
			if (FD_ISSET(i, &_working_set))
				connect_sk(i);
	} while (true);
	//} while (end_server == false);
	end_server();
}

inline void	Server::connect_sk(int i)
{
	_sk_ready--;
	if (i == _listen_sk)
		accept_client_sk();
	else
		connect_client_sk(i);
}

inline void	Server::connect_client_sk(int i)
{
	std::cout << "Socket " << i << " is readable." << std::endl;
	get_client_request(i);
	std::cout << "Client send: \n"
		<< "=============================================\n"
		<< _request.get_http_request();
	std::cout 
		<< "============================================="
		<< std::endl;
	server_response(i);
	close_connection(i);
}

inline void	Server::end_server(void)
{
	for (int i = 0; i <= _max_sk; ++i)
		if (FD_ISSET(i, &_master_set))
			close(i);
	std::cout << "End server" << std::endl;
}

void		close_all_listen_sk(std::vector<Configuration> &confs)
{
	for (std::vector<Configuration>::iterator it = confs.begin() ; it != confs.end(); ++it)
		if (it._listen_sk > 0)
			close(it._listen_sk);
}

void	Server::get_listen_sk(Configuration &c)
{
	c.set_listen_sk(socket(AF_INET, SOCK_STREAM, 0));
	if (c.get_listen_sk() < 0)
	{
		perror("listen socket: socket() failed");
		exit(-1);
	}
	int    on = 1;
	if (setsockopt(c.get_listen_sk(), SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on)) < 0)
	{
		perror("reusable socket: setsockopt() failed");
		close_all_listen_sk(_confs);
		exit(-1);
	}
	fcntl(c.get_listen_sk(), F_SETFL, O_NONBLOCK);	// ioctl not allowed
}

void	Server::bind_addr(Configuration &c)
{
	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(conf.get_port);
	addr.sin_addr.s_addr = inet_addr(conf.get_ip_address);
	std::cout << "Listening at " << conf.get_ip_address << ":" << conf.get_port << std::endl;
	if (bind(c.get_listen_sk(), (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind() failed");
		close_all_listen_sk(_confs);
		exit(-1);
	}
	if (listen(c.get_listen_sk(), _max_clients) < 0)
	{
		perror("listen() failed");
		close_all_listen_sk(_confs);
		exit(-1);
	}
}

//Accept all the new connections, create a new socket and add to the master set
inline void	Server::accept_client_sk(void)
{
	std::cout << "Listening socket is readable" << std::endl;
	int	new_sk;
	do
	{
		new_sk = accept(_listen_sk, NULL, NULL);
		if (new_sk < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("accept() failed");
				//end_server = true;
			}
			break;
		}
		fcntl(new_sk, F_SETFL, O_NONBLOCK);
		std::cout << "  New incoming connection - " << new_sk << std::endl;
		FD_SET(new_sk, &_master_set);
		if (new_sk > _max_sk)
			_max_sk = new_sk;
	} while (new_sk != -1);
}

inline bool	Server::select_available_sk(void)
{
	std::cout << "Waiting on select() ..." << std::endl;
	_sk_ready = select(_max_sk + 1, &_working_set, NULL, NULL, NULL);// No timeout
	if (_sk_ready < 0)
	{
		perror("working set select() failed");
		return (false);
	}
	return (true);
}

inline void	Server::server_response(int i)
{
	//Send back data
	const char* http_response =
		"HTTP/1.1 200 OK\r\n"
		"Content-Type: text/html\r\n"
		"Connection: close\r\n"  // Close the connection after this response
		"\r\n"  // End of headers
		"<link rel=\"icon\" href=\"data:,\">"
		"<html><body><h1>Hello, client!</h1></body></html>";
	if (send(i, http_response, strlen(http_response), 0) < 0)
	{
		perror("  send() failed");
		//close_conn = 1;
		//break;
	}
	std::cout << "Data sent" << std::endl;
}

inline void	Server::get_client_request(int i)
{
	std::cout << "Receive data from client" << std::endl;
	_request.clean();
	char		response[BUFFER + 1];
	std::string	s = "";
	int		ret = 1;
	while (ret && ret > 0)
	{
		ret = recv(i, response, BUFFER, 0);
		if (ret < 0)
		{
			if (errno != EWOULDBLOCK)
				perror("  recv() failed");
			return ;
		}
		else if (ret == 0)
		{
			std::cout << "Connection closed" << std::endl;
			return ;
		}
		else
		{
			response[ret] = 0;
			s += std::string(response);
			_request.set_http_request(s);
		}
	}
}

inline void	Server::close_connection(int i)
{
	close(i);
	FD_CLR(i, &_master_set);
	if (i == _max_sk)
		while (!FD_ISSET(_max_sk, &_master_set))
			_max_sk -= 1;
}
