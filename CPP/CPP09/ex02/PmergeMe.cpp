/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 19:18:39 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(std::vector<int>& a) { _a = &a; }

PmergeMe::~PmergeMe() {}

void    PmergeMe::sort()
{
    for (size_t i = 0; i < _a->size() / 2 - 1; ++i)
        _p.push_back(PairedValue<int>((*_a)[i * 2], (*_a)[i * 2 + 1]));
}

int     PmergeMe::binarySearch(std::vector<int>& arr, int target)
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

void    PmergeMe::insertInSortedArray(std::vector<int>& arr, int num)
{
    int insertPos = binarySearch(arr, num);
    arr.insert(arr.begin() + insertPos, num);
}

bool    PmergeMe::isSorted(std::vector<int>& arr)
{
    for (size_t i = 0; i < arr.size() - 1; ++i)
        if (arr[i] > arr[i + 1])
            return false;
    return true;
}

void    PmergeMe::print()
{
    for (size_t i = 0; i < _a->size(); i++)
        std::cout << (*_a)[i] << " ";
    std::cout << std::endl;
}

void    PmergeMe::print_p()
{
    for (size_t i = 0; i < _p.size(); i++)
        _p[i].print();
    std::cout << std::endl;
}

std::vector<int>*   PmergeMe::get_a(void) const {return (_a);}
