/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/15 10:00:16 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <deque>

#include "MutantStack.hpp"

int	main()
{
    std::cout << "============== std::list ===============" << std::endl;
    std::list<int>    mstack0;
    mstack0.push_back(5);
    mstack0.push_back(17);
    std::cout << mstack0.back() << std::endl;
    mstack0.pop_back();
    std::cout << mstack0.size() << std::endl;
    mstack0.push_back(3);
    mstack0.push_back(5);
    mstack0.push_back(737);
    mstack0.push_back(0);
    std::list<int>::iterator  itt = mstack0.begin();
    std::list<int>::iterator  itte = mstack0.end();
    ++itt;
    --itt;
    while (itt != itte)
    {
        std::cout << *itt << std::endl;
        ++itt;
    }

    std::cout << "============== MutantStack ===============" << std::endl;
    MutantStack<int>    mstack;
    mstack.push(5);
    mstack.push(17);
    std::cout << mstack.top() << std::endl;
    mstack.pop();
    std::cout << mstack.size() << std::endl;
    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    mstack.push(0);
    MutantStack<int>::iterator  it = mstack.begin();
    MutantStack<int>::iterator  ite = mstack.end();
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int>     s(mstack);

    std::cout << "============== MutantStack const_reverse_iterator ===============" << std::endl;
    MutantStack<int>::const_iterator  cit = mstack.begin();
    MutantStack<int>::const_iterator  cite = mstack.end();
    std::cout << "[ ";
    while (cit != cite)
    {
        if (cit + 1 != cite)
            std::cout << *cit << ", ";
        else
            std::cout << *cit;
        ++cit;
    }
    std::cout << " ]" << std::endl;

    std::cout << "============== MutantStack reverse_iterator ===============" << std::endl;
    MutantStack<int>::reverse_iterator  rit = mstack.rbegin();
    MutantStack<int>::reverse_iterator  rite = mstack.rend();
    std::cout << "[ ";
    while (rit != rite)
    {
        if (rit + 1 != rite)
            std::cout << *rit << ", ";
        else
            std::cout << *rit;
        ++rit;
    }
    std::cout << " ]" << std::endl;

    std::cout << "============== MutantStack const_reverse_iterator ===============" << std::endl;
    MutantStack<int>::const_reverse_iterator  crit = mstack.rbegin();
    MutantStack<int>::const_reverse_iterator  crite = mstack.rend();
    std::cout << "[ ";
    while (crit != crite)
    {
        if (crit + 1 != crite)
            std::cout << *crit << ", ";
        else
            std::cout << *crit;
        ++crit;
    }
    std::cout << " ]" << std::endl;
    return 0;
}
