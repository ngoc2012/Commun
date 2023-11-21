/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Serializer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 17:59:44 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERIALIZER_HPP
# define SERIALIZER_HPP

#include <iostream>
#include <stdlib.h>	// atof
#include <limits>	// numeric_limits
#include <sstream>	// istringstream
#include <cstring>	// strlen
#include <cfloat>	// DLB_MAX
#include <cerrno>	// errno

# define DBL_TRUE_MIN std::numeric_limits<double>::min()

enum	e_types {NONE, CHAR, INT, FLOAT, DOUBLE};

class Convert
{
	private:
		e_types		type;
		char		_char;
		int		_int;
		float		_float;
		double		_double;
		//long double	_ldouble;

		Convert();
		Convert(const Convert&);
	public:
		Convert(char *);
		Convert &operator=(const Convert& op);
		virtual ~Convert();

		void	get_str(char *);
		void	get_char();
		void	get_int(char *);
		void	get_float(char *);
		void	get_double(char *);
};

#endif
