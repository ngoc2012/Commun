/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/28 11:27:49 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
	private:
		std::string	name;
		bool		sign;
		int		sign_grade;
		int		exec_grade;
		Form();
	public:
		Form(const Form&);
		Form &operator=(const Form& op);
		Form(const std::string, int, int);
		virtual ~Form();

		std::string	getName( void ) const;
		bool		getSign( void ) const;
		int		getSignGrade( void ) const;
		int		getExecGrade( void ) const;

		void		beSigned( Bureaucrat& );
		void		setSign( void );

		class GradeTooHighException : public std::exception
		{
			public: virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception
		{
			public: virtual const char* what() const throw();
		};
};

std::ostream&   operator<<(std::ostream&, const Form&);

#endif
