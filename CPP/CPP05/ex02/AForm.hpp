/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AForm.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/28 15:41:58 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include "Bureaucrat.hpp"

class Bureaucrat;

class AForm
{
	protected:
		std::string	name;
		std::string	target;
		bool		sign;
		int		sign_grade;
		int		exec_grade;
		void		beExecuted() const;
		AForm();
	public:
		AForm(const AForm&);
		AForm &operator=(const AForm& op);
		AForm(const std::string, int, int);
		virtual ~AForm();

		std::string	getName( void ) const;
		bool		getSign( void ) const;
		int		getSignGrade( void ) const;
		int		getExecGrade( void ) const;

		void		beSigned( Bureaucrat& );
		void		setSign( void );
		void		execute(Bureaucrat const & executor) const;

		class GradeTooHighException : public std::exception
		{
			public: virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception
		{
			public: virtual const char* what() const throw();
		};
};

std::ostream&   operator<<(std::ostream&, const AForm&);

#endif
