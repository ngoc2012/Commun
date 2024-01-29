/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Base.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:50:42 by ngoc              #+#    #+#             */
/*   Updated: 2023/11/21 19:12:37 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_HPP
# define BASE_HPP

class Base
{
	private:
		Base(const Base&);
		Base	&operator=(const Base& op);
	public:
		Base();
		virtual ~Base();

		Base*	generate(void);
		void	identify(Base* b);
		void	identify(Base& b);
};

class A: public Base {};
class B: public Base {};
class C: public Base {};

#endif
