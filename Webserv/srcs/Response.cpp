/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/07 22:00:08 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Host.hpp"
#include "Server.hpp"
#include "Location.hpp"
#include "Request.hpp"
#include "Header.hpp"

#include "Response.hpp"

Response::Response()
{
	_header = "";
	_full_file_name = "";
	_status_code = 200;
	_location = 0;
	_end = false;
	std::cout << "Response Default constructor" << std::endl;
}
Response::Response(const Response& src) { *this = src; }
Response&	Response::operator=( Response const & src )
{
	(void) src;
	return (*this);
}
/*
Response::Response(int sk, Host* h, Server* s, Request* r) :
_socket(sk),
_host(h),
_server(s),
_request(r)
{
	_header = "";
	_full_file_name = "";
	_status_code = 200;
	_location = 0;
	_end = false;
	std::cout << "Response Constructor sk: " << sk << std::endl;
}
*/
Response::~Response()
{
	if (_upload_file.is_open())
		_upload_file.close();
	if (_download_file.is_open())
		_download_file.close();
    /*
	{
		std::cout << "File in response close" << std::endl;
		if (_file.fail())
			std::cerr << "Error closing file" << std::endl;
		else
			std::cout << "File closed successfully" << std::endl;
	}
    */
	std::cout << "Destruction response: " << _socket << std::endl;
}

int     Response::build_header(int &sc)
{
    std::cout << "Build header" << std::endl;
    _status_code = sc;
    if (_status_code != 200)
        return (resquest_error());
    std::string	url = _request->get_url();
    find_location(url);
    if (_status_code != 200)
        return (resquest_error());
    get_full_file_name(url);
    Header	header(_status_code, get_file_extension(_full_file_name), this);
    header.set_allow(get_methods_str());
    if (_status_code == 200)
    {
        std::cout << _full_file_name << std::endl;
        switch (_request->get_method())
        {
            case GET:
                get_file_content();
                break;
            case PUT:
                download();
                break;
            default:
                _body = "default";
                _content_length = _body.length();
                break;
        }
    }
    _header = header.generate();
    return (_status_code);
}

void	Response::send(void)
{
    std::cout << _status_code << std::endl;
	if(_header != "")
    {
        std::cout << "Header:\n" << _header << std::endl;
        if (::send(_socket, _header.c_str(), _header.length(), 0) < 0)
        {
            _end = true;
            perror("send() failed");
        }
        _header = "";
    }
    else if ((_request->get_method() == GET || _request->get_method() == POST)
        && _location->get_cgi_pass() != "")
        execute_cgi();
    else if (_request->get_method() == GET)
		get();
    if (_end)
        _host->close_client_sk(_socket);
    //_host->delete_response(_socket);
    //std::cout << "Response sent" << std::endl;
}

void	Response::download(void)
{
    _download_file.open(_full_file_name.c_str());
    if (!_download_file.is_open()) {
        std::cerr << "Error: Can not open the file " << _full_file_name << std::endl;
        _status_code = 500;	// Internal server error
        _end = true;
        return ;
    }
    std::string body_in_header = _request->get_body_in_header();
    _download_file.write(body_in_header.c_str(), body_in_header.size());
    size_t  body_buffer = _request->get_body_buffer();
    char	request[body_buffer];
    std::memset(request, 0, sizeof(request));
    int     ret = 1;
    while ((ret = recv(_socket, request, body_buffer, 0)) > 0)
    {
        _download_file.write(request, ret);
        std::memset(request, 0, sizeof(request));
    }
    _download_file.close();
    _end = true;
}

int	    Response::resquest_error(void)
{
    Header	header(_status_code, std::string(""), this);
    header.set_allow(get_methods_str());
    _end = true;
    _content_length = 0;
    _header = header.generate();
    if (::send(_socket, _header.c_str(), _header.length(), 0) < 0)
        perror("send() failed");
    return (_status_code);
}

void	Response::get_file_content(void)
{
    _content_length = get_file_size(_full_file_name);
    //_content_length = 2 * _host->get_client_body_buffer_size() * KILOBYTE;
    //std::cout << "File open" << std::endl;
    _upload_file.open(_full_file_name.c_str(), std::ios::binary);
    if (!_upload_file.is_open())
    {
        std::cerr << "Failed to open file: " << _full_file_name << std::endl;
        _status_code = 500;	// Internal server error
        _end = true;
    }
}

void	Response::execute_cgi(void)
{
    std::cout << _location->get_cgi_pass() << std::endl;
    get_file_content();
}

bool	Response::find_method(e_method m, Location* loc)
{
	std::vector<e_method>	methods = loc->get_methods();

	for (std::vector<e_method>::iterator	it = methods.begin();
		it != methods.end(); ++it)
		if (m == *it)
			return (true);
	//std::cout << _request->get_method() << "==" << *it << std::endl;
	return (false);
}

bool	Response::compare_url(std::string url, std::string l_url)
{
	//std::cout << url << "==" << l_url << std::endl;
	// Folder
	if (l_url[l_url.size() - 1] == '/')
	{
		if (url == l_url || url == l_url.substr(0, l_url.size() - 1)
			|| (url.size() > l_url.size() && url.substr(0, l_url.size()) == l_url))
			return (true);
	}
	// File
	else if (url == l_url)
		return (true);
    if (l_url.find('*') != std::string::npos && match_wildcard(url.c_str(), l_url.c_str()))
		return (true);
	return (false);
}

void	Response::find_location(std::string url)
{
	bool	found = false;

	std::vector<Location*>		locations = _server->get_locations();
	for (std::vector<Location*>::iterator it = locations.begin();
		it != locations.end(); ++it)
	{
		if (compare_url(url, (*it)->get_url()))
		{
			_location = *it;
			found = true;
			if (find_method(_request->get_method(), *it))
				_status_code = 200;
			else
				_status_code = 405; // Method not allowed
		}
	}
	if (!found)
		_status_code = 404; // Not found
}

std::string	Response::get_methods_str(void)
{
	if (!_location)
		return (std::string(""));
	std::vector<e_method>	methods = _location->get_methods();
	std::string	s = "";
	for(std::vector<e_method>::iterator it = methods.begin(); it != methods.end(); ++it)
	{
		if (it != methods.begin())
			s += ",";
		switch (*it)
		{
			case GET:
				s += "GET";
				break;
			case POST:
				s += "POST";
				break;
			case PUT:
				s += "PUT";
				break;
			case NONE:
				s += "NONE";
				break;
		}
	}
	return (s);
}

std::string	Response::get_file_extension(std::string& file_path)
{
	size_t dot_position = file_path.find_last_of('.');
	if (dot_position != std::string::npos && dot_position < file_path.size() - 1)
		return (file_path.substr(dot_position + 1));
	return ("");
}

void	Response::get_full_file_name(std::string url)
{
	if (_location)
	{
		if (_location->get_alias() == "")
			_full_file_name += _server->get_root();
		else
			_full_file_name += _location->get_alias();
		if (url.size() > _location->get_url().size())
			_full_file_name += url.substr(1, url.size() - 1);
	}
	struct stat	info;
	if (stat(_full_file_name.c_str(), &info) == 0 && S_ISDIR(info.st_mode))
		_full_file_name += "index.html";
	struct stat	buffer;
	if (stat(_full_file_name.c_str(), &buffer) != 0)
		_status_code = 404; // Not found
	//std::cout << _full_file_name << std::endl;
}

size_t		Response::get_file_size(std::string &file_name)
{
	std::ifstream file(file_name.c_str(), std::ios::binary | std::ios::ate);
	if (!file.is_open()) {
		std::cerr << "Failed to open file: " << file_name << std::endl;
		_status_code = 500;	// Internal server error
		return 0;
	}
	return (file.tellg());
}

void	Response::get(void)
{ 
	size_t	chunk_size = _host->get_client_body_buffer_size() * KILOBYTE;

	char	buffer[chunk_size];
	//std::cout << "chunk_size: " << chunk_size << std::endl;
	_upload_file.read(buffer, chunk_size);
	size_t	bytes_read = _upload_file.gcount();
	::send(_socket, buffer, bytes_read, 0);
	if (_upload_file.eof())
	{
		_upload_file.close();
		_end = true;
	}
}

Location*	Response::get_location(void) const {return (_location);}
size_t		Response::get_content_length(void) const {return (_content_length);}
void		Response::set_socket(int s) {_socket = s;}
void		Response::set_host(Host* h) {_host = h;}
void		Response::set_server(Server* s) {_server = s;}
void		Response::set_request(Request* r) {_request = r;}
void		Response::set_status_code(int e) {_status_code = e;}
