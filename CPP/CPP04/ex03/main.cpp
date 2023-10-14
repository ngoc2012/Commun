/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/14 10:02:08 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Character.hpp"
#include "MateriaSource.hpp"
#include "Ice.hpp"
#include "Cure.hpp"

int main()
{
	AMateria* tmp;

	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	std::cout << "tmp = src->createMateria(\"cure\");" << std::endl;
	tmp = src->createMateria("cure");

	src->learnMateria(new Cure());
	ICharacter* me = new Character("me");
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);
	std::cout << "============ tmp = src->createMateria(\"cure\"); ===========" << std::endl;
	tmp = src->createMateria("cure");

	std::cout << "============= Character bob =================\n";
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	std::cout << "============== END ============\n";

	delete bob;
	delete me;
	delete src;
	return 0;
}
