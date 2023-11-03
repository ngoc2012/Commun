/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Convert.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/03 11:16:53 by ngoc             ###   ########.fr       */
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

		void	getChar( std::string );
		void	getInt( std::string );
		void	getFloat( std::string );
		void	getDouble( std::string );

		class	ConvertException: public std::exception {
			virtual const char* what() const throw() { return "Unknown type"; }
		};
};

#endif
