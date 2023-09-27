/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:20:40 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/27 06:17:38 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_H
# define PHONEBOOK_H

# define N_CONTACTS 8
# define WIDTH 10

#include "Contact.hpp"

class PhoneBook
{
	private:
		Contact contacts[N_CONTACTS];
	public:
		PhoneBook(void);
		~PhoneBook(void);

		void	add(void);
		void	show(void) const;
		void	search(void) const;
};

#endif
