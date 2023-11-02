/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/02 11:29:22 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MateriaSource.hpp"

MateriaSource::MateriaSource()
{
	for (int i = 0; i < SLOTS_MS; i++) {materias[i] = 0;}
	std::cout << "MateriaSource default constructor." << std::endl;
}
MateriaSource::MateriaSource(const MateriaSource& src) {
	*this = src;
	std::cout << "MateriaSource copy constructor." << std::endl;
}
void	MateriaSource::destroy(void)
{
	for (int i = 0; i < SLOTS_MS; i++)
		if (materias[i])
			delete materias[i];
}
MateriaSource&	MateriaSource::operator=( MateriaSource const & src )
{
	destroy();
	for (int i = 0; i < SLOTS_MS; i++)
		materias[i] = src.materias[i]->clone();
	return (*this);
}
MateriaSource::~MateriaSource()
{
	destroy();
 	std::cout << "MateriaSource destructor." << std::endl;
}

void	MateriaSource::learnMateria(AMateria* m)
{
	int	i = -1;
	while (++i < SLOTS_MS && materias[i])
		if (materias[i] == m)
		{
			std::cerr << "Error: Materia " << m->getType() << " does existed in this MateriaSource." << std::endl;
			return ;
		}
	if (i == SLOTS_MS)
	{
		std::cerr << "MateriaSource materias are full." << std::endl;
		return ;
	}
	materias[i] = m;
}

AMateria	*MateriaSource::createMateria(std::string const &type)
{
	for ( int i = 0; i < SLOTS_MS; i++ )
		if ( materias[i] && materias[i]->getType() == type )
			return materias[i]->clone();
	std::cerr << "Error: Type "<< type << " not found." << std::endl;
	return 0;
}
