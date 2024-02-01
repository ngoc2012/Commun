/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/01 13:22:54 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_CPP
# define PMERGEME_CPP

#include "PmergeMe.hpp"

template <typename T>
void    PmergeMe::sort(std::vector<T>& _a, std::vector<T>& _S)
{
    std::vector<PairedValue<T> >    _p;
    std::vector<T>                  _Y;

    size_t  n = _a.size();
    if (!n)
        return ;
    if (n == 1)
    {
        _S = _a;
        return ;
    }
    if (n == 2)
    {
        _S = _a;
        if (_S[0] > _S[1])
            std::swap(_S[0], _S[1]);
        return ;
    }
    
    if (n <= 4)
    {
        _S = _a;
        for (size_t i = 1; i < n; i++)
            for (size_t j = 0; j < i; j++)
                if (_S[i] < _S[j])
                    std::swap(_S[i], _S[j]);
        return ;
    }
    
    n /= 2;
    for (size_t i = 0; i < n; i++)
        _p.push_back(PairedValue<T>(_a[i * 2], _a[i * 2 + 1]));
    if (_a.size() > n * 2)
    {
        _p.push_back(PairedValue<T>(_a[n * 2]));
        n++;
    }
    if (!_debug)
    {
        PmergeMe            pp;
        std::vector<T>      SS;
    }
        std::sort(_p.begin(), _p.end());
    else
    {
        std::cout << "========================================================" << std::endl;
        print(_a);
        std::cout << "========================================================" << std::endl;
        print_p(_p);
        // NO RECURSIVE TEST
        std::sort(_p.begin(), _p.end());
        std::cout << "========================================================" << std::endl;
        print_p(_p);
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
                    if (_p[i]._pos >= insertPos)
                        _p[i]._pos++;
            }
            if (_debug)
            {
                print_s(_S);
                print_p(_p);
            }
                
        }
        if (_debug)
            std::cout << std::endl;

        _S.push_back(_p[k]._x);

        if (_debug)
        {
            print_p(_p);
            print_s(_S);
            print_y(_Y);
        }
    } while (k < k_max);
}

template <typename T>
int PmergeMe::binarySearch(std::vector<T>& arr, T target, int start, int end) {
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
void    PmergeMe::insertInSortedArray(std::vector<T>& arr, T num, int start, int end)
{
    int insertPos = binarySearch(arr, num, start, end);
    arr.insert(arr.begin() + insertPos, num);
}

template <typename T>
bool    PmergeMe::isSorted(std::vector<T>& a)
{
    for (size_t i = 0; i < a.size() - 1; i++)
        if (a[i] > a[i + 1])
            return false;
    return true;
}

template <typename T>
void    PmergeMe::print(std::vector<T>& _a)
{
    for (size_t i = 0; i < _a.size(); i++)
        std::cout << _a[i] << " ";
    std::cout << std::endl;
}

template <typename T>
void    PmergeMe::print_p(std::vector<T>& p)
{
    std::cout << "P:" << std::endl;
    for (size_t i = 0; i < p.size(); i++)
    {
        std::cout << i << ":" << p[i]._pos << ":";
        p[i].print();
        std::cout << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void    PmergeMe::print_s(std::vector<T>& S)
{
    std::cout << "S:" << std::endl;
    if (!S.size())
        return ;
    //const std::type_info&   typeInfo = typeid(S[0]);
    //bool                    isInt = (typeInfo == typeid(int));
    for (size_t i = 0; i < S.size(); i++)
    {
        std::cout << i << ":" << S[i] << " ";
        std::cout << " ";
    }
    std::cout << std::endl;
}

template <typename T>
void    PmergeMe::print_y(std::vector<T>& Y)
{
    std::cout << "Y:" << std::endl;
    for (size_t i = 0; i < Y.size(); i++)
        std::cout << Y[i] << " ";
    std::cout << std::endl;
}

#endif
