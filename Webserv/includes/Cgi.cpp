/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/06 15:01:18 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
 
class	Server;
class	Location;
class	Request;
class	Configuration;

class	Response
{
	private:
		int		    _socket;
		Host*		_host;
		Server*		_server;
		Request*	_request;
		Location*	_location;	
		size_t		_content_length;
		int		    _status_code;
		std::string	_full_file_name;
		std::string	_header;
		std::string	_body;
		bool		_end;
		std::ifstream	_file;

		bool		find_method(e_method, Location*);
		bool		compare_url(std::string, std::string);
		void		find_location(std::string);
		std::string	get_methods_str(void);
		std::string	get_file_extension(std::string&);
		void		get_full_file_name(std::string);
		size_t		get_file_size(std::string &file_name);
		void		get(void);
        void	    resquest_error(void);
        void	    get_content(void);
        void	    execute_cgi(void);

		Response(const Response&);
		Response	&operator=(const Response& op);
	public:
		//Response(int, Host*, Server*, Request*);
		Response();
		virtual ~Response();

		void		send(void);
		size_t		get_content_length(void) const;
		Location*	get_location(void) const;	

		void		set_socket(int);
		void		set_host(Host*);
		void		set_server(Server*);
		void		set_request(Request*);
		void		set_status_code(int);
};

#endif
