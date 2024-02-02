/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoc <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 19:17:48 by ngoc              #+#    #+#             */
/*   Updated: 2024/02/02 09:55:13 by ngoc             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <iostream>
#include <stack>
#include <sstream>

int evaluateRPN(const std::string& expression) {
    std::stack<int> stack;

    std::istringstream iss(expression);
    std::string token;

    while (iss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.size() < 2) {
                std::cerr << "Error: Insufficient operands for operator " << token << std::endl;
                return -1;
            }

            int operand2 = stack.top();
            stack.pop();

            int operand1 = stack.top();
            stack.pop();

            int result;
            if (token == "+")
                result = operand1 + operand2;
            else if (token == "-")
                result = operand1 - operand2;
            else if (token == "*")
                result = operand1 * operand2;
            else if (token == "/") {
                if (operand2 == 0) {
                    std::cerr << "Error: Division by zero" << std::endl;
                    return -1;
                }
                result = operand1 / operand2;
            }

            stack.push(result);
        } else {
            int number;
            std::istringstream(token) >> number;
            stack.push(number);
        }
    }

    if (stack.size() == 1) {
        return stack.top();
    } else {
        std::cerr << "Error: Invalid expression" << std::endl;
        return -1;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " \"RPN expression\"" << std::endl;
        return 1;
    }

    std::string rpnExpression = argv[1];
    int result = evaluateRPN(rpnExpression);

    if (result != -1) {
        std::cout << result << std::endl;
    }

    return 0;
}
