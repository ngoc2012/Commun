/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/01 13:18:03 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <map>
#include <list>

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

class PmergeMe
{
	private:
		
		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);

        int         binarySearch(std::vector<int>& arr, int target, int start, int end);
        void        insertInSortedArray(std::vector<int>& arr, int num, int start, int end);

        int         binarySearchA(std::list<int>& lst, int target, int start, int end);
        void        insertInSortedArrayA(std::list<int>& lst, int num, int start, int end);

	public:
        PmergeMe() {}

		virtual     ~PmergeMe() {}

        bool        isSorted(std::vector<int>&);
        void        sort(std::vector<int>&, std::vector<int>&);
        void        print(std::vector<int>&);
        void        print_p(std::vector<PairedValue>&);

        bool        isSortedA(std::list<int>&, int);
        void        sortA(std::list<int>&, std::list<int>&, int);
        void        printA(std::list<int>&, int);
        void        print_pA(std::list<PairedValue>&, int);
        
};

#endif
