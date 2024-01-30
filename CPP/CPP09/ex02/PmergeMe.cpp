/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/30 10:20:09 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <algorithm>
#include <typeinfo>

#include "PmergeMe.hpp"

template <typename T>
PmergeMe<T>::PmergeMe(std::vector<T>& a) { _a = &a; }

template <typename T>
PmergeMe<T>::~PmergeMe() {}

template <typename T>
void    PmergeMe<T>::sort()
{
    if (!_a->size())
        return ;
    if (_a->size() == 1)
    {
        _S = *_a;
        return ;
    }
    print();
    if (_a->size() == 2)
    {
        _S = *_a;
        if (_S[0] > _S[1])
            std::swap(_S[0], _S[1]);
        return ;
    }

    size_t  n = _a->size() / 2;
    size_t  ny = n;

    for (size_t i = 0; i < n; i++)
        _p.push_back(PairedValue<T>((*_a)[i * 2], (*_a)[i * 2 + 1]));
    if (_a->size() > n * 2)
    {
        _p.push_back(PairedValue<T>((*_a)[n * 2]));
        n++;
    }
    std::cout << "========================================================" << std::endl;
    print();
    std::cout << "========================================================" << std::endl;
    print_p();
    // NO RECURSIVE TEST
    std::sort(_p.begin(), _p.end());
    std::cout << "========================================================" << std::endl;
    print_p();
    //std::cout << "(x0=" << _p[0]._smaller << ", x1=" << _p[0]._larger << ") ";
    for (size_t i = 0; i < _p.size(); i++)
    {
        if (i == 0)
            std::cout << "(x" << i + 1 << "=" << _p[i]._smaller << ", x" << i + 2 << "=" << _p[i]._larger << ")";
        else
            std::cout << "(y" << i + 2 << "=" << _p[i]._smaller << ", x" << i + 2 << "=" << _p[i]._larger << ")";
        std::cout << " ";
    }
    std::cout << std::endl;
    // NO RECURSIVE TEST end
    if (!_p[0]._nan)
        _S.push_back(_p[0]._smaller);
    for (size_t i = 0; i < n; i++)
    {
        _S.push_back(_p[i]._larger);
    }
        
    print_s();
    for (size_t i = 1; i < ny; i++)
        if (!_p[i]._nan)
            _Y.push_back(_p[i]._smaller);
    std::cout << "Y:" << std::endl;
    for (size_t i = 0; i < _Y.size(); i++)
        std::cout << _Y[i] << " ";
    std::cout << std::endl;
    //size_t i = 1;
    //for (size_t i = 1; i < ny; ++i)
    //    std::cout << _p[i]._smaller << " ";
    //std::cout << std::endl;
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
    for (size_t i = 0; i < arr.size() - 1; i++)
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
        //std::cout << i << " ";
        _p[i].print();
        std::cout << " ";
    }
    std::cout << std::endl;
}

template <typename T>
struct isInt {
    static const bool value = false;
};

template <>
struct isInt<int> {
    static const bool value = true;
};

template <typename T>
void    PmergeMe<T>::print_s()
{
    std::cout << "S:" << std::endl;
    if (!_S.size())
        return ;
    //const std::type_info&   typeInfo = typeid(_S[0]);
    //bool                    isInt = (typeInfo == typeid(int));
    for (size_t i = 0; i < _S.size(); i++)
    {
        std::cout << _S[i] << " ";
        //else
        //    _S[i].print();
        std::cout << " ";
    }
    std::cout << std::endl;
}
