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
		T*			_a;
		size_t		_size;
		Array(const Array&);
		Array	&operator=(const Array& op);
	public:
		Array();
		virtual ~Array();

		Array*	generate(void);
		void	identify(Array* b);
		void	identify(Array& b);

		class IndexError : public std::exception {
        public:
            virtual const char* what() const throw() { return "Index is out of bounds";}
    	};
};

template <typename T>
Array::~Array() { delete [] _a; }

template <typename T>
T& Array::operator[](size_t i) const {
    if (i >= _size)
        throw OutOfBoundsException();
    return _a[i];
}

template <typename T>
std::ostream& operator<<( std::ostream& out, const Array<T>& a )
{
    for (size_t i = 0;i < a.size();i++)
        out << a[i] << ", ";
    return out;
}

#endif
