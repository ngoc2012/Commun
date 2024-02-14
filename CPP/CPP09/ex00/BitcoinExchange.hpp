/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 15:55:47 by minh-ngu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <vector>

class BitcoinExchange
{
	private:
		unsigned int		_N;
        std::vector<int>    _v;
        std::vector<int>    _sorted;
		
		BitcoinExchange();
		
	public:

		BitcoinExchange(unsigned int const &);
		BitcoinExchange(const BitcoinExchange&);
		BitcoinExchange	&operator=(const BitcoinExchange& op);
		virtual ~BitcoinExchange();

        int     size() const;
        void    addNumber(int);
        int     shortestBitcoinExchange() const;
        int     longestBitcoinExchange() const;
		int     binarySearch(std::vector<int>& arr, int target, int start, int end);

		std::vector<int>*    	get_v();
		unsigned int			get_N();

		template <class Iterator>
        void        addNumber(Iterator start, Iterator end);

        class TooManyElements : public std::exception
		{
			public: virtual const char* what() const throw();
		};
		class TooFewElements : public std::exception
		{
			public: virtual const char* what() const throw();
		};
};

std::ostream& operator<<( std::ostream& out, BitcoinExchange& a );

template <class Iterator>
void    BitcoinExchange::addNumber(Iterator start, Iterator end)
{
    while (start != end)
        addNumber(*start++);
}

#endif
