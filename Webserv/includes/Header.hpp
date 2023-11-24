/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/24 21:30:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctime>	// time

#include <iostream>
#include <iomanip>	 // strftime, gmtime

#ifndef HEADER_HPP
# define HEADER_HPP
 
class	Server;
class	Location;
class	ClientRequest;
class	ConfigurationParser;
class	Response;

class	Header
{
	private:
		int					_err_code;
		Response*				_response;
		std::map<int, std::string>		_status;
		std::map<std::string, std::string>	_types;
		std::string				_str;

		std::string			get_current_time(void);
		std::string			file_last_modified_time(std::string);
		void				init(void);

		Header();
		Header(const Header&);
		Header		&operator=(const Header& op);
	public:
		Header(int, std::string, Response*);
		virtual ~Header();

		std::string			get_str(void) const;
};

#endif
