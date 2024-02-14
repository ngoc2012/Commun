/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Span.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/14 08:57:56 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPAN_HPP
# define SPAN_HPP

#include <iostream>

class Span
{
	private:
		unsigned int		_N;
        std::vector<int>    _v;
		
		Span();
		Span(const Span&);
		Span	&operator=(const Span& op);
	public:
		Span(unsigned int);
		virtual ~Span();

        addNumber();

};

std::ostream& operator<<( std::ostream& out, const Span& a );

#endif
