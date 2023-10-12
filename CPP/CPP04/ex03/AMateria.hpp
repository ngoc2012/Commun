/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AMateria.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/12 09:03:43 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>


class AMateria
{
protected:
[...]
public:
AMateria(std::string const & type);
[...]
std::string const & getType() const; //Returns the materia type
virtual AMateria* clone() const = 0;
virtual void use(ICharacter& target);
};
/*
class Animal
{
	protected:
		Animal();
		Animal(const Animal&);
		std::string	type;
	public:
		Animal &operator=(const Animal& op);
		virtual ~Animal();

		virtual void    makeSound( void ) const;
		std::string     getType( void ) const;
		virtual void    showBrain( void ) const;
		virtual void	setBrain(std::string, int);
};
*/

#endif
