/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:19:11 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/10 16:30:53 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    std::string input;

    for (int i = 1; i < ac; i ++)
    {
        input.append(av[i]);
        input.append(" ");
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
        // exonul.printVec();
        exonul.getTimeVec();
        exonul.getTimeLst();
    }
    catch(const PmergeMe::badInput& e)
    {
        std::cerr << e.msg() << '\n';
    }
}