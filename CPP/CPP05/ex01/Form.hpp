/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/18 08:19:28 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# define MAX_GRADE 1
# define MIN_GRADE 150

#include <iostream>

class Bureaucrat
{
	private:
		std::string	name;
		bool		sign;
		int		min_grade;
		int		max_grade;
	public:
		Bureaucrat();
		Bureaucrat(const Bureaucrat&);
		Bureaucrat &operator=(const Bureaucrat& op);
		Bureaucrat(const std::string, int);
		virtual ~Bureaucrat();

		std::string	getName( void ) const;
		int		getGrade( void ) const;

		void		upGrade( void );
		void		downGrade( void );

		class GradeTooHighException : public std::exception
		{
			public: virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception
		{
			public: virtual const char* what() const throw();
		};
};

std::ostream&   operator<<(std::ostream&, const Bureaucrat&);

#endif
