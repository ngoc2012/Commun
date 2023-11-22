/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClientRequest.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/22 08:18:00 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "ClientRequest.hpp"

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
	_start_pos_body = 0;
	_http_request = "";
	_content_type0 = "";
	_content_type1 = "";
	_method = NONE;
	_url = "";
}

void	ClientRequest::read_client_request(void)
{
	std::cout << "Receive data from client" << std::endl;
	clean();
	char		response[BUFFER + 1];
	int		ret = 1;

	int	ret = recv(_socket, response, BUFFER, 0);
	if (ret <= 0)
		perror(" recv() failed");
	do
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
				if (!read_header(_http_request))
				{
					_host->get_sk_server()[_socket]->response(_socket);
					break ;
				}
				std::cout << "=============== Body =============\n"
					<< &_http_request[_start_pos_body]
					<< "===================================" << std::endl;
			}
			else
				_http_request += std::string(response);
		}
	}
	while (ret && ret > 0)
	_host->close_client_sk(_socket);
}

void	ClientRequest::cat_http_request(std::string s) {_http_request += s;}

bool	ClientRequest::read_header(std::string& header)
{

	std::vector<std::string>	lines = split_string(header, "\n");
	std::vector<std::string>	first_line = split_string(lines[0], " 	");

	if (!read_method(first_line[0]))
		return (false);
	read_content_type(header, _content_type0);
	if (_content_type0 != "")
	{
		std::string	s = header.substr(header.find("Content-Type:") + 14);
		read_content_type(s, _content_type1);
	}
	if (!find_start_pos_body(header))
		return (false);
	return (true);
}

bool	ClientRequest::read_method(std::string& s)
{
	std::cout << s << std::endl;
	if (s == "GET")
		_method = GET;
	else if (s == "POST")
		_method = POST;
	else
	{
		_error = 400;
		std::cerr << "Error: Method unknown : " << s << std::endl;
		return (false);
	}
	return (true);
}

bool	ClientRequest::find_start_pos_body(std::string& s)
{
	size_t	pos0 = s.find("Content-Type:");
	if (pos0 != std::string::npos)
	{
		size_t	pos1 = s.find("Content-Type:", pos0 + 14);
		if (pos1 != std::string::npos)
		{
			pos0 = s.find("\r\n\r\n", pos1);
			if (pos0 != std::string::npos)
				_start_pos_body = pos0 + 4;
			else
				return (false);
		}
		else
		{
			pos1 = s.find("\r\n\r\n", pos0);
			if (pos1 != std::string::npos)
				_start_pos_body = pos1 + 4;
			else
				return (false);
		}
		return (true);
	}
	pos0 = s.find("\r\n\r\n");
	if (pos0 != std::string::npos)
		_start_pos_body = pos0 + 4;
	return (true);
}

bool	ClientRequest::read_content_type(std::string& s, std::string& c)
{
	const char*	types[] = {
		"text/plain",
		"text/html",
		"text/css",
		"text/javascript",
		"text/xml",
		"application/json",
		"application/xml",
		"application/pdf",
		"application/zip",
		"application/octet-stream",
		"image/jpeg",
		"image/png",
		"image/gif",
		"image/svg+xml",
		"audio/mpeg",
		"video/mp4",
		"multipart/form-data",
		"application/x-www-form-urlencoded"
	};
	size_t	pos = s.find("Content-Type:");
	std::vector<std::string>	words;
	if (pos != std::string::npos)
	{
		words = split_string(s.substr(pos + 14, 50), ";\n");
		//std::cout << "|" << words[0] << "|" << std::endl << std::flush;
		for (int i = 0; i < 18; i++)
			if (words[0] == std::string(types[i]))
				c = words[0];
		return (false);
	}
	return (true);
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
