/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/05 21:32:54 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>	// htons
#include <unistd.h>	// close
#include <iostream>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/ioctl.h>

#include <stdlib.h>
#include <cstdio> // perror
#include <cstring> // memcpy

# define BUFFER	1028
# define MAX_CLIENTS 128
# define PORT 4242
# define IP_ADDRESS "127.0.0.1"

#ifndef ANIMAL_HPP
# define ANIMAL_HPP

#include <iostream>

class Animal
{
	protected:
		std::string	type;
	public:
		Animal();
		Animal(const Animal&);
		Animal &operator=(const Animal& op);
		/*
		Deleting Through Base Class Pointer: The warning occurs when you use the delete operator to destroy an object through a pointer or reference to a base class (e.g., Animal* ptr = new Dog; delete ptr;). If the base class has a non-virtual destructor, it may not correctly call the derived class's destructor, potentially leading to resource leaks or undefined behavior.
		*/
		virtual ~Animal();

		virtual void    makeSound( void ) const;
		std::string     getType( void ) const;
};

#endif
