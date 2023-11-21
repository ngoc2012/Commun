/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 08:57:43 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#ifndef LOCATION_HPP
# define LOCATION_HPP

class	Location
{
	private:
		std::vector<e_method>		_methods;
		std::string			_alias;

		Location(const Location&);
		Location			&operator=(const Location& op);
	public:
		Location();
		virtual ~Location();

		std::vector<e_method>		get_methods(void) const;
		void				insert_methods(e_method);
};

#endif
