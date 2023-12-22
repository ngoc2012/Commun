/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/22 09:41:59 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#include "Response.hpp"

#ifndef CLIENTREQUEST_HPP
# define CLIENTREQUEST_HPP
 
# define REQUEST_BUFFER 1024

class	Host;

class	Request
{
	private:
		int		        _socket;
		Host*		    _host;
		Server*		    _server;
		Response	    _response;
		Location*	    _location;	

		int		        _fd_in;
		int		        _status_code;
		size_t		    _body_size;
		size_t		    _body_position;
        char		    _raw[REQUEST_BUFFER + 1];
		std::string	    _url;
		std::string	    _header;
		std::string	    _content_type;
		e_method	    _method;
        bool            _read_queue;
        bool            _end_fd_in;
		std::string	    _full_file_name;

		void		read_header(void);
		void		get_fd_out(void);
		bool		parser_header(void);
		bool		read_method(std::string&);
		bool		read_content_type(std::string&, std::string&);
		bool		split_header_body(std::string&);
		int         end_read(void);
		void		read_header(void);

		Request();
		Request(const Request&);
		Request &operator=(const Request& op);
	public:
		Request(int, Host*, Server*);
		virtual ~Request();

		int         read(void);

        bool        get_end_fd_in(void) const;
		e_method	get_method(void) const;
		std::string	get_url(void) const;
		Response*	get_response(void);
		int		    get_status_code(void) const;
        std::string	get_body_in_header(void) const;
        std::string	get_content_type(void) const;
        size_t		get_body_size(void) const;
        std::string	get_header(void) const;
        std::string	get_full_file_name(void) const;
};

#endif
