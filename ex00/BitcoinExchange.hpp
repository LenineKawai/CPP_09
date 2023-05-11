/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:39:30 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/11 10:54:44 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

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

#include <map>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>

void    fillMap(std::ifstream &db, std::map< std::string, double > &map);
void    writeOutput(std::ifstream &infile, std::map< std::string, double > &map);


typedef struct s_date
{
    int     year;
    int     month;
    int     day;
    bool    validity;
}   t_date;

#endif