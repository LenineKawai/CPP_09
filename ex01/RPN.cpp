/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:29:54 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/02 17:54:07 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool    isCharset(char c, std::string charset)
{
    size_t size = charset.size();
    for (size_t i = 0; i < size; i ++)
        if (c == charset[i])
            return (true);
    return (false);
}

RPN::RPN()
{
    // std::cout << GREEN << "Default constructor" << END << std::endl;
}

RPN::RPN(const std::string &input)
{
    // std::cout << BLUE << "constructor" << END <<  std::endl;
    checkInput(input);
    _input = input;
}

RPN::RPN(const RPN &rpn)
{
    // std::cout << YELLOW << "copy constructor" << END << std::endl;
    *this = rpn;
}

RPN &RPN::operator=(const RPN &rpn)
{
    this->_stack = rpn._stack;
    this->_input = rpn._input;
    return (*this);
}

RPN::~RPN()
{
    // std::cout << RED << "DESTRUCTED" << END << std::endl;
}

/******** MEMBER FUNCTIONS ********/

void    RPN::checkInput(const std::string &input)
{
    size_t i = 0;
    size_t size = input.size();

    if (size == 0)
            throw (badInput()); 
    while (i < size)
    {
        while (i < size && input[i] == ' ')
            i ++;
        if ((i < size) 
        && (isCharset(input[i], NB_CHARSET) == false && isCharset(input[i], OPER_CHARSET) == false))
            throw (badInput()); 
        i ++;
    }
}

int     oper(char c, int first, int second)
{
    switch (c)
    {
        case '-':
            return (first - second);
        case '+':
            return (first + second);
        case '*':
            return (first * second);
        case '/':
            return (first / second);
        default:
            return(0);
    }
}

void    RPN::compute()
{
    size_t i = 0;
    size_t size = _input.size();
    int    tmp;
    
    while (i < size)
    {
        while (_input[i] == ' ')
            i ++;
        if (i < size && isCharset(_input[i], NB_CHARSET))
            _stack.push(_input[i] - 48);
        else if (i < size)
        {
            if (_stack.size() < 2)
            {
                std::cerr << BOLD << RED << "incomputable input : "
                "there is less than 2 numbers in the stack when an operator is called" << END << std::endl; 
                return ;
            }
            else
            {
                tmp = _stack.top();
                _stack.pop();
                tmp = oper(_input[i], _stack.top(), tmp); 
                _stack.pop();
                _stack.push(tmp);
            }
        }
        i ++;
    }
    if (_stack.size() > 1)
        std::cerr << BOLD << RED << "computation failed, there seems to be to few operands" << END << std::endl;
    else
        std::cout << BOLD << "computation result for '" << YELLOW << _input << WHITE << "' :" << std::endl
        << GREEN << _stack.top() << END << std::endl;
}

const std::string   RPN::badInput::bad() const throw()
{
    return ("bad input");
}

