/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/15 08:37:31 by ngoc             ###   ########.fr       */
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
    std::cout << mstack0.front() << std::endl;
    mstack0.pop_front();
    std::cout << mstack0.size() << std::endl;
    mstack0.push_back(3);
    mstack0.push_back(5);
    mstack0.push_back(737);
    mstack0.push_back(0);
    std::list<int>::iterator  it = mstack0.begin();
    std::list<int>::iterator  ite = mstack0.end();
    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    //std::stack<int>     s(mstack0);

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
    return 0;
}
