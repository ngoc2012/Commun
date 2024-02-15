/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/15 17:52:21 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <map>

class BitcoinExchange
{
	private:
        std::map<int, float>        _prices;
		
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange&);
		BitcoinExchange	&operator=(const BitcoinExchange& op);
	public:
		BitcoinExchange(const char *);
		virtual ~BitcoinExchange();

        float   exchange(std::string, float);

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
