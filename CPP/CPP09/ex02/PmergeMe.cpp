/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/02 06:09:19 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_CPP
# define PMERGEME_CPP

#include "PmergeMe.hpp"

template <typename T, typename U>
void    PmergeMe<T,U>::sort(T& A, T& S)
{
    size_t  n = A.size();
    if (!n)
        return ;
    if (n == 1)
    {
        S = A;
        return ;
    }
    if (n == 2)
    {
        S = A;
        if (S[0] > S[1])
            std::swap(S[0], S[1]);
        return ;
    }
    
    if (n <= 4)
    {
        S = A;
        for (size_t i = 1; i < n; i++)
            for (size_t j = 0; j < i; j++)
                if (S[i] < S[j])
                    std::swap(S[i], S[j]);
        return ;
    }
    
    // x, y with x is bigger
    std::map<int, int>  P;
    T    X;
    size_t  n2 = n / 2;
    for (size_t i = 0; i < n2; i++)
    {
        if (A[i * 2 + 1] > A[i * 2])
        {
            X.push_back(A[i * 2 + 1]);
            P[A[i * 2 + 1]] = A[i * 2];
        }
        else
        {
            X.push_back(A[i * 2]);
            P[A[i * 2]] = A[i * 2 + 1];
        }
        
    }
    if (n > n2 * 2)
    {
        X.push_back(A[n2 * 2]);
        P[A[n2 * 2]] = -1;
    }

    T    XX;
    PmergeMe            p;
    p.sort(X, XX);

    U        VP;
    for (size_t i = 0; i < XX.size(); i++)
        VP.push_back(PairedValue(XX[i], P[XX[i]]));

    int     pos = 0;
    if (VP[0]._y != -1)
    {
        S.push_back(VP[0]._y);
        pos++;
    }
    S.push_back(VP[0]._x);
    pos++;
    int     j = 0;
    int     k = 0;
    int     k0 = k;
    int     nn = 1;
    int     k_max = VP.size() - 1;
    int     insertPos;
    do {
        nn *= 2;
        j = nn - j;
        k0 = k;
        k += j;
        if (k > k_max)
            k = k_max;
        for (int m = k0 + 1; m < k; m++)
        {
            VP[m]._pos = pos;
            S.push_back(VP[m]._x);
            pos++;
        }
        VP[k]._pos = S.size();
        for (int m = k; m > k0; m--)
        {
            if (VP[m]._y != -1)
            {
                insertPos = binarySearch(S, VP[m]._y, 0, VP[k - 1]._pos);
                S.insert(S.begin() + insertPos, VP[m]._y);
                pos++;
                for (int i = k0 + 1; i <= k; i++)
                    if (VP[i]._pos >= insertPos)
                        VP[i]._pos++;
            }
        }
        S.push_back(VP[k]._x);
        pos++;
    } while (k < k_max);
}

template <typename T, typename U>
int     PmergeMe<T,U>::binarySearch(T& arr, int target, int start, int end) {
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
template <typename T, typename U>
void    PmergeMe<T,U>::insertInSortedArray(T& arr, int num, int start, int end)
{
    int insertPos = binarySearch(arr, num, start, end);
    arr.insert(arr.begin() + insertPos, num);
}

std::ostream& operator<<(std::ostream& s, PairedValue& a)
{
    return s << "(" << a._y << ", " << a._x << ")";
}

#endif
