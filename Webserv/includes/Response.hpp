/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/22 11:48:33 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
 
# define RESPONSE_BUFFER 1024

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

		std::string	    _header;
		int		        _status_code;
		size_t		    _content_length;

        bool            _write_queue;
        int             _fd_out;
		bool		    _end_fd_out;

        void	        write_header(void);
        void	        get_file_size(void);

		void		    get_fd_out(void);
        void	        write_body(void);

		int 		    end_connection(void);

		Response(const Response&);
		Response	&operator=(const Response& op);
	public:
		Response();
		virtual ~Response();

		int 		    write(void);

        bool		    get_end_fd_out(void) const;
		size_t		    get_content_length(void) const;

		void		    set_socket(int);
		void		    set_host(Host*);
		void		    set_server(Server*);
		void		    set_request(Request*);
        void		    set_status_code(int);
        void            set_write_queue(bool);
};

#endif
