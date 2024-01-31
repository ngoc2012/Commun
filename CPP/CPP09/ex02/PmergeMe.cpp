/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/31 09:51:56 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    //size_t  ny = n;

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
    //std::cout << "(x0=" << _p[0]._y << ", x1=" << _p[0]._x << ") ";
    for (size_t i = 0; i < _p.size(); i++)
    {
        if (i == 0)
            std::cout << "(x" << i + 1 << "=" << _p[i]._y << ", x" << i + 2 << "=" << _p[i]._x << ")";
        else
            std::cout << "(y" << i + 2 << "=" << _p[i]._y << ", x" << i + 2 << "=" << _p[i]._x << ")";
        std::cout << " ";
    }
    std::cout << std::endl;
    // NO RECURSIVE TEST end
    if (!_p[0]._nan)
        _S.push_back(_p[0]._y);
    _S.push_back(_p[0]._x);
    int     j = 2;
    int     k = 2;
    int     k0 = k;
    int     nn = 2;
    int     j_max = _p.size() - 1;
    int     m_min = 0;
    int     k_max = j_max;
    while (j <= j_max)
    {
        k0 = k;
        k += j;
        m_min = 0;
        k_max = k - 2;
        if (k > j_max)
        {
            m_min = k - j_max;
            k_max = j_max;
        }
        // push to S from (k0 - 2) + 1 to (k - 2) - 1
        // and get the position
        //std::cout << (k0 - 2) + 1 << " " << (k - 2) - 1 << std::endl;
        for (int m = (k0 - 2) + 1; m < k_max; m++)
        {
            std::cout << m << " ";
            _S.push_back(_p[m]._x);
        }
        std::cout << std::endl;
        for (int m = m_min; m < j; m++)
        {
            std::cout << k - m << " ";

        }
        std::cout << std::endl;
        _S.push_back(_p[k_max]._x);
        print_s();

        nn *= 2;
        j = nn - j;
    }
    
    for (size_t i = 1; i < n; i++)
        if (!_p[i]._nan)
            _Y.push_back(_p[i]._y);
    std::cout << "Y:" << std::endl;
    for (size_t i = 0; i < _Y.size(); i++)
        std::cout << _Y[i] << " ";
    std::cout << std::endl;
    //size_t i = 1;
    //for (size_t i = 1; i < ny; ++i)
    //    std::cout << _p[i]._y << " ";
    //std::cout << std::endl;
}

template <typename T>
int PmergeMe<T>::binarySearch(std::vector<T>& arr, T target, int start, int end) {
    int low = start;
    int high = end;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == target) {
            return mid; // Element found at position mid.
        } else if (arr[mid] < target) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return low; // Element not found, but this is the position where it should be inserted.
}

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
