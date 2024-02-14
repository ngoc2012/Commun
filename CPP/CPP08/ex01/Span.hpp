/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 09:48:34 by ngoc             ###   ########.fr       */
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

};

std::ostream& operator<<( std::ostream& out, const Span& a );

#endif
