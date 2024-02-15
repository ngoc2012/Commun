/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/15 11:39:38 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <vector>

class BitcoinExchange
{
	private:
        std::<std::string, float>    _prices;
		
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange&);
		BitcoinExchange	&operator=(const BitcoinExchange& op);
	public:
		BitcoinExchange(const char *);
		virtual ~BitcoinExchange();

        float   exchange(std::string, float) const;

        class OutOfDate : public std::exception
		{
			public: virtual const char* what() const throw();
		};
        class DataError : public std::exception
		{
			public: virtual const char* what() const throw();
		};
};

#endif
