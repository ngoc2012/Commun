/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/12/08 05:12:01 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>	// time

#include <iostream>
#include <iomanip>	 // strftime, gmtime

#ifndef HEADER_HPP
# define HEADER_HPP
 
class	Server;
class	Location;
class	Request;
class	Configuration;
class	Response;

class	Header
{
	private:
		int					                _status_code;
		Response*				            _response;
		std::map<int, std::string>		    _status;
		std::map<std::string, std::string>	_types;
		std::string				            _allow;
		std::string				            _extension;

		std::string			get_current_time(void);
		std::string			file_last_modified_time(std::string);
		void				init(void);

		Header();
		Header(const Header&);
		Header		&operator=(const Header& op);
	public:
		Header(int, std::string, Response*);
		virtual ~Header();

		std::string			generate(void);

        void				set_status_code(int);
		void				set_allow(std::string);
};

#endif
