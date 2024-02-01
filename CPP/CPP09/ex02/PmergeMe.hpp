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
#include <typeinfo>

// Class for paired values
template <typename T>
class   PairedValue
{
    public:
        T       _y;
        T       _x;
        int     _pos;
        bool    _nan;

        PairedValue	&operator=(const PairedValue& op)
        {
            _y = op._y;
            _x = op._x;
        }

        PairedValue(T& a, T& b)
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

        PairedValue(T& b)
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
std::ostream& operator<<(std::ostream& s, PairedValue<T>& a)
{
    return s << "(" << a._y << ", " << a._x << ")";
}

class PmergeMe
{
	private:
		
		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);

        template <typename T>
        int         binarySearch(std::vector<T>& arr, T target, int start, int end);
        template <typename T>
        void        insertInSortedArray(std::vector<T>& arr, T num, int start, int end);

	public:
        bool        _debug;
        PmergeMe() {_debug = false;}

		virtual     ~PmergeMe() {}

        template <typename T>
        bool        isSorted(std::vector<T>& arr);
        template <typename T>
        void        sort(std::vector<T>&, std::vector<T>&);
        template <typename T>
        void        print(std::vector<T>&);
        template <typename T>
        void        print_p(std::vector<T>&);
        template <typename T>
        void        print_s(std::vector<T>&);
        template <typename T>
        void        print_y(std::vector<T>&);
};

#include "PmergeMe.cpp"

#endif
