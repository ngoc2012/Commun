/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/24 14:19:59 by ngoc             ###   ########.fr       */
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

		Header();
		Header(const Header&);
		Header		&operator=(const Header& op);
	public:
		Header(int, Response*);
		virtual ~Header();

		void			send(void);
};

#endif
