/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dog.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/10 18:11:50 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Dog.hpp"

Dog::Dog() {
	brain = new Brain();
	type = "Dog";
	std::cout << type << " default constructor." << std::endl;
}
Dog::Dog(const Dog& src) : Animal(src) {
	brain = new Brain();
	*brain = *src.brain;
	*this = src;
	std::cout << type << " copy constructor." << std::endl;
}
Dog&	Dog::operator=( Dog const & src )
{
	*brain = *src.brain;
	type = src.type;
	return (*this);
}
Dog::~Dog()
{
	if (brain)
		delete(brain);
	std::cout << type << " destructor." << std::endl;
}
void    Dog::makeSound( void ) const
{
	std::cout << "Gaugau..." << std::endl;
}
void    Dog::showBrain( void ) const { brain->show(); }
void	Dog::setBrain(std::string s, int i)
{
	if (i < 0 || i >= MAX_BRAIN)
	{
		std::cerr << "Error: no " << i << " index!!!\n";
		return ;
	}
	brain->setIdea(s, i);
}
