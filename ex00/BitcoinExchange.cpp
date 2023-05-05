/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 10:39:41 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/03 09:39:14 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#define DATE_CHARSET    "0123456789"
#define VALUE_CHARSET   "0123456789., "

bool    isCharset(char c, std::string charset)
{
    size_t size = charset.size();
    for (size_t i = 0; i < size; i ++)
        if (c == charset[i])
            return (true);
    return (false);
}

std::string *cppsplit(std::string str, char sep)
{
    int         wordCT = 1;
    int         strSize = str.size();
    std::string *strArray;
    
    for (int i = 0; i < strSize; i ++)
    {
        if (str[i] == sep && i != strSize - 1 && i != 0)
        {
            wordCT ++;
            i ++;
        } 
        while (str[i] && str[i] == sep)
            i ++;
    }
    try
    {
        strArray = new std::string[wordCT + 1];

        int i = 0;
        int j = 0;

        while (i < wordCT)
        {
            while (str[j] == sep)
                j ++;
            while(str[j] && str[j] != sep)
            {
                strArray[i].push_back(str[j]);
                j ++;
            }
            i ++;
        }
        if (wordCT != 3)
        {
            delete[] strArray;
            return (0);
        }
        return (strArray);
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return (0);
    }
    return (0);
}

t_date buildDate(std::string dateStr)
{
    t_date date;

    date.validity = true;
    std::string *dateSplit = cppsplit(dateStr, '-');
    if (dateSplit == NULL)
    {
        date.validity = false;
        return (date);
    }
    date.year   = std::atoi(dateSplit[0].c_str());
    date.month  = std::atoi(dateSplit[1].c_str());
    date.day    = std::atoi(dateSplit[2].c_str());
    if (errno == ERANGE)
    {
        date.validity = false;
        errno = 0;
        delete[] dateSplit;
        return (date);
    }

    if (date.month <= 12)
    {
        if (date.month == 2 && date.year % 4 == 0 && date.day > 29)
            date.validity = false ;
        else if (date.month == 2 && date.year % 4 != 0 && date.day > 28)
            date.validity = false;
        else if (date.month % 2 == 0 && date.month != 8 && date.day > 31)
            date.validity = false;
        else if (date.month % 2 != 0 && date.day > 30)
            date.validity = false ;
    }
    else
        date.validity = false;
    delete[] dateSplit;
    
    return (date);
}

bool    isFirstDateGreater(t_date first, t_date second)
{
    if (first.year < second.year)
        return (false);
    else if (first.year == second.year)
    {
        if (first.month > second.month)
            return (true);
        else if (first.month == second.month)
        {
            if (first.day > second.day)
                return (true);
            else
                return (false);
        }
        else
            return (false);
    }
    else
        return (true); 
}

bool    isFirstDateSmaller(t_date first, t_date second)
{
    if (first.year > second.year)
        return (false);
    else if (first.year == second.year)
    {
        if (first.month < second.month)
            return (true);
        else if (first.month == second.month)
        {
            if (first.day < second.day)
                return (true);
            else
                return (false);
        }
        else
            return (false);
    }
    else
        return (true); 
}


bool   checkDate(std::map< std::string, double > &map, std::string date, int lineCT)
{
    size_t  i           = 0;
    size_t  size        = date.size();
    t_date  dateStruct  = buildDate(date);
    t_date  dbStart     = buildDate(map.begin()->first);
    t_date  dbEnd       = buildDate(map.rbegin()->first);
    
    if (dateStruct.validity == false)
    {
        std::cerr << "Invalid date :" << RED << BOLD << " line " << lineCT << END <<" => ' " << date << " '" << std::endl;
        return (false);
    }

    while (i < size)
    {
        if (date[i] == '-')
            i ++;
        if (i < size && isCharset(date[i], DATE_CHARSET) == false)
        {
            std::cerr << "Invalid date format :" << RED << BOLD << " line " << lineCT << END " => ' " << date << " '" << std::endl;
            return (false);
        }
        i ++;
    }
    
    if (isFirstDateSmaller(dateStruct, dbStart) == true || isFirstDateGreater(dateStruct, dbEnd) == true)
    {
        std::cerr << "This date is outside of our database range : line " << RED << BOLD << " line " << lineCT << END " => ' " << date << " '" << std::endl;
        return (false);
    }
    return (true);
}

bool    checkValue(std::string val, int lineCT)
{
    size_t  i           = 0;
    size_t  size        = val.size();
    int     pointCT = 0;
    double  numVal;

    while (i < size)
    {
        if (size > 1 && i == 0 && (val[i] == '-' || val[i] == '+'))
            i ++;
        if (i < size && (val[i] == '.' || val[i] == ','))
            pointCT ++;
        if (i < size && (pointCT > 1 || isCharset(val[i], VALUE_CHARSET) == false))
        {
            std::cerr << "Invalid value :" << RED << BOLD << " line " << lineCT << END " => ' " << val << " '" << std::endl;
            return (false);
        }
        i ++;
    }
    numVal = std::atof(val.c_str());

    if (numVal <= 0)
    {
            std::cerr << "Invalid negativ or null value :" << RED << BOLD << " line " << lineCT << END " => ' " << numVal << " '" << std::endl;
            return (false);
    }
    if (numVal >= 1000)
    {
            std::cerr << "Value is too high :" << RED << BOLD << " line " << lineCT << END " => ' " << numVal << " '" << std::endl;
            return (false);
    }
    return (true);
}

bool    checkInputLine(std::map< std::string, double > &map, std::string &line, std::string *tmp_key, std::string *tmp_val)
{
    size_t          i = 0;
    size_t          size = line.size();
    static size_t   lineCT = 0;

    lineCT ++;

    if (line == "date | value")
        return (false);

    while (i < size)
    {
        while (i < size && line[i] != ' ' && line[i] != '|')
            i ++;
        *tmp_key = line.substr(0, i);

        if (checkDate(map, *tmp_key, lineCT) == false)
            return (false);

        while (i < size && line[i] == ' ')
            i ++;

        if (line[i] != '|')
        {
            std::cerr << "Invalid format :" << RED << BOLD << " line " << lineCT << END " => " << line << " // user yyyy-mm-dd | val format." << std::endl;
            return (false);
        }
        
        i ++;

        while (i < size && line[i] == ' ')
            i ++;
        
        if (i >= size)
        {
            std::cerr << "Invalid format :" << RED << BOLD << " line " << lineCT << END " => " << line << " // user yyyy-mm-dd | val format." << std::endl;
            return (false);
        }

        *tmp_val = line.substr(i, size - i);
        if (checkValue(*tmp_val, lineCT) == false)
            return (false);
        else
            return (true);
        i ++;
    }
    return (false);
}

void    fillMap(std::ifstream &db, std::map< std::string, double > &map)
{
    std::string line;
    std::string tmp_key;
    std::string tmp_val;
    
    std::getline(db, line);
    line.clear();
    while (db.eof() == false)
    {
        std::getline(db, line);
        for (size_t i = 0; i < line.size(); i ++)
        {
            if (line[i] == ',')
            {
                tmp_key = line.substr(0, i);
                tmp_val = line.substr(i + 1, line.size() - i);
                map.insert( std::pair< std::string, double >(tmp_key, std::atof(tmp_val.c_str())) );
                tmp_key.clear();
                tmp_val.clear();
            }
        }
        line.clear();
    }
}

void    writeOutput(std::ifstream &infile, std::map< std::string, double > &map)
{
    std::string line;
    std::string tmp_val;
    std::string tmp_key;
    
    while (infile.eof() == false)
    {
        std::getline(infile, line);
        if (checkInputLine(map, line, &tmp_key, &tmp_val) == true)
        {
            if (map.find(tmp_key) != map.end())
                std::cout << BOLD << std::atof(tmp_val.c_str()) << " BitCoins at the date of : " << BLUE << tmp_key << WHITE << " were worth : "
                << YELLOW << map.find(tmp_key)->second * std::atof(tmp_val.c_str()) << END << std::endl;
            else
            {
                std::map< std::string, double >::iterator it = map.lower_bound(tmp_key);
                it --;
                std::cout << BOLD <<std::atof(tmp_val.c_str()) << " BitCoins at the date of : " << BLUE << tmp_key << WHITE << " were worth : "
                << YELLOW << it->second * std::atof(tmp_val.c_str()) << END << std::endl;

            }
        }
        line.clear();
        tmp_key.clear();
        tmp_val.clear();
    }
}