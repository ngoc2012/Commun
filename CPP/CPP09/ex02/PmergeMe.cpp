/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 21:24:55 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#include "PmergeMe.hpp"

template <typename T>
PmergeMe<T>::PmergeMe(std::vector<T>& a) { _a = &a; }

template <typename T>
PmergeMe<T>::~PmergeMe() {}

template <typename T>
void    PmergeMe<T>::sort()
{
    size_t n = _a->size() / 2;
    for (size_t i = 0; i < n; ++i)
        _p.push_back(PairedValue<T>((*_a)[i * 2], (*_a)[i * 2 + 1]));
    if (_a->size() > n * 2)
        _p.push_back(PairedValue<T>(-1, (*_a)[n * 2 + 1]));
    std::sort(p._p.begin(), p._p.end());

}

template <typename T>
int     PmergeMe<T>::binarySearch(std::vector<T>& arr, T target)
{
    int low = 0;
    int high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low;
}

template <typename T>
void    PmergeMe<T>::insertInSortedArray(std::vector<T>& arr, T num)
{
    int insertPos = binarySearch(arr, num);
    arr.insert(arr.begin() + insertPos, num);
}

template <typename T>
bool    PmergeMe<T>::isSorted(std::vector<T>& arr)
{
    for (size_t i = 0; i < arr.size() - 1; ++i)
        if (arr[i] > arr[i + 1])
            return false;
    return true;
}

template <typename T>
void    PmergeMe<T>::print()
{
    for (size_t i = 0; i < _a->size(); i++)
        std::cout << (*_a)[i] << " ";
    std::cout << std::endl;
}

template <typename T>
void    PmergeMe<T>::print_p()
{
    for (size_t i = 0; i < _p.size(); i++)
    {
        _p[i].print();
        std::cout << " ";
    }
    std::cout << std::endl;
}
