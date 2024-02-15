/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MutantStack.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khni <ael-khni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 18:21:41 by ael-khni          #+#    #+#             */
/*   Updated: 2024/02/15 08:43:34 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

#include <iostream>
#include <algorithm>
#include <list>
#include <stack>
#include <deque>

template<typename T, class Container = std::deque<T> > 
class MutantStack : public std::stack< T, Container >
{
public:

    MutantStack( void ) {};
    ~MutantStack( void ) {};

    MutantStack( const MutantStack& rhs );
    MutantStack&    operator=( const MutantStack& rhs );

    typedef typename Container::iterator    iterator;
    typedef typename std::stack<T>::container_type::const_iterator const_iterator;
    typedef typename std::stack<T>::container_type::reverse_iterator reverse_iterator;
    typedef typename std::stack<T>::container_type::const_reverse_iterator const_reverse_iterator;

    iterator    begin();
    iterator    end();
};

#include "MutantStack.tpp"

#endif
