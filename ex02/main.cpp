/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:19:11 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/11 13:58:46 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    std::string input;

    if (ac < 2)
    {
        std::cerr << "No args given" << std::endl;
        return (1);
    }

    for (int i = 1; i < ac; i ++)
    {
        if (av[i][0] == 0)
            ;
        else
        {
            input.append(av[i]);
            if (i < ac - 1)
                input.append(" ");
        }
    }
    
    try
    {
        PmergeMe exonul(input);
        std::cout << "Before : ";
        exonul.printInput();
        exonul.sortVec();
        exonul.sortLst();
        std::cout << "After : ";
        exonul.printLst();
        std::cout << "aFtEr : ";
        exonul.printVec();
        exonul.getTimeVec();
        exonul.getTimeLst();
    }
    catch(const PmergeMe::badInput& e)
    {
        std::cerr << e.msg() << '\n';
        return (1);
    }
    return (0);
}