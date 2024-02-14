/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 08:55:23 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>

template <typename T>
class Span
{
	private:
		T*			_a;
		size_t		_size;
		
		Span();
		Span(const Span&);
		Span	&operator=(const Span& op);
	public:
		Span(unsigned int);
		virtual ~Span();

		T& operator[](size_t) const;
		size_t	size() const;

		class IndexError : public std::exception {
		public:
			virtual const char* what() const throw() { return "Error: Index too big";}
		};
};

template <typename T>
std::ostream& operator<<( std::ostream& out, const Span<T>& a );

#include "Span.tpp"

#endif
