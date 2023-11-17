/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/17 15:43:09 by ngoc             ###   ########.fr       */
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
ClientRequest::ClientRequest(int sk, Host* h) : _socket(sk), _host(h)
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
	_http_request = "";
	_method0 = "";
	_method1 = "";
	_url = "";
}

void	ClientRequest::read_client_request(void)
{
	std::cout << "Receive data from client" << std::endl;
	clean();
	char		response[BUFFER + 1];
	int		ret = 1;
	while (ret && ret > 0)
	{
		ret = recv(_socket, response, BUFFER, 0);
		if (ret < 0)
		{
			if (errno != EWOULDBLOCK)
				perror("  recv() failed");
			else
			{
				std::cout << "Client send: \n"
					<< "=============================================\n"
					<< _http_request
					<< "=============================================\n";
				_host->get_sk_server()[_socket]->response(_socket);
			}
			break ;
		}
		else if (ret == 0)
		{
			std::cout << "Connection closed" << std::endl;
			break ;
		}
		else
		{
			response[ret] = 0;
			if (_http_request == "")
			{
				_http_request += std::string(response);
				read_header(_http_request);
				//if (_method0 == "")
				//{
				//	std::cerr << "Error: no Content-Type" << std::endl;
				//	_host->get_sk_server()[_socket]->response(_socket);
				//	break ;
				//}
			}
			else
				_http_request += std::string(response);
		}
	}
	_host->close_client_sk(_socket);
}

void	ClientRequest::cat_http_request(std::string s) {_http_request += s;}

void	ClientRequest::read_header(std::string& header)
{
	size_t		pos, pos0;

	std::vector<std::string>	lines = split_string(header, "\n");
	std::vector<std::string>	first_line = split_string(lines[0], "\n");

	//std::cout << header << std::endl;
	pos0 = header.length() - 1;
	pos = header.find("Content-Type:");
	if (pos != std::string::npos)
	{
		pos0 = header.find(";", pos);
		if (pos0 != std::string::npos)
			_method0 = header.substr(pos + 14, pos0 - pos - 14);
	}
	pos = header.find("Content-Type:", pos0);
	if (pos != std::string::npos)
	{
		pos0 = header.find(";", pos);
		if (pos0 != std::string::npos)
			_method1 = header.substr(pos + 14, pos0 - pos - 14);
	}
}

//void	ClientRequest::set_method(std::string m) {_method = m;}
void	ClientRequest::set_http_request(std::string s) {_http_request = s;}

//std::string	ClientRequest::get_method(void) const {return (_method);}
std::string	ClientRequest::get_http_request(void) const {return (_http_request);}

/*
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
	////std::cout << s0 << std::endl;
	//size_t endPos = s.find("--" + line.substr(boundaryPos + boundary.length()));
	//// Extract the file content
	//std::string fileData = fileContent.substr(startPos, endPos - startPos);
	//// Save the file on the server
	//saveFile("uploaded_file.txt", fileData);
}
_request.set_http_request(s);
*/
