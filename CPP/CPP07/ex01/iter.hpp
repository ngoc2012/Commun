/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 06:19:06 by ngoc              #+#    #+#             */
/*   Updated: 2024/01/29 07:24:00 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstdlib> // Required for atoi function

template<typename T>
void    iter(T* a, size_t len, void (&f)(T const &))
{
    for (size_t i = 0; i < len; i++)
        f(a[i]);
}

template<typename T>
void    print(T const & x) {std::cout << x << " ";}

template<typename T>
void    double_it(T const & x) {std::cout << std::atoi(x)*2 << " ";}