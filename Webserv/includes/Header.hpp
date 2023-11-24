/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Header.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/24 13:16:24 by ngoc             ###   ########.fr       */
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
		Header();
		Header(const Header&);
		Header		&operator=(const Header& op);
	public:
		Header(int, Response*);
		virtual ~Header();

		void			send(void);
};

#endif
