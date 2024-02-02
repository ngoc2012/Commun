/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/02 06:08:10 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <map>
#include <deque>

class   PairedValue
{
    public:
        int       _x;
        int       _y;
        int     _pos;

        PairedValue(int& x, int& y): _x(x), _y(y)
        {
            _pos = -1;
        }
};

std::ostream& operator<<(std::ostream& s, PairedValue& a);

template <typename T>
class PmergeMe
{
	private:
		
		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);

        int         binarySearch(T<int>& arr, int target, int start, int end);
        void        insertInSortedArray(T<int>& arr, int num, int start, int end);
	public:
        PmergeMe() {}

		virtual     ~PmergeMe() {}

        void        sort(T<int>&, T<int>&);
};

#include "PmergeMe.cpp"

#endif
