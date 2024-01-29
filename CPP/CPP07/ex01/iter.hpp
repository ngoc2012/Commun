/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 06:19:06 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 07:14:03 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

template<typename T>
void    swap(T& a, T& b)
{
    T tmp = a;
    a = b;
    b = tmp;
}

template<typename T>
T   min(T& a, T& b) { return ( a < b ? a : b ); }

template<typename T>
T   max(T& a, T& b) { return ( a > b ? a : b ); }
