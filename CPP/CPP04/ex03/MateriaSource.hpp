/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MateriaSource.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/13 17:34:45 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIASOURCE_HPP
# define MATERIASOURCE_HPP
# define SLOTS_MS 4

#include <iostream>
#include "ICharacter.hpp"

class MateriaSource: public IMateriaSource
{
	private:
		std::string	name;
		AMateria	*slots[SLOTS_MS];
		MateriaSource();
		MateriaSource(const Character&);
	public:
		MateriaSource &operator=(const MateriaSource& op);
		MateriaSource(std::string const & type);
		virtual ~MateriaSource();

		destroy( void );
};

#endif
