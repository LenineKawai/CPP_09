/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:18:32 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/10 16:44:24 by mgolinva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <cerrno>
#include <cstdlib>
#include <sys/time.h>
#include <iomanip>

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

# define CHARSET "0123456789 "
# define VECTOR 0
# define LIST 1
# define MERGE_LIMIT 31

class PmergeMe
{
private:
    PmergeMe();
    size_t                          _mergeLimit;
    std::string                     _input;
    std::vector < unsigned int >    _vector;
    std::list < unsigned int >      _list;
    double                          _vecTime;
    double                          _lstTime;

    std::vector<unsigned int>   mergesortVec(std::vector<unsigned int> vec1, std::vector<unsigned int> vec2);
    std::vector<unsigned int>   mergeVec(std::vector<unsigned int> &vec);
    void                        insertVec(std::vector<unsigned int> &vec);
    std::list<unsigned int>     mergesortLst(std::list<unsigned int> lst1, std::list<unsigned int> lst2);
    std::list<unsigned int>     mergeLst(std::list<unsigned int> &lst);
    void                        insertLst(std::list<unsigned int> &lst);

public:
    PmergeMe(const std::string &input);
    PmergeMe(const PmergeMe &cp);
    ~PmergeMe();

    PmergeMe &operator=(const PmergeMe &cp);

    bool    checkInput();
    bool    fillVec();
    bool    fillLst();
    void    sortVec();
    void    sortLst();
    void    printVec() const;
    void    printLst();
    void    printInput() const;
    void    getTimeVec() const;
    void    getTimeLst() const;


    class badInput : public std::exception
    {
        public :
            const std::string msg() const throw();
    };
};

#endif

