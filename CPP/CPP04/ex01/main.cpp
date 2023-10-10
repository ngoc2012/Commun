/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/10 17:31:47 by ngoc             ###   ########.fr       */
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
	delete(m);
	//Animal	zoo[N_ANIMAL];
	//for (int i = 0; i < N_ANIMAL; i++)
	//{
	//	if (i % 2)

	//}
	//for (int i = 0; i < N_ANIMAL; i++)
	//{
	//}
	return (0);
}
