/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/16 08:53:16 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

#include <iostream>
#include <list>

class BitcoinExchange
{
	private:
        double                  _max_date;
        std::list<double>       _dates;
        std::list<float>        _prices;
		
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange&);
		BitcoinExchange	&operator=(const BitcoinExchange& op);
	public:
		BitcoinExchange(const char *);
		virtual ~BitcoinExchange();

		bool	isValidDateFormat(std::string&);
		bool    isValidNumber(const char*);
        float   exchange(std::string, float);

        class DateError : public std::exception
		{
			public: virtual const char* what() const throw();
		};
        class DataError : public std::exception
		{
			public: virtual const char* what() const throw();
		};
};

#endif
