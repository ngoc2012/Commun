/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/22 07:35:29 by ngoc             ###   ########.fr       */
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

		size_t		    _content_length;
		int		        _status_code;
		std::string	    _header;
		std::string	    _body;
		std::string	    _http;
		size_t		    _body_buffer;
		size_t		    _body_max;
        bool            _write_queue;
		bool		    _end_fd_out;
        int             _fd_out;

		std::string	    get_file_extension(std::string&);
		//size_t		    get_file_size(std::string &file_name);
		void		    get(void);
        void	        get_file_content(void);
		void		    get_fd_in(void);
		int 		    end_connection(void);
        void	        write_header(void);
        void	        write_body(void);
        void	        get_body_size(void);

		Response(const Response&);
		Response	&operator=(const Response& op);
	public:
		//Response(int, Host*, Server*, Request*);
		Response();
		virtual ~Response();

		void		write(void);

        bool		get_end_fd_out(void) const;
		size_t		get_content_length(void) const;

		void		set_socket(int);
		void		set_host(Host*);
		void		set_server(Server*);
		void		set_request(Request*);
        void        set_write_queue(bool);
};

#endif
