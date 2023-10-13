/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/13 18:18:23 by ngoc             ###   ########.fr       */
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
	public:
		Character();
		Character(const Character&);
		Character &operator=(const Character& op);
		Character(std::string const & type);
		virtual ~Character();

		destroy( void );
};

#endif
