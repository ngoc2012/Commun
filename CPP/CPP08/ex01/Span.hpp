/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Array.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 06:17:05 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>

template <typename T>
class Array
{
	private:
		T*			_a;
		size_t		_size;
		
	public:
		Array();
		Array(size_t);
		Array(const Array&);
		Array	&operator=(const Array& op);
		virtual ~Array();

		T& operator[](size_t) const;
		size_t	size() const;

		class IndexError : public std::exception {
		public:
			virtual const char* what() const throw() { return "Error: Index too big";}
		};
};

template <typename T>
std::ostream& operator<<( std::ostream& out, const Array<T>& a );

#include "Array.tpp"

#endif
