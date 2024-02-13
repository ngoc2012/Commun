/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/13 17:37:13 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>

template <typename T>
class Array
{
	private:
		Array(const Array&);
		Array	&operator=(const Array& op);
	public:
		Array();
		virtual ~Array();

		Array*	generate(void);
		void	identify(Array* b);
		void	identify(Array& b);
};

template <typename T>
std::ostream& operator<<( std::ostream& out, const Array<T>& a )
{
    for (size_t i = 0;i < a.size();i++)
        out << a[i] << ", ";
    return out;
}

#endif
