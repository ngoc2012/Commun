/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/18 07:24:18 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>

class Bureaucrat
{
	protected:
		std::string	type;
	public:
		Bureaucrat();
		Bureaucrat(const Bureaucrat&);
		Bureaucrat &operator=(const Bureaucrat& op);
		virtual ~Bureaucrat();

		std::string	getName( void ) const;
		int		getGrade( void ) const;

		class GradeTooHighException : public std::exception
		{
			virtual const char* what() const throw();
		};
};

std::ostream&   operator<<(std::ostream&, const Bureaucrat&);

#endif
