/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cat.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/10 14:49:44 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"

Cat::Cat() {
	brain = new Brain();
	type = "Cat";
	std::cout << type << " default constructor." << std::endl;
}
Cat::Cat(const Cat& src) : Animal(src) {
	brain = new Brain();
	*this = src;
	std::cout << type << " copy constructor." << std::endl;
}
Cat&	Cat::operator=( Cat const & src )
{
	brain = src.brain;
	type = src.type;
	return (*this);
}
Cat::~Cat() {
	delete(brain);
	std::cout << type << " destructor." << std::endl;
}
void    Cat::makeSound( void ) const
{
	std::cout << "Meomeo..." << std::endl;
}
void    Cat::showBrain( void ) const { brain->show(); }
void	Cat::setBrain(std::string s, int i)
{
	if (i < 0 || i >= MAX_BRAIN)
	{
		std::cerr << "Error index!!!";
		return ;
	}
	brain.ideas[i] = s;
}
