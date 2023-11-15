/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Host.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/15 17:44:48 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"

Host::Host(const Host& src) { *this = src; }

Host::Host(std::vector<Server*> &c) {
	_max_sk = -1;
	_servers = c;
	_end_host = false;
}

Host&	Host::operator=( Host const & src )
{
	//_servers = src.get_servers();
	(void) src;
	return (*this);
}

Host::~Host() {}

std::vector<Server>	*Host::get_servers(void) const {return (_servers);}

void	Host::set_end_host(bool e) {_end_host = e;}

void	Host::start(void)
{
	FD_ZERO(&_master_set);
	for (std::vector<Server>::iterator it = _servers->begin() ; it != _servers->end(); ++it)
	{
		get_listen_sk(*it);
		bind_addr(*it);
		if ((*it).get_listen_sk() > _max_sk)
			_max_sk = (*it).get_listen_sk();
		FD_SET((*it).get_listen_sk(), &_master_set);
	}
	//end_host = false;
	do
	{
		memcpy(&_working_set, &_master_set, sizeof(_master_set));
		if (select_available_sk() == false)
			break;
		for (int i = 0; i <= _max_sk && _sk_ready > 0; ++i)
			if (FD_ISSET(i, &_working_set))
				connect_sk(i);
	} while (true);
	//} while (end_host == false);
	//end();
}

void	Host::connect_sk(int i)
{
	_sk_ready--;
	// check if the socket is a listen socket
	for (std::vector<Server>::iterator it = _servers->begin() ; it != _servers->end(); ++it)
		if (i == (*it).get_listen_sk())
		{
			accept_client_sk((*it).get_listen_sk());
			return ;
		}
	// connect socket
	connect_client_sk(i);
}

inline void	Host::connect_client_sk(int i)
{
	std::cout << "Socket " << i << " is readable." << std::endl;
	get_client_request(i);
	server_response(i);
	close_connection(i);
}

void	Host::end(void)
{
	for (int i = 0; i <= _max_sk; ++i)
		if (FD_ISSET(i, &_master_set))
			close(i);
	for (std::vector<Server*>::iterator it = servers.begin() ; it != servers.end(); ++it)
		delete (*it);
	std::cout << "End server" << std::endl;
}

void		close_all_listen_sk(std::vector<Server> &confs)
{
	for (std::vector<Server>::iterator it = confs.begin() ; it != confs.end(); ++it)
		if ((*it).get_listen_sk() > 0)
			close((*it).get_listen_sk());
}

void	Host::get_listen_sk(Server &c)
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
		close_all_listen_sk(*_servers);
		exit(-1);
	}
	fcntl(c.get_listen_sk(), F_SETFL, O_NONBLOCK);	// ioctl not allowed
}

void	Host::bind_addr(Server &c)
{
	struct sockaddr_in	addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(c.get_port());
	addr.sin_addr.s_addr = inet_addr(c.get_ip_address());
	std::cout << "Listening at " << c.get_ip_address() << ":" << c.get_port() << std::endl;
	if (bind(c.get_listen_sk(), (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("bind() failed");
		close_all_listen_sk(*_servers);
		exit(-1);
	}
	if (listen(c.get_listen_sk(), c.get_max_clients()) < 0)
	{
		perror("listen() failed");
		close_all_listen_sk(*_servers);
		exit(-1);
	}
}

//Accept all the new connections, create a new socket and add to the master set
inline void	Host::accept_client_sk(int listen_sk)
{
	std::cout << "Listening socket is readable" << std::endl;
	int	new_sk;
	do
	{
		new_sk = accept(listen_sk, NULL, NULL);
		if (new_sk < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				perror("accept() failed");
				_end_host = true;
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

inline bool	Host::select_available_sk(void)
{
	std::cout << "Waiting on select() ..." << std::endl;
	_sk_ready = select(_max_sk + 1, &_working_set, NULL, NULL, NULL);// No timeout
	if (_sk_ready < 0)
	{
		if (_end_host == false)
			perror("working set select() failed");
		return (false);
	}
	return (true);
}

inline void	Host::server_response(int i)
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

inline void	Host::get_client_request(int i)
{
	std::cout << "Receive data from client" << std::endl;
	ClientRequest			_request;
	_request.clean();
	char		response[BUFFER + 1];
	std::string	s = "";
	int		ret = 1;
	size_t		pos, pos0;
	while (ret && ret > 0)
	{
		ret = recv(i, response, BUFFER, 0);
		if (ret < 0)
		{
			if (errno != EWOULDBLOCK)
				perror("  recv() failed");
			std::cout << "Client send: \n"
				<< "=============================================\n"
				<< _request.get_http_request();
			std::cout 
				<< "============================================="
				<< std::endl;
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
			if (_request.get_method() == "")
			{
				pos = s.find("Content-Type:");
				if ( pos != std::string::npos)
				{
					pos0 = s.find(";", pos);
					if ( pos0 != std::string::npos)
					{
						_request.set_method(s.substr(pos + 14, pos0 - pos - 14));
						std::cout << "|" << _request.get_method() << "|" << std::endl;
					}
				}
			}
			if (_request.get_method() == "multipart/form-data")
			{
				// The combination \r\n is often used to indicate the end of a line of text in text files
				// Find the start of the file content
				const std::string boundary = "boundary=";
				size_t boundaryPos = s.find(boundary);
				//if (boundaryPos == std::string::npos) {
				//	std::cerr << "Boundary not found in Content-Type header." << std::endl;
				//	return;
				//}

				size_t startPos = s.find("\r\n\r\n", boundaryPos) + 4;
				std::string	s0 = s.substr(startPos);
				pos = s0.find("Content-Type:");
				if ( pos != std::string::npos)
				{
					startPos = s0.find("\r\n\r\n", pos) + 4;
					s0 = s0.substr(startPos);
				}
				//std::cout << s0 << std::endl;
				/*
				size_t endPos = s.find("--" + line.substr(boundaryPos + boundary.length()));

				// Extract the file content
				std::string fileData = fileContent.substr(startPos, endPos - startPos);

				// Save the file on the server
				saveFile("uploaded_file.txt", fileData);
				*/
			}
			_request.set_http_request(s);
		}
	}
}

inline void	Host::close_connection(int i)
{
	close(i);
	FD_CLR(i, &_master_set);
	// If i is max_sk -> find another max_sk
	if (i == _max_sk)
		while (!FD_ISSET(_max_sk, &_master_set))
			_max_sk -= 1;
}
