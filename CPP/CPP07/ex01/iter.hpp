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

template<typename T>
void    iter(T* a, size_t len, void (&f)(T &))
{
    for (size_t i = 0; i < len; i++)
        f(a[i]);
}

template<typename T>
void    print(T& x) {std::cout << x << " ";}

template<typename T>
void    double_it(T& x) {std::cout << x*2 << " ";}