/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/16 09:35:04 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

#include <iostream>
#include <list>

class RPN
{
	private:
		RPN();
		RPN(const RPN&);
		RPN	&operator=(const RPN& op);
	public:
		RPN(const char *);
		virtual ~RPN();

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
