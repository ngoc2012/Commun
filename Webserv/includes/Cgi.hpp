/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cgi.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/27 17:14:02 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef CGI_HPP
# define CGI_HPP

class	Request;

class	Cgi
{
	private:
        std::string     _pass;
        std::string     _file;
		Request*        _request;
        char**          _envs;
        char*           _argv[3];

        bool            envs();

		Cgi(const Cgi&);
		Cgi	&operator=(const Cgi& op);
	public:
		Cgi();
		//Cgi(Request*);
		virtual ~Cgi();

        void            execute();
        void	        set_request(Request*);
};

#endif
