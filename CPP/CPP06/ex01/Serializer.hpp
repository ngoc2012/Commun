/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 18:02:41 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

#include <iostream>

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

class Serializer
{
	private:
		Serializer(const Serializer&);
		Serializer &operator=(const Serializer& op);
	public:
		Serializer();
		virtual ~Serializer();

		uintptr_t	serialize( Data *data );
		Data*		deserialize( uintptr_t data );
};

#endif
