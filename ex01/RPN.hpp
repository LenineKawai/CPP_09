/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:29:57 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/11 16:16:24 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <iostream>
#include <string>

# define RESET   "\033[0;0m"
# define ERASE   "\033[2K\r"
# define GREY    "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define PINK    "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"
# define BOLD    "\033[1m"
# define UNDER   "\033[4m"
# define SUR     "\033[7m"
# define END     "\033[0m"
# define CENTER  "\033[60G"

# define OPER_CHARSET "+-/*"
# define NB_CHARSET "0123456789"

class RPN
{
    private:
        std::string         _input;
        std::stack< float >   _stack;
        
        RPN();
        
    public:
        RPN(const std::string &input);
        RPN(const RPN &rpn);
        ~RPN();

        RPN &operator=(const RPN &rpn);

        void    checkInput(const std::string &input);
        void    compute();
    
    class badInput : public std::exception
    {
        public:
            const std::string bad() const throw();
    };
    
};



#endif