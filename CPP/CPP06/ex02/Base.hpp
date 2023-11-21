/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 18:37:40 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include <iostream>

#include "Data.hpp"

#ifndef BASE_HPP
# define BASE_HPP

class Base
{
	private:
		Base(const Base&);
		Base &operator=(const Base& op);
	public:
		Base();
		virtual ~Base();

		uintptr_t	serialize( Data *data );
		Data*		deserialize( uintptr_t data );
};

#endif
