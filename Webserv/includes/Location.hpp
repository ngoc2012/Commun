/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 15:40:40 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#include "webserv.hpp"

#ifndef LOCATION_HPP
# define LOCATION_HPP

class	Location
{
	private:
		std::string			_url;
		std::vector<e_method>		_methods;
		std::string			_alias;

		Location();
		Location(const Location&);
		Location			&operator=(const Location& op);
	public:
		Location(std::string);
		virtual ~Location();

		std::vector<e_method>		get_methods(void) const;
		std::string			get_alias(void) const;
		std::string			get_url(void) const;

		void				insert_methods(e_method);
		void				set_alias(std::string);
		void				set_url(std::string);
};

#endif