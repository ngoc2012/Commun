/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/13 16:19:32 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHARACTER_HPP
# define CHARACTER_HPP
# define SLOTS 4

#include <iostream>
#include "ICharacter.hpp"

class Character: public ICharacter
{
	private:
		std::string	name;
		AMateria	*slots[SLOTS];
		Character();
		Character(const Character&);
	public:
		Character &operator=(const Character& op);
		Character(std::string const & type);
		virtual ~Character();
};

#endif
