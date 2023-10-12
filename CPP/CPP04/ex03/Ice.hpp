/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ice.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/12 09:44:12 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICE_HPP
# define ICE_HPP

#include <iostream>

class Ice
{
	protected:
		Ice();
		Ice(const Ice&);
		std::string	type;
	public:
		Ice(std::string const & type);
		virtual ~Ice();

		std::string const & getType() const; //Returns the materia type
		virtual Ice* clone() const = 0;
		virtual void use(ICharacter& target);
};

#endif
