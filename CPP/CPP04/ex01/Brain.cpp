/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Brain.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/10 14:56:13 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Brain.hpp"

Brain::Brain() { std::cout << "Brain default constructor." << std::endl; }
Brain::Brain(const Brain& src) {
	for (int i = 0; i < MAX_BRAIN; i++)
		ideas[i] = src.ideas[i];
	std::cout << "Brain copy constructor." << std::endl;
}
Brain&	Brain::operator=( Brain const & src ) {
	for (int i = 0; i < MAX_BRAIN; i++)
		ideas[i] = src.ideas[i];
	return (*this);
}
Brain::~Brain() { std::cout << "Brain destructor." << std::endl; }
void	Brain::show(void) const
{
	for (int i = 0; i < MAX_BRAIN; i++)
		std::cout << i << ": " << ideas[i] << ",";
	std::cout << std::endl;
}
void	Brain::setIdea(std::string s, int i) { ideas[i] = s; }
