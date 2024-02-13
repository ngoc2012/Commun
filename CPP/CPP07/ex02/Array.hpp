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
Array<T>::Array()
{
	_a = new T();
	_size = 0;
}

template <typename T>
Array<T>::Array(size_t n)
{
	_a = new T[n];
	_size = n;
	for (size_t i = 0; i < n; i++ )
		_a[i] = 0;
}

template <typename T>
Array<T>::Array(const Array& src)
{
	*this = src;
}

template <typename T>
Array<T>&	Array<T>::operator=( Array const & src )
{
	for (size_t i = 0; i < src.size(); i++ )
		_a[i] = src[i];
	return (*this);
}

template <typename T>
Array<T>::~Array() { delete [] _a; }

template <typename T>
T& Array<T>::operator[](size_t i) const
{
	if (i >= _size)
		throw IndexError();
	return _a[i];
}

template <typename T>
size_t	Array<T>::size() const { return (_size);}

template <typename T>
std::ostream& operator<<( std::ostream& out, const Array<T>& a )
{
	if (!a.size())
	{
		out << "[]";
		return (out);
	}
	out << "[";
	for (size_t i = 0;i < a.size() - 1;i++)
		out << a[i] << ", ";
	out << a[a.size() - 1] << "]";
	return (out);
}

#endif