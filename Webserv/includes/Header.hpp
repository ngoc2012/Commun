/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/24 14:35:18 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

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
		int				_err_code;
		Response*			_response;
		std::map<int, std::string>	_status;
		std::string			_str;

		Header();
		Header(const Header&);
		Header		&operator=(const Header& op);
	public:
		Header(int, Response*);
		virtual ~Header();

		std::string			get_str(void) const;
};

#endif
