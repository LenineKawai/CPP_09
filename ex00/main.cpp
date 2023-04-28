/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:20:28 by mgolinva          #+#    #+#             */
/*   Updated: 2023/04/28 15:11:38 by mgolinva         ###   ########.fr       */
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

    if (infile.good() && db.good())
    {
        fillMap(db, course);
        writeOutput(infile, course);
        // std::map< std::string, double >::iterator it = course.begin();
        // std::map< std::string, double >::iterator end = course.end();
        // std::cout << "course size : " << course.size() <<std::endl;
        // for (; it != end; it ++)
        // {
        //     std::cout << "key : " << it->first << " | val : " << it->second << std::endl;
        // }
        //parse input file
        
        //print results

    }

    else
    {
        std::cerr << "access to specified files was denied, they may not exist, be a directoy, or reading rights might be restricted" << std::endl;
        return (1);
    }


    
    return (0);
}