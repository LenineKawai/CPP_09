/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:29:54 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/11 16:19:28 by mgolinva         ###   ########.fr       */
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
    ;
}

RPN::RPN(const std::string &input)
{
    checkInput(input);
    _input = input;
}

RPN::RPN(const RPN &rpn)
{
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
    ;
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
        if (i == size)
            throw(badInput());
        if ((i < size) 
        && (isCharset(input[i], NB_CHARSET) == false && isCharset(input[i], OPER_CHARSET) == false))
            throw (badInput()); 
        i ++;
    }
}

float     oper(char c, float first, float second)
{
    switch (c)
    {
        case '-':
            return (second - first);
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
    float  tmp;
    
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
                std::cout << BOLD << RED << "incomputable input : "
                "there is less than 2 numbers in the stack when an operator is called" << END << std::endl; 
                return ;
            }
            else if (_input[i] == '/' && _stack.top() == 0)
            {
                std::cout << BOLD << RED << "incomputable input : "
                << "there is a division by zero occurence that leads to undefined behaviours" << END << std::endl;
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
        std::cout << BOLD << RED << "computation failed, there seems to be too few operators" << END << std::endl;
    else
        std::cout << BOLD << "computation result for '" << YELLOW << _input << WHITE << "' :" << std::endl
        << GREEN << _stack.top() << END << std::endl;
}

const std::string   RPN::badInput::bad() const throw()
{
    return ("bad input");
}

