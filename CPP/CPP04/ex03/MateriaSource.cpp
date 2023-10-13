/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/13 17:47:12 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < SLOTS; i++) {slots[i] = 0;}
	std::cout << "MateriaSource default constructor." << std::endl;
}
MateriaSource::MateriaSource(const MateriaSource& src) {
	*this = src;
	std::cout << "MateriaSource copy constructor." << std::endl;
}
void	MateriaSource::destroy(void)
{
	for (int i = 0; i < SLOTS; i++)
		if (slots[i])
			delete(slots[i]);
}
MateriaSource&	MateriaSource::operator=( MateriaSource const & src )
{
	destroy();
	for (int i = 0; i < SLOTS; i++)
		slots[i] = new AMateria(src.slots[i]);
	return (*this);
}
MateriaSource::~MateriaSource()
{
	destroy();
 	std::cout << "MateriaSource destructor." << std::endl;
}

void	MateriaSource::learnMateria(AMateria* m)
{
	int	i = 0;
	while (i < SLOTS && slots[i])
		i++;
	if (i == SLOTS - 1)
	{
		std::cerr << "MateriaSource slots are full." << std::endl;
		return ;
	}
	slots[i] = m;
}

void	MateriaSource::createMateria(std::string const &type)
{
	for ( int i = 0; i < SLOTS_MS; i++ )
		if ( materias[i] && materias[i]->getType() == type )
			return materias[i]->clone();
	return 0;
}
