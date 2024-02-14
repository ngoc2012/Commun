/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 08:54:31 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

Span<T>::Span()
{
	_a = new T();
	_size = 0;
}

template <typename T>
Span<T>::Span(size_t n)
{
	_a = new T[n];
	_size = n;
	for (size_t i = 0; i < n; i++ )
		_a[i] = 0;
}

template <typename T>
Span<T>::Span(const Span& src)
{
	*this = src;
}

template <typename T>
Span<T>&	Span<T>::operator=( Span const & src )
{
	for (size_t i = 0; i < src.size(); i++ )
		_a[i] = src[i];
	return (*this);
}

template <typename T>
Span<T>::~Span() { delete [] _a; }

size_t	Span<T>::size() const { return (_size);}

std::ostream& operator<<( std::ostream& out, const Span<T>& a )
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
