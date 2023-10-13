/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:16:32 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/13 17:48:24 by ngoc             ###   ########.fr       */
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
			delete(materias[i]);
}
MateriaSource&	MateriaSource::operator=( MateriaSource const & src )
{
	destroy();
	for (int i = 0; i < SLOTS; i++)
		materias[i] = new AMateria(src.materias[i]);
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
	while (i < SLOTS_MS && materias[i])
		i++;
	if (i == SLOTS_MS - 1)
	{
		std::cerr << "MateriaSource materias are full." << std::endl;
		return ;
	}
	materias[i] = m;
}

void	MateriaSource::createMateria(std::string const &type)
{
	for ( int i = 0; i < SLOTS_MS; i++ )
		if ( materias[i] && materias[i]->getType() == type )
			return materias[i]->clone();
	return 0;
}
