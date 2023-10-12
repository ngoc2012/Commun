/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/12 11:30:09 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP

#include <iostream>
#include "ICharacter.hpp"

class Character: public ICharacter
{
	protected:
		Character();
		Character(const Character&);
		std::string	type;
	public:
		Character &operator=(const Character& op);
		Character(std::string const & type);
		virtual ~Character();

		//std::string const & getType() const; //Returns the materia type
		//virtual Character* clone() const = 0;
		//virtual void use(ICharacter& target);
};

#endif
