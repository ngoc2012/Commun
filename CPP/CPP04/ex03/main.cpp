/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/02 11:59:58 by ngoc             ###   ########.fr       */
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
	std::cout << ">>>src->learnMateria(new Ice());" << std::endl;
	Ice	*i = new Ice();
	src->learnMateria(i);
	std::cout << ">>>tmp = src->createMateria(\"cure\");" << std::endl;
	tmp = src->createMateria("cure");

	std::cout << ">>>src->learnMateria(new Cure());" << std::endl;
	Cure	*c = new Cure();
	src->learnMateria(c);
	std::cout << ">>>src->learnMateria(new Cure());" << std::endl;
	src->learnMateria(c->clone());
	std::cout << ">>>src->learnMateria(new Ice());" << std::endl;
	src->learnMateria(i->clone());
	std::cout << ">>>AMateria *tmp0 = new Ice();" << std::endl;
	AMateria *tmp0 = new Ice();
	std::cout << ">>>src->learnMateria(tmp0);" << std::endl;
	src->learnMateria(tmp0);
	delete tmp0;
	std::cout << ">>>============= Character me =================\n";
	std::cout << ">>>ICharacter* me = new Character(\"me\");" << std::endl;
	ICharacter* me = new Character("me");
	std::cout << ">>>tmp = src->createMateria(\"ice\");" << std::endl;
	tmp = src->createMateria("ice");
	std::cout << ">>>me->equip(tmp);" << std::endl;
	me->equip(tmp);
	std::cout << ">>>============ tmp = src->createMateria(\"cure\"); ===========" << std::endl;
	std::cout << ">>>tmp = src->createMateria(\"cure\");" << std::endl;
	tmp = src->createMateria("cure");
	std::cout << ">>>me->equip(tmp);" << std::endl;
	me->equip(tmp);
	std::cout << ">>>me->equip(tmp);" << std::endl;
	me->equip(tmp);
	std::cout << ">>>me->equip(src->createMateria(\"ice\"));" << std::endl;
	me->equip(src->createMateria("ice"));
	std::cout << ">>>AMateria* tmp1 = src->createMateria(\"ice\");" << std::endl;
	AMateria* tmp1 = src->createMateria("ice");
	std::cout << ">>>me->equip(tmp1);" << std::endl;
	me->equip(tmp1);
	std::cout << ">>>AMateria* tmp2 = src->createMateria(\"ice\");" << std::endl;
	AMateria* tmp2 = src->createMateria("ice");
	std::cout << ">>>me->equip(tmp2);" << std::endl;
	me->equip(tmp2);
	delete tmp2;
	std::cout << ">>>me->unequip(3);" << std::endl;
	me->unequip(3);
	delete tmp1;

	std::cout << ">>>============= Character bob =================\n";
	std::cout << ">>>ICharacter* bob = new Character(\"bob\");" << std::endl;
	ICharacter* bob = new Character("bob");
	std::cout << ">>>me->use(0, *bob);" << std::endl;
	me->use(0, *bob);
	std::cout << ">>>me->use(1, *bob);" << std::endl;
	me->use(1, *bob);
	std::cout << ">>>bob->use(0, *me);" << std::endl;
	bob->use(0, *me);
	std::cout << ">>>bob->use(1, *me);" << std::endl;
	bob->use(1, *me);
	std::cout << ">>>============== END ============\n";

	std::cout << ">>>delete bob;" << std::endl;
	delete bob;
	std::cout << ">>>delete me;" << std::endl;
	delete me;
	std::cout << ">>>delete src;" << std::endl;
	delete src;
	return 0;
}
