/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 10:30:00 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/02 17:46:12 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int ac, char **av)
{

    if (ac != 2)
    {
        std::cerr << "this program only take one argument, a list of numbers more or equal to zero and less than 10 and operators such as:\n"
        << "'8 9 * 9 - 9 - 9 - 4 - 1' + or '89*9-9-9-4-1'+" << std::endl;
        return (1);
    }
    std::string input(av[1]);

    try
    {
        RPN rpn(input);
        rpn.compute();
    }
    catch(RPN::badInput &e)
    {
        std::cerr << RED << BOLD << "Error :" << e.bad() << END << std::endl;
    }

    return (0);
}