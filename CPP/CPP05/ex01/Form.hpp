/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Form.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/10/18 08:23:51 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORM_HPP
# define FORM_HPP

# define MAX_GRADE 1
# define MIN_GRADE 150

# include <iostream>
# include "Bureaucrat.hpp"

class Form
{
	private:
		std::string	name;
		bool		sign;
		int		min_grade;
		int		max_grade;
	public:
		Form();
		Form(const Form&);
		Form &operator=(const Form& op);
		Form(const std::string, int, int);
		virtual ~Form();

		std::string	getName( void ) const;
		bool		getSign( void ) const;
		int		getMinGrade( void ) const;
		int		getMaxGrade( void ) const;

		void		beSigned( void );

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
