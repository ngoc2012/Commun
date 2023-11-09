/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/09 22:17:57 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
{
	char	ip[] = "127.0.0.1";
	_port = 4242;
	_ip_address = ip;
	_max_clients = 128;
}

Server::Server(const Server& src) { *this = src; }

Server&	Server::operator=( Server const & src )
{
	(void) src;
	return (*this);
}

Server::~Server() {}

void	Server::start(void)
{
	get_listen_sk();
	bind_addr();

	FD_ZERO(&_master_set);
	_max_sk = _listen_sk;
	FD_SET(_listen_sk, &_master_set);

	//end_server = false;
	do
	{
		memcpy(&_working_set, &_master_set, sizeof(_master_set));
		if (select_available_sk() == false)
			break;
		for (int i = 0; i <= _max_sk && _sk_ready > 0; ++i)
			if (FD_ISSET(i, &_working_set))
			{
				_sk_ready--;
				if (i == _listen_sk)
					accept_client_sk();
				else
					connect_client_sk(i);
			}
	} while (true);
	//} while (end_server == false);
}

inline void	Server::end_server(void)
{
	for (int i = 0; i <= _max_sk; ++i)
	{
		if (FD_ISSET(i, &_master_set))
			close(i);
	}
	std::cout << "End server" << std::endl;
}

inline void	Server::get_listen_sk(void)
{
	_listen_sk = socket(AF_INET, SOCK_STREAM, 0);
	if (_listen_sk < 0)
	{
		perror("listen socket: socket() failed");
		exit(-1);
	}
	int    on = 1;
	if (setsockopt(_listen_sk, SOL_SOCKET,  SO_REUSEADDR,
                   (char *)&on, sizeof(on)) < 0)
	{
		perror("reusable socket: setsockopt() failed");
		close(_listen_sk);
		exit(-1);
	}
	fcntl(_listen_sk, F_SETFL, O_NONBLOCK);	// ioctl not allowed
}

inline void	Server::bind_addr(void)
{
	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(_port);
	addr.sin_addr.s_addr = inet_addr(_ip_address);
	std::cout << "Listening at " << _ip_address << ":" << _port << std::endl;
	if (bind(_listen_sk, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind() failed");
		close(_listen_sk);
		exit(-1);
	}
	if (listen(_listen_sk, _max_clients) < 0)
	{
		perror("listen() failed");
		close(_listen_sk);
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
