/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 10:11:08 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>
#include <vector>

class Span
{
	private:
		unsigned int		_N;
        std::vector<int>    _v;
        std::vector<int>    _sorted;
		
		Span();
		Span(const Span&);
		Span	&operator=(const Span& op);
	public:
		Span(unsigned int);
		virtual ~Span();

        int     size() const;
        void    addNumber(int);
        int     shortestSpan() const;
        int     longestSpan() const;

        const char* TooManyElements::what() const throw()
        { return ("Error: Too many elements."); }
        const char* TooFewElements::what() const throw()
        { return ("Error: Too few elements."); }
};

std::ostream& operator<<( std::ostream& out, const Span& a );

#endif
