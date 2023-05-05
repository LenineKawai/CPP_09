/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:19:11 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/05 17:49:51 by mgolinva         ###   ########.fr       */
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
        exonul.sortVec();
        exonul.printVec();
    }
    catch(const PmergeMe::badInput& e)
    {
        std::cerr << e.msg() << '\n';
    }
}