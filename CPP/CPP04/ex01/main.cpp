/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/10 18:13:12 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cat.hpp"
#include "Dog.hpp"
#define N_ANIMAL 100

int main()
{
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	delete(i);
	delete(j);
	Dog* m = new Dog();
	m->setBrain("haha", 25);
	m->setBrain("hehe", 70);
	m->setBrain("moemoe", -1);
	m->setBrain("hoaoha", 100);
	m->showBrain();
	Dog k;
	k = *m;
	k.showBrain();
	Dog h(k);
	h.showBrain();
	delete(m);
	Cat* m1 = new Cat();
	m1->setBrain("hoho", 1);
	m1->setBrain("enen", 99);
	m1->setBrain("moemoe", -1);
	m1->setBrain("hoaoha", 100);
	m1->showBrain();
	Cat k1;
	k1 = *m1;
	k1.showBrain();
	delete(m1);
	Animal	*zoo[N_ANIMAL];
	for (int i = 0; i < N_ANIMAL; i++)
	{
		if (i % 2)
			zoo[i] = new Dog();
		else
			zoo[i] = new Cat();
	}
	for (int i = 0; i < N_ANIMAL; i++)
		delete(zoo[i]);
	return (0);
}
