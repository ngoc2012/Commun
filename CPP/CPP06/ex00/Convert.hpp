/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/13 10:08:09 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
# define CONVERT_HPP

#include <iostream>
#include <stdlib.h>	// atof
#include <limits>	// numeric_limits
#include <sstream>	// istringstream
#include <cstring>	// strlen

enum	e_types {NONE, CHAR, INT, FLOAT, DOUBLE};

class Convert
{
	private:
		e_types		type;
		char		_char;
		int		_int;
		float		_float;
		double		_double;
		std::string	_s_char;
		std::string	_s_int;
		std::string	_s_float;
		std::string	_s_double;

		Convert();
		Convert(const Convert&);
	public:
		Convert(char *);
		Convert &operator=(const Convert& op);
		virtual ~Convert();

		void	get_str(char *);
		void	get_char();
		void	get_int(char *);
		/*
		void	setChar();
		void	setInt();
		void	setFloat();
		void	setDouble();
		std::string	getChar();
		std::string	getInt();
		std::string	getFloat();
		std::string	getDouble();
		*/
};

#endif
