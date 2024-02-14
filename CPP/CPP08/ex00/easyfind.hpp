/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   easyfind.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 07:13:52 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_HPP
# define ARRAY_HPP

#include <iostream>

template <typename T>
class easyfind
{
	private:
		T*			_a;
		size_t		_size;
		
	public:
		easyfind();
		easyfind(size_t);
		easyfind(const easyfind&);
		easyfind	&operator=(const easyfind& op);
		virtual ~easyfind();

		T& operator[](size_t) const;
		size_t	size() const;

		class IndexError : public std::exception {
		public:
			virtual const char* what() const throw() { return "Error: Index too big";}
		};
};

template <typename T>
std::ostream& operator<<( std::ostream& out, const easyfind<T>& a );

#include "easyfind.tpp"

#endif
