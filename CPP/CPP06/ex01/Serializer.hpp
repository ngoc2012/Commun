/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 18:01:57 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

class Serializer
{
	private:
		e_types		type;
		char		_char;
		int		_int;
		float		_float;
		double		_double;
		//long double	_ldouble;

		Serializer();
		Serializer(const Serializer&);
		Serializer &operator=(const Serializer& op);
	public:
		virtual ~Serializer();

		uintptr_t	serialize( Data *data );
		Data*		deserialize( uintptr_t data );
};

#endif
