/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/03 11:19:52 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERT_HPP
# define CONVERT_HPP

#include <iostream>
#include <stdlib.h>
//#include <string>
//#include <limits>
//#include <fstream>

class Convert
{
	public:
		Convert();
		Convert(const Convert&);
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
