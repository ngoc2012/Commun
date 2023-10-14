/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/13 23:05:05 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP
# define SLOTS_MS 4

#include <iostream>
#include "Character.hpp"
#include "IMateriaSource.hpp"

class MateriaSource: public IMateriaSource
{
	private:
		AMateria	*materias[SLOTS_MS];
	public:
		MateriaSource();
		MateriaSource(const MateriaSource&);
		MateriaSource(const Character&);
		MateriaSource &operator=(const MateriaSource& op);
		MateriaSource(std::string const & type);
		virtual ~MateriaSource();

		void	destroy(void);
		void learnMateria(AMateria*);
		AMateria* createMateria(std::string const & type);
};

#endif
