/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/04 15:21:10 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
# define CONVERT_HPP

#include <iostream>
#include <stdlib.h>	// atof
#include <limits>	// numeric_limits
#include <sstream>	// istringstream
#include <cstring>	// strlen

enum	e_types {CHAR, INT, FLOAT, DOUBLE};

class Convert
{
	private:
		e_types	type;
		std::string	_char;
		std::string	_int;
		std::string	_float;
		std::string	_double;
		Convert();
		Convert(const Convert&);
	public:
		Convert(char *);
		Convert &operator=(const Convert& op);
		virtual ~Convert();

		void	setChar();
		void	setInt();
		void	setFloat();
		void	setDouble();
		std::string	getChar();
		std::string	getInt();
		std::string	getFloat();
		std::string	getDouble();

		class	ConvertException: public std::exception {
			virtual const char* what() const throw() { return "Unknown type"; }
		};
};

#endif
