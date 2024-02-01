/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/01 08:41:27 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename T>
PmergeMe<T>::PmergeMe(std::vector<T>& a) { _a = &a; _debug = false;}

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
    if (_a->size() == 2)
    {
        _S = *_a;
        if (_S[0] > _S[1])
            std::swap(_S[0], _S[1]);
        return ;
    }

    size_t  n = _a->size() / 2;
    for (size_t i = 0; i < n; i++)
        _p.push_back(PairedValue<T>((*_a)[i * 2], (*_a)[i * 2 + 1]));
    if (_a->size() > n * 2)
    {
        _p.push_back(PairedValue<T>((*_a)[n * 2]));
        n++;
    }
    if (!_debug)
        std::sort(_p.begin(), _p.end());
    else
    {
        std::cout << "========================================================" << std::endl;
        print();
        std::cout << "========================================================" << std::endl;
        print_p();
        // NO RECURSIVE TEST
        std::sort(_p.begin(), _p.end());
        std::cout << "========================================================" << std::endl;
        print_p();
        for (size_t i = 0; i < _p.size(); i++)
        {
            if (i == 0)
                std::cout << "(x" << i + 1 << "=" << _p[i]._y << ", x" << i + 2 << "=" << _p[i]._x << ")";
            else
                std::cout << "(y" << i + 2 << "=" << _p[i]._y << ", x" << i + 2 << "=" << _p[i]._x << ")";
            std::cout << " ";
        }
        std::cout << std::endl;
    }
    /*
    */
    // NO RECURSIVE TEST end
    if (!_p[0]._nan)
        _S.push_back(_p[0]._y);
    _S.push_back(_p[0]._x);
    int     j = 0;
    int     k = 0;
    int     k0 = k;
    int     nn = 1;
    int     k_max = _p.size() - 1;
    int     insertPos;
    //_p[1]._pos = _S.size();
    do {
        nn *= 2;
        j = nn - j;
        k0 = k;
        k += j;
        if (k > k_max)
            k = k_max;
        for (int m = k0 + 1; m < k; m++)
        {
            if (_debug)
                std::cout << m + 2 << ":" << _S.size() << " ";
            _p[m]._pos = _S.size();
            _S.push_back(_p[m]._x);
        }
        _p[k]._pos = _S.size();
        if (_debug)
            std::cout << std::endl;
        for (int m = k; m > k0; m--)
        {
            if (_debug)
                std::cout << m + 2 << " ";
            if (!_p[m]._nan)
            {
                _Y.push_back(_p[m]._y);
                insertPos = binarySearch(_S, _p[m]._y, 0, _p[k - 1]._pos);
                if (_debug)
                    std::cout << "Insert: " << _p[m]._y << " " << k - 1 << " " << _p[k - 1]._pos << " " << insertPos << std::endl;
                _S.insert(_S.begin() + insertPos, _p[m]._y);
                for (int i = k0 + 1; i <= k; i++)
                    if (_p[i]._pos > insertPos)
                        _p[i]._pos++;
            }
            if (_debug)
                print_p();
        }
        if (_debug)
            std::cout << std::endl;

        _S.push_back(_p[k]._x);

        if (_debug)
        {
            print_p();
            print_s();
            print_y();
        }
    } while (k < k_max);
}

template <typename T>
int PmergeMe<T>::binarySearch(std::vector<T>& arr, T target, int start, int end) {
    int low = start;
    int high = end;

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

// start end included
template <typename T>
void    PmergeMe<T>::insertInSortedArray(std::vector<T>& arr, T num, int start, int end)
{
    int insertPos = binarySearch(arr, num, start, end);
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
    std::cout << "P:" << std::endl;
    for (size_t i = 0; i < _p.size(); i++)
    {
        std::cout << _p[i]._pos << ":";
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

template <typename T>
void    PmergeMe<T>::print_y()
{
    std::cout << "Y:" << std::endl;
    for (size_t i = 0; i < _Y.size(); i++)
        std::cout << _Y[i] << " ";
    std::cout << std::endl;
}
