/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/19 06:58:59 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
 
# define MEGABYTE 1048576
# define KILOBYTE 1024

class	Server;
class	Location;
class	Request;
class	Configuration;

class	Response
{
	private:
		int		        _socket;
		Host*		    _host;
		Server*		    _server;
		Request*	    _request;
		Location*	    _location;	

		size_t		    _content_length;
		int		        _status_code;
		std::string	    _full_file_name;
		std::string	    _header;
		std::string	    _body;
		std::string	    _http;
		bool		    _end;
		std::ifstream	_upload_file;
		std::ofstream	_download_file;
		size_t		    _body_buffer;
		size_t		    _body_max;
        bool            _write_queue;
		bool		    _end_fd_out;

		std::string	get_file_extension(std::string&);
		size_t		get_file_size(std::string &file_name);
		void		get(void);
        void	    get_file_content(void);
        void	    execute_cgi(void);
        void        download(void);
        void        flush_request_body(void);
        void        request_header(void);
        void        request_body(void);

		Response(const Response&);
		Response	&operator=(const Response& op);
	public:
		//Response(int, Host*, Server*, Request*);
		Response();
		virtual ~Response();

		void		write(void);
        void	    header(void);
		void		body(void);
        int	        resquest_error(void);

		size_t		get_content_length(void) const;

		void		set_socket(int);
		void		set_host(Host*);
		void		set_server(Server*);
		void		set_request(Request*);
		void		set_status_code(int);
};

#endif
