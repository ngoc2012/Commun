/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Contact.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:20:40 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/27 06:15:24 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
# define PHONEBOOK_H

# define N_CONTACTS 8
# define WIDTH 10

#include <iostream>
#include <iomanip>      // std::setw

class Contact
{
	private:
		std::string _firstName;
		std::string _lastName;
		std::string _nickname;
		std::string _phoneNumber;
		std::string _darkestSecret;
	public:
		Contact(void);
		~Contact(void);

		void	show(int index) const;
};

class PhoneBook
{
	private:
		Contact contacts[8];
	public:
		PhoneBook(void);
		~PhoneBook(void);

		void	add(void);
		void	show(void) const;
		void	search(void) const;
};

#endif
