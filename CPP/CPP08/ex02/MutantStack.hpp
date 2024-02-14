/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 14:16:16 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <iostream>

template <typename T>
class MutantStack
{
	private:
		T*			_a;
		size_t		_size;
		
	public:
		typedef typename std::stack<T>::container_type::iterator iterator;
        typedef typename std::stack<T>::container_type::const_iterator const_iterator;
        typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
        typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

		MutantStack();
		MutantStack(size_t);
		MutantStack(const MutantStack&);
		MutantStack	&operator=(const MutantStack& op);
		virtual ~MutantStack();

		T& operator[](size_t) const;
		size_t	size() const;

		class IndexError : public std::exception {
		public:
			virtual const char* what() const throw() { return "Error: Index too big";}
		};
};

template <typename T>
std::ostream& operator<<( std::ostream& out, const MutantStack<T>& a );

#include "MutantStack.tpp"

#endif
