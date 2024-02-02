/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/02 10:12:15 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <iostream>
#include <stack>
#include <sstream>

void    eval(const std::string& expression)
{
    std::stack<int>         st;
    std::istringstream      iss(expression);
    std::string             c;

    while (iss >> c) {
        if (c == "+" || c == "-" || c == "*" || c == "/") {
            if (st.size() < 2)
            {
                std::cerr << "Error: Insufficient operands for operator " << c << std::endl;
                return ;
            }

            int operand2 = st.top();
            st.pop();

            int operand1 = st.top();
            st.pop();

            int result;
            if (c == "+")
                result = operand1 + operand2;
            else if (c == "-")
                result = operand1 - operand2;
            else if (c == "*")
                result = operand1 * operand2;
            else if (c == "/") {
                if (operand2 == 0)
                {
                    std::cerr << "Error: Division by zero" << std::endl;
                    return ;
                }
                result = operand1 / operand2;
            }

            st.push(result);
        }
        else
        {
            int number;
            std::istringstream(c) >> number;
            st.push(number);
        }
    }

    if (st.size() == 1)
        std::cout << st.top() << std::endl;
    else
        std::cerr << "Error: Invalid expression" << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: .\\" << argv[0] << " \"RPN expression\"" << std::endl;
        std::cerr << "Example: .\\" << argv[0] << " \"8 9 * 9 - 9 - 9 - 4 - 1 +\"" << std::endl;
        return 1;
    }

    eval(std::string(argv[1]));
    return 0;
}
