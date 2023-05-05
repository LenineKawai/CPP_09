/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:24:55 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/05 17:54:03 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

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
        return (strArray);
    }
    catch (std::bad_alloc &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return (0);
    }
    return (0);
}

PmergeMe::PmergeMe(const std::string &input)
{
    // std::cout << BOLD << input << END << std::endl;
    _input = input;
    if (checkInput() == false || fillContainers() == false)
        throw(PmergeMe::badInput());
    if (_vector.size() < MERGE_LIMIT)
        _mergeLimit = _vector.size() / 2;
    else
        _mergeLimit = MERGE_LIMIT;
}

PmergeMe::PmergeMe(const PmergeMe &cp)
{
    *this = cp;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &cp)
{
    this->_input = cp._input;
    this->_vector = cp._vector;
    this->_list = cp._list;
    return (*this);
}

// std::string &PmergeMe::operator<<(PmergeMe &cp)
// {
//     std::vector< unsigned int >::iterator vIt = cp._vector.begin();
//     std::vector< unsigned int >::iterator vEnd = cp._vector.end();

//     std::string *str = NULL;

//     *str = "";

//     *str + "vector :\n";

//     if (cp._vector.empty())
//     {
//         for (;vIt != vEnd; vIt ++)
//             *str += *vIt + " ";
//         *str + "\r\n";
//     }

//     *str + "list :\n";

//     std::list< unsigned int >::iterator lIt = cp._list.begin();
//     std::list< unsigned int >::iterator lEnd = cp._list.end();
//     if (cp._list.empty())
//     {
//         for (;lIt != lEnd; lIt ++)
//             *str += *lIt + " ";
//         *str + "\r\n";
//     }

//     return (*str);
// }

PmergeMe::~PmergeMe()
{
    _input.clear();
    _vector.clear();
    _list.clear();
}

/******** MEMBER FUNCTIONS ********/

bool    PmergeMe::checkInput()
{
    size_t  size = _input.size();

    std::cout << _input.size() << std::endl;
    
    for (size_t i = 0; i < size; i++)
    {
        if (isCharset(_input[i], CHARSET) == false)
            return (false);
    }
    return (true);
}

bool    PmergeMe::fillContainers()
{
    unsigned int    tmp;
    std::string     *split;

    // std::cout << RED << _input << END << std::endl;
    split = cppsplit(_input, ' ');
    for(size_t i = 0;  split[i][0] != 0; i++)
    {
        tmp = std::atol(split[i].c_str());
        if (errno == ERANGE)
        {
            errno = 0;
            delete[] split;
            return (false);
        }
        _vector.push_back(tmp);
        _list.push_back(tmp);
    }
    delete[] split;
    return (true);
}

std::vector<unsigned int> mergesortVec(std::vector<unsigned int> vec1, std::vector<unsigned int> vec2)
{
    std::vector< unsigned int > newVec;
    
    while (vec1.empty() == false && vec2.empty() == false)
    {
        if (vec1.front() <= vec2.front())
        {
            newVec.push_back(vec1.front());
            vec1.erase(vec1.begin());
        }
        else if (vec2.front() < vec1.front())
        {
            newVec.push_back(vec2.front());
            vec2.erase(vec2.begin());
        }
    }
    if (vec1.empty() == false)
        newVec.insert(newVec.end(), vec1.begin(), vec1.end());
    if (vec2.empty() == false)
        newVec.insert(newVec.end(), vec2.begin(), vec2.end());
    
    size_t size2 = newVec.size();

    for (size_t i = 0; i < size2; i ++)
        std::cout << BOLD << GREEN << newVec[i] << " ";
    std::cout << END << std::endl;

    return (newVec);
}

std::vector<unsigned int>    PmergeMe::mergeVec(std::vector<unsigned int> &vec)
{
    std::vector< unsigned int > vec1;
    std::vector< unsigned int > vec2;
    std::vector< unsigned int > sortedVec;


    if (vec.size() > _mergeLimit)
    {
        for (size_t i = 0; i < vec.size() / 2; i++)
            vec1.push_back(vec[i]);
        for (size_t i = vec.size() / 2 + 1; i < vec.size(); i++)
            vec2.push_back(vec[i]);
        mergeVec(vec1);
        mergeVec(vec2);
        vec = mergesortVec(vec1, vec2);
    }
    else
        insertVec(vec);
    return (vec);
}

void    PmergeMe::insertVec(std::vector<unsigned int> &vec)
{
    size_t          size = vec.size();
    unsigned int    tmp;
    size_t j;

    for (size_t i = 0; i < size; i ++)
    {
        for (j = i; j > 0 && vec[j - 1] > vec[j]; j --)
        {
            tmp = vec[j];
            vec[j] = vec[j - 1];
            vec[j - 1] = tmp;
        }
        i = j + 1;
    }
    size_t size2 = vec.size();

    for (size_t i = 0; i < size2; i ++)
        std::cout << BOLD << CYAN << vec[i] << " ";
    std::cout << END << std::endl;
}



void    PmergeMe::sortVec()
{
    // std::cout << _mergeLimit << std::endl;
    
   _vector = mergeVec(_vector);
}
// void    PmergeMe::sortLst()
// {

// }

const std::string   PmergeMe::badInput::msg() const throw()
{
    return ("non numerical input");
}


/*** PRINT ***/

void    PmergeMe::printInput()    const {std::cout << BOLD << _input << END << std::endl;}

void    PmergeMe::printVec()      const
{
    size_t size = _vector.size();

    for (size_t i = 0; i < size; i ++)
        std::cout << BOLD << YELLOW << _vector[i] << " ";
    std::cout << END << std::endl;
}
void    PmergeMe::printLst()
{
    std::list< unsigned int >::iterator end = _list.end();

    for (std::list< unsigned int >::iterator it = _list.begin(); it != end; it ++)
        std::cout << BOLD << BLUE << *it << " ";
    std::cout << END << std::endl;
}

