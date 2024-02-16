/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/16 10:18:01 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <list>

class RPN
{
	private:
		RPN(const RPN&);
		RPN	&operator=(const RPN& op);

	public:
		RPN();
		virtual ~RPN();

        int    eval(const std::string& expression);

        class DivisionZero : public std::exception
		{
			public: virtual const char* what() const throw();
		};
        class NumberFormat : public std::exception
		{
			public: virtual const char* what() const throw();
		};
        class OperandsError : public std::exception
		{
			public: virtual const char* what() const throw();
		};
};

#endif
