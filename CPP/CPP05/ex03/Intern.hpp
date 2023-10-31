/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Intern.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/31 09:03:38 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERN_HPP
# define INTERN_HPP

# include <iostream>
# include "Bureaucrat.hpp"

class Bureaucrat;

class Intern
{
	public:
		Intern(const Intern&);
		Intern &operator=(const Intern& op);
		Intern(const std::string, int, int);
		virtual ~Intern();

		makeForm
};

std::ostream&   operator<<(std::ostream&, const Intern&);

#endif
