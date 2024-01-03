/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Address.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:57:07 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/03 09:17:47 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef ADDRESS_HPP
# define ADDRESS_HPP

class	Address
{
	private:
		Address(const Address&);
		Address	&operator=(const Address& op);

	public:
		Address();
		virtual ~Address();
};

#endif
