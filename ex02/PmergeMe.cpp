/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:24:55 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/10 17:08:40 by mgolinva         ###   ########.fr       */
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
    if (checkInput() == false)
        throw(PmergeMe::badInput());
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

    for (size_t i = 0; i < size; i++)
    {
        if (isCharset(_input[i], CHARSET) == false)
            return (false);
    }
    return (true);
}

bool    PmergeMe::fillVec()
{
    unsigned int    tmp;
    std::string     *split;

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
    }
    delete[] split;
    return (true);
}

bool    PmergeMe::fillLst()
{
    unsigned int    tmp;
    std::string     *split;

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
        _list.push_back(tmp);
    }
    delete[] split;
    return (true);
}

std::vector<unsigned int> PmergeMe::mergesortVec(std::vector<unsigned int> vec1, std::vector<unsigned int> vec2)
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

    return (newVec);
}

std::vector<unsigned int>    PmergeMe::mergeVec(std::vector<unsigned int> &vec)
{
    std::vector< unsigned int > vec1;
    std::vector< unsigned int > vec2;
    std::vector< unsigned int > sortedVec;
    size_t size = vec.size();
    size_t middle;

    size % 2 ? middle = size / 2 : middle = size / 2 + 1;

    if (vec.size() > _mergeLimit)
    {
        for (size_t i = 0; i < middle; i++)
            vec1.push_back(vec[i]);
        for (size_t i = middle; i < vec.size(); i++)
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
    unsigned int    tmp = 0;
    size_t          j = 0;
    size_t          i = 0;

    // for (std::vector< unsigned int >::iterator it = vec.begin(); it != vec.end(); it++)
    //     std::cout << RED << *it << END <<  " ";
    if (size <= 1)
        return ;
    while( i < size)
    {
        j = i + 1;
        while (j > 0 && j < size && vec[j] < vec[j - 1])
        {
            tmp = vec[j];
            vec[j] = vec[j - 1];
            vec[j - 1] = tmp;
            j --;
        }
        i ++;
    }
    // for (std::vector< unsigned int >::iterator it = vec.begin(); it != vec.end(); it++)
    //     std::cout << GREEN << *it << END <<  " ";
    // std::cout << std::endl;
}

void    PmergeMe::sortVec()
{
    struct timeval  Tstart;
    struct timeval  Tend;
    double          tmp = 0;

    gettimeofday(&Tstart, 0);

    if (fillVec() == false)
        throw(PmergeMe::badInput());

   _vector = mergeVec(_vector);

    gettimeofday(&Tend, 0);

    _vecTime = static_cast<double>(Tend.tv_sec - Tstart.tv_sec);
    if (Tend.tv_sec == Tstart.tv_sec + 1 && (1000000 - Tend.tv_usec) + Tstart.tv_usec >= 1000000)
        _vecTime = 0;
    if (Tend.tv_sec > Tstart.tv_sec)
    {
        tmp = ((1000000 - Tstart.tv_usec) + Tend.tv_usec );
        _vecTime += tmp / 1000000;
    }
    else
    {
        tmp = (Tend.tv_usec - Tstart.tv_usec);
        _vecTime += tmp / 1000000;
    }
}

std::list<unsigned int> PmergeMe::mergesortLst(std::list<unsigned int> lst1, std::list<unsigned int> lst2)
{
    std::list< unsigned int > newLst;
    
    while (lst1.empty() == false && lst2.empty() == false)
    {
        if (lst1.front() <= lst2.front())
        {
            newLst.push_back(lst1.front());
            lst1.erase(lst1.begin());
        }
        else if (lst2.front() < lst1.front())
        {
            newLst.push_back(lst2.front());
            lst2.erase(lst2.begin());
        }
    }
    if (lst1.empty() == false)
        newLst.insert(newLst.end(), lst1.begin(), lst1.end());
    if (lst2.empty() == false)
        newLst.insert(newLst.end(), lst2.begin(), lst2.end());

    return (newLst);
}

std::list<unsigned int>    PmergeMe::mergeLst(std::list<unsigned int> &lst)
{
    std::list< unsigned int > lst1;
    std::list< unsigned int > lst2;
    std::list< unsigned int >::iterator it = lst.begin();
    std::list< unsigned int >::iterator end = lst.end();
    std::list< unsigned int > sortedlst;
    size_t size = lst.size();
    size_t middle;

    size % 2 ? middle = size / 2 : middle = size / 2 + 1;

    if (lst.size() > _mergeLimit)
    {
        for (size_t i = 0; i < middle && it != end; i++, it ++)
            lst1.push_back(*it);
        for (size_t i = middle; i < lst.size() && it != end; i++, it ++)
            lst2.push_back(*it);
        mergeLst(lst1);
        mergeLst(lst2);
        lst = mergesortLst(lst1, lst2);
    }
    else
        insertLst(lst);
    return (lst);
}

void    PmergeMe::insertLst(std::list<unsigned int> &lst)
{
    unsigned int tmp;
    std::list<unsigned int>::iterator j;
    std::list<unsigned int>::iterator i = lst.begin();
    std::list<unsigned int>::iterator end = lst.end();
    std::list<unsigned int>::iterator next;

    if (lst.size() <= 1)
        return;
    ++i;
    // for (std::list< unsigned int >::iterator it = lst.begin(); it != lst.end(); it++)
    //     std::cout << RED << *it << END <<  " ";
    while (i != end)
    {
        j = i;
        --j;
        tmp = *i;
        while (j != end && *j > tmp)
        {
            next = j;
            ++next;
            *next = *j;
            --j;
        }
        next = j;
        ++next;
        *next = tmp;
        ++i;
    }
    // for (std::list< unsigned int >::iterator it = lst.begin(); it != lst.end(); it++)
    //     std::cout << GREEN << *it << END <<  " ";
    // std::cout << std::endl;
}

void    PmergeMe::sortLst()
{
    struct timeval Tstart;
    struct timeval Tend;
    double tmp;

    gettimeofday(&Tstart, 0);

    if (fillLst() == false)
        throw(PmergeMe::badInput());

    _list = mergeLst(_list);

    gettimeofday(&Tend, 0);

    _lstTime = static_cast<double>(Tend.tv_sec - Tstart.tv_sec);
    if (Tend.tv_sec == Tstart.tv_sec + 1 && (1000000 - Tend.tv_usec) + Tstart.tv_usec >= 1000000)
        _lstTime = 0;
    if (Tend.tv_sec > Tstart.tv_sec)
    {
        tmp = ((1000000 - Tstart.tv_usec) + Tend.tv_usec );
        _lstTime += tmp / 1000000;
    }
    else
    {
        tmp = (Tend.tv_usec - Tstart.tv_usec);
        _lstTime += tmp / 1000000;
    }
}

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

void    PmergeMe::getTimeVec() const
{
   std::cout << BOLD << "time to process a range of " << _vector.size() << " elements with std::vector : "
   << RED << _vecTime << " s" <<END << std::endl;
}
void    PmergeMe::getTimeLst() const
{
    std::cout << BOLD << "time to process a range of " << _list.size() << " elements with std::list : "
    << RED << _lstTime << " s" END << std::endl;
}

