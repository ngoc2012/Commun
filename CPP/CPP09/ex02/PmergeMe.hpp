/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/31 09:49:44 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

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

        bool operator>(const PairedValue& other) const {
            return _x > other._x;
        }
};

//std::ostream& operator<<(std::ostream& s, PairedValue

template <typename T>
class PmergeMe
{
	private:
        std::vector<T>*                   _a;

		PmergeMe();
		PmergeMe(const PmergeMe&);
		PmergeMe	&operator=(const PmergeMe& op);

        int         binarySearch(std::vector<T>& arr, T target, int start, int end);

	public:
        std::vector<PairedValue<T> >    _p;
        std::vector<T>                  _S;
        std::vector<T>                  _Y;
		PmergeMe(std::vector<T>&);
		virtual ~PmergeMe();

        bool        isSorted(std::vector<T>& arr);
        void        sort();
        void        print();
        void        print_p();
        void        print_s();
        void        print_y();
        void        insertInSortedArray(std::vector<T>& arr, T num, int start, int end);
};

#endif
