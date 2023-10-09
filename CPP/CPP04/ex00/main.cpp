/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/09 13:34:13 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "WrongCat.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main()
{
	const Animal* meta = new Animal();
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	Animal k;
	std::cout << "k:" << k.getType() << ", sound: ";
	k.makeSound();
	k = *i;
	std::cout << "k:" << k.getType() << ", sound: ";
	k.makeSound();
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); //will output the cat sound!
	j->makeSound();
	meta->makeSound();
	const WrongAnimal* m = new WrongCat();
	std::cout << "m:" << m->getType() << ", sound: ";
	m->makeSound();
	WrongAnimal n;
	std::cout << "n:" << n.getType() << ", sound: ";
	n.makeSound();
	n = *m;
	std::cout << "n:" << n.getType() << ", sound: ";
	n.makeSound();
	delete(meta);
	delete(i);
	delete(j);
	delete(m);
	return (0);
}
