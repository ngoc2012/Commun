/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/04 15:18:29 by ngoc             ###   ########.fr       */
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
		Convert();
		Convert(const Convert&);
	public:
		Convert(char *);
		Convert &operator=(const Convert& op);
		virtual ~Convert();

		void	getChar( char* );
		void	getInt( char* );
		void	getFloat( char* );
		void	getDouble( char* );

		class	ConvertException: public std::exception {
			virtual const char* what() const throw() { return "Unknown type"; }
		};
};

#endif
