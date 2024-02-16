/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:54:04 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/16 10:23:12 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>

#include "RPN.hpp"

RPN::RPN() {}

RPN::~RPN() {}

int    RPN::eval(const std::string& expression)
{
    std::stack<int>         st;
    std::istringstream      iss(expression);
    std::string             tk;

    while (iss >> tk) {
        if (tk == "+" || tk == "-" || tk == "*" || tk == "/") {
            if (st.size() < 2)
                throw RPN::OperandsError();
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
                    throw RPN::DivisionZero();
                r = op1 / op2;
            }
            st.push(r);
        }
        else
        {
            if (tk.size() > 1)
                throw RPN::NumberFormat();
            if (!std::isdigit(tk[0]))
                throw RPN::NumberFormat();
            int number;
            std::istringstream(tk) >> number;
            st.push(number);
        }
    }

    if (st.size() == 1)
        return (st.top());
    throw RPN::ExpressionError();
}

const char* RPN::DivisionZero::what() const throw() { return ("Error: Division by zero."); }
const char* RPN::NumberFormat::what() const throw() { return ("Error: Number format."); }
const char* RPN::OperandsError::what() const throw() { return ("Error: Operands."); }
const char* RPN::ExpressionError::what() const throw() { return ("Error: Invalid expression."); }
