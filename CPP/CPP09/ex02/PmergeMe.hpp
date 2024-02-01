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
#include <algorithm>
#include <map>

class   PairedValue
{
    public:
        int       _y;
        int       _x;
        int     _pos;
        bool    _nan;

        PairedValue	&operator=(const PairedValue& op)
        {
            _y = op._y;
            _x = op._x;
            _pos = op._pos;
            _nan = op._nan;
        }

        PairedValue(int& a, int& b)
        {
            if (a > b)
            {
                _x = a;
                _y = b;
            }
            else
            {
                _x = b;
                _y = a;
            }
            _pos = -1;
            _nan = false;
        }

        PairedValue(int& b)
        {
            _x = b;
            _y = b;
            _pos = -1;
            _nan = true;
        }

        void    print() { std::cout << "(" << _y << ", " << _x << ")";}

        bool operator<(const PairedValue& other) const {
            return _x < other._x;
        }

        bool operator==(const PairedValue& other) const {
            return _x == other._x;
        }

        bool operator>(const PairedValue& other) const {
            return _x > other._x;
        }
};

template <typename T>
std::ostream& operator<<(std::ostream& s, PairedValue& a)
{
    return s << "(" << a._y << ", " << a._x << ")";
}

class PmergeMe
{
	private:
		
		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);

        int         binarySearch(std::vector<int>& arr, int target, int start, int end);
        void        insertInSortedArray(std::vector<int>& arr, int num, int start, int end);

	public:
        bool        _debug;
        PmergeMe() {_debug = false;}

		virtual     ~PmergeMe() {}

        bool        isSorted(std::vector<int>&);
        void        sort(std::vector<int>&, std::vector<int>&);
        void        print(std::vector<int>&);
        void        print_p(std::map<int, int>&);
};

#endif
