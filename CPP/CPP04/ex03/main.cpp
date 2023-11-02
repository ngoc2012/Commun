/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/02 11:23:09 by ngoc             ###   ########.fr       */
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
	src->learnMateria(new Cure());
	src->learnMateria(new Ice());
	AMateria *tmp0 = new Ice();
	std::cout << "src->learnMateria(tmp0);" << std::endl;
	src->learnMateria(tmp0);
	delete tmp0;
	std::cout << "============= Character me =================\n";
	ICharacter* me = new Character("me");
	tmp = src->createMateria("ice");
	me->equip(tmp);
	std::cout << "============ tmp = src->createMateria(\"cure\"); ===========" << std::endl;
	tmp = src->createMateria("cure");
	me->equip(tmp);
	me->equip(tmp);
	me->equip(src->createMateria("ice"));
	AMateria* tmp1 = src->createMateria("ice");
	me->equip(tmp1);
	AMateria* tmp2 = src->createMateria("ice");
	me->equip(tmp2);
	delete tmp2;
	me->unequip(3);
	delete tmp1;

	std::cout << "============= Character bob =================\n";
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);
	me->use(1, *bob);
	bob->use(0, *me);
	bob->use(1, *me);
	std::cout << "============== END ============\n";

	delete bob;
	delete me;
	delete src;
	return 0;
}
