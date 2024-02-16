/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/16 10:11:54 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>

#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

void    RPN::eval(const std::string& expression)
{
    std::stack<int>         st;
    std::istringstream      iss(expression);
    std::string             tk;

    while (iss >> tk) {
        if (tk == "+" || tk == "-" || tk == "*" || tk == "/") {
            if (st.size() < 2)
            {
                std::cerr << "Error: Insufficient operands for operator " << tk << std::endl;
                return ;
            }

            int op2 = st.top();
            st.pop();

            int op1 = st.top();
            st.pop();

            int r;
            if (tk == "+")
                r = op1 + op2;
            else if (tk == "-")
                r = op1 - op2;
            else if (tk == "*")
                r = op1 * op2;
            else if (tk == "/") {
                if (op2 == 0)
                {
                    std::cerr << "Error: Division by zero" << std::endl;
                    return ;
                }
                r = op1 / op2;
            }

            st.push(r);
        }
        else
        {
            if (tk.size() > 1)
            {
                std::cerr << "Error: Number too long: " << tk << std::endl;
                return ;
            }
            if (!std::isdigit(tk[0]))
            {
                std::cerr << "Error: Not a number" << std::endl;
                return ;
            }
            int number;
            std::istringstream(tk) >> number;
            st.push(number);
        }
    }

    if (st.size() == 1)
        std::cout << st.top() << std::endl;
    else
        std::cerr << "Error: Invalid expression" << std::endl;
}

const char* RPN::DivisionZero::what() const throw() { return ("Error: Division by zero."); }
const char* RPN::NumberFormat::what() const throw() { return ("Error: Number format."); }
