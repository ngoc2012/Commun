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

		iterator begin() { return (std::stack<T>::c.begin()); }
		const_iterator begin() const { return (std::stack<T>::c.begin()); }
		iterator end() { return (std::stack<T>::c.end()); }
		const_iterator end() const { return (std::stack<T>::c.end()); }
		reverse_iterator rbegin() { return (std::stack<T>::c.rbegin()); }
		const_reverse_iterator rbegin() const { return (std::stack<T>::c.rbegin()); }
		reverse_iterator rend() { return (std::stack<T>::c.rend()); }
		const_reverse_iterator rend() const { return (std::stack<T>::c.rend()); } 

};

template <typename T>
std::ostream& operator<<( std::ostream& out, const MutantStack<T>& a );

#include "MutantStack.tpp"

#endif
