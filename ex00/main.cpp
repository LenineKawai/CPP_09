/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:20:28 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/11 15:47:59 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


int main(int ac, char **av)
{
    std::map < std::string, double > course;
    std::ifstream db("data.csv");

    if (ac != 2)
    {
        std::cerr << "This program only take one argument : a relativ or absolute path to an input file." << std::endl;
        return (1);
    }

    std::ifstream infile(av[1]);

    if (infile.good() && db.good() && infile)
    {
        fillMap(db, course);
        writeOutput(infile, course);
    }

    else
    {
        std::cerr << "access to specified files was denied, they may not exist, be a directoy, or reading rights might be restricted" << std::endl;
        return (1);
    }


    
    return (0);
}