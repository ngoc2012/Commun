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

//std::ostream& operator<<(std::ostream& s, PairedValue

class PmergeMe
{
	private:
		
		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);

        template <typename T>
        int         binarySearch(std::vector<PairedValue<T> >& arr, PairedValue<T> target, int start, int end);
        template <typename T>
        void        insertInSortedArray(std::vector<PairedValue<T> >& arr, PairedValue<T> num, int start, int end);

	public:
        bool        _debug;
        PmergeMe();
		virtual     ~PmergeMe();

        bool        isSorted(std::vector<PairedValue<int> >& arr);

        template <typename T>
        void        sort(std::vector<PairedValue<T> >&, std::vector<PairedValue<T> >&);
        template <typename T>
        void        print(std::vector<PairedValue<T> >&);
        template <typename T>
        void        print_p(std::vector<PairedValue<T> >&);
        template <typename T>
        void        print_s(std::vector<PairedValue<T> >&);
        template <typename T>
        void        print_y(std::vector<PairedValue<T> >&);
};

#endif
