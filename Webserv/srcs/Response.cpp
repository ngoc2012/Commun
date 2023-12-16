/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/16 16:32:44 by ngoc             ###   ########.fr       */
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
	_body_max = _host->get_client_max_body_size() * MEGABYTE;
	_body_buffer = _host->get_client_body_buffer_size() * KILOBYTE;
	//std::cout << "Response Default constructor" << std::endl;
}
Response::Response(const Response& src) { *this = src; }
Response&	Response::operator=( Response const & src )
{
	(void) src;
	return (*this);
}
Response::~Response()
{
	if (_upload_file.is_open())
		_upload_file.close();
	if (_download_file.is_open())
		_download_file.close();
	//std::cout << "Destruction response: " << _socket << std::endl;
}

int     Response::body()
{
}

int     Response::header()
{
    //std::cout << "Build header" << std::endl;
    if (_status_code != 200)
        return (resquest_error());
    request_header();

    Header	header(_status_code, get_file_extension(_full_file_name), this);
    header.set_allow(_location->get_methods_str());
    if (_status_code == 200)
        request_body();
    header.set_status_code(_status_code);
    _header = header.generate();
}

void     Response::request_header()
{
    std::string	url = _request->get_url();

    _location = Location::find_location(url,
            _server->get_locations(),
            _request->get_method(),
    _status_code);

    if (!_location || _status_code != 200)
        return ;

    _full_file_name = _location->get_full_file_name(url,
            _server->get_root());

	struct stat buffer;
	if (_request->get_method() != PUT
            && stat(_full_file_name.c_str(), &buffer) != 0)
		_status_code = 404; // Not found
}

void     Response::request_body()
{
    std::cout << _full_file_name << std::endl;
    switch (_request->get_method())
    {
        case GET:
            flush_request_body();
            get_file_content();
            break;
        case PUT:
            download();
            //std::cout << "flush_request_body" << std::endl;
            //flush_request_body();
            break;
        default:
            _body = "default";
            _content_length = _body.length();
            break;
    }
}

void	Response::send(void)
{
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

void	Response::flush_request_body(void)
{
    std::cout << "Flush body" << std::endl;
    char	request[_body_buffer];
    int     ret;

    while ((ret = recv(_socket, request, body_buffer, 0)) > 0)
        ;
}

void	Response::download(void)
{
    /*
	const char*	types_supported[] = {
		"text/plain",
		"text/html",
		"text/css",
		"text/javascript",
		"image/jpeg",
		"image/png",
		"image/gif",
		"video/mp4",
	};
    for (int i = 0; i < 8; i++)
        if (words[0] == std::string(types[i]))
        {
            c = words[0];
            return (true);
        }
        */
    _download_file.open(_full_file_name.c_str());
    if (!_download_file.is_open()) {
        std::cerr << "Error: Can not open the file " << _full_file_name << std::endl;
        _status_code = 500;	// Internal server error
        return ;
    }
    std::string body_in_header = _request->get_body_in_header();
    _download_file.write(body_in_header.c_str(), body_in_header.size());
    char	request[_body_buffer];
    std::memset(request, 0, sizeof(request));
    size_t  size_total = 0;
    int     ret = 1;
    while ((ret = recv(_socket, request, body_buffer, 0)) > 0)
    {
        size_total += ret;
        _download_file.write(request, ret);
        std::memset(request, 0, sizeof(request));
    }
    _download_file.close();
    std::cout << "size_total = " << size_total << std::endl;
}

int	    Response::resquest_error(void)
{
    flush_request_body();
    Header	header(_status_code, std::string(""), this);
    header.set_allow(_location->get_methods_str());
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

std::string	Response::get_file_extension(std::string& file_path)
{
	size_t dot_position = file_path.find_last_of('.');
	if (dot_position != std::string::npos && dot_position < file_path.size() - 1)
		return (file_path.substr(dot_position + 1));
	return ("");
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
