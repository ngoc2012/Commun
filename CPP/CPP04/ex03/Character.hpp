/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Character.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/13 18:26:31 by ngoc             ###   ########.fr       */
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

		std::string const & getName() const = 0;
		void equip(AMateria* m) = 0;
		void unequip(int idx) = 0;
		void use(int idx, ICharacter& target) = 0;
		void	destroy( void );
};

#endif
