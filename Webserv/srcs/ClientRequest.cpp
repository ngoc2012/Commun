/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/16 19:10:16 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClientRequest.hpp"
#include "Host.hpp"

ClientRequest::ClientRequest()
{
	std::cout << "ClientRequest Default constructor" << std::endl;
	clean();
}
ClientRequest::ClientRequest(const ClientRequest& src) { *this = src; }
ClientRequest&	ClientRequest::operator=( ClientRequest const & src )
{
	(void) src;
	return (*this);
}
ClientRequest::ClientRequest(int sk, Host* h) : _socket = sk, _host = h
{
	std::cout << "ClientRequest Constructor sk: " << sk << std::endl;
}
ClientRequest::~ClientRequest()
{
	std::cout << "Destruction client request" << std::endl;
	if (_socket > 0)
	{
		std::cout << "Close socket: " << _socket << std::endl;
		close(_socket);
	}
}

void	ClientRequest::clean()
{
	_socket = -1;
	_http_request = "";
	_method = "";
	_url = "";
}

void	Host::read_client_request(void)
{
	std::cout << "Receive data from client" << std::endl;
	clean();
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
			if (method == "")
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
			if (method == "multipart/form-data")
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
	_host->servers[_socket]->response();
}

void	ClientRequest::set_method(std::string m) {_method = m;}
void	ClientRequest::set_http_request(std::string s) {_http_request = s;}
void	ClientRequest::cat_http_request(std::string s) {_http_request += s;}

std::string	ClientRequest::get_method(void) const {return (_method);}
std::string	ClientRequest::get_http_request(void) const {return (_http_request);}
