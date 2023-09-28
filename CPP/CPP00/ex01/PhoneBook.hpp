/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PhoneBook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:20:40 by ngoc              #+#    #+#             */
/*   Updated: 2023/09/28 12:09:32 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONEBOOK_HPP
# define PHONEBOOK_HPP

# define N_CONTACTS 8

#include "Contact.hpp"

class PhoneBook
{
	private:
		int	n;
		Contact contacts[N_CONTACTS];
	public:
		PhoneBook(void);
		~PhoneBook(void);

		void	add(void);
		void	set_n(int n);
		void	show(void) const;
		void	search(void) const;
		int	get_n(void) const;
};

#endif
