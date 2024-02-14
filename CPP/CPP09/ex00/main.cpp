/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/02 10:24:09 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <sstream>
#include <cctype>

void    eval(const std::string& expression)
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
                std::cerr << "Error: Number too long" << std::endl;
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
