/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 09:18:32 by mgolinva          #+#    #+#             */
/*   Updated: 2023/05/05 17:50:24 by mgolinva         ###   ########.fr       */
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
# define MERGE_LIMIT 2

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
    /* data */
public:
    PmergeMe(const std::string &input);
    PmergeMe(const PmergeMe &cp);
    ~PmergeMe();

    PmergeMe &operator=(const PmergeMe &cp);
    // std::string &operator<<(PmergeMe &cp);

    bool    checkInput();
    bool    fillContainers();
    void    sortVec();
    // void    sortLst();
    std::vector<unsigned int>    mergeVec(std::vector<unsigned int> &vec);
    void    insertVec(std::vector<unsigned int> &vec);
    void    printLst();
    void    printVec() const;
    void    printInput() const;


    class badInput : public std::exception
    {
        // private :
        //     std::string _arg;
        public :
            // badInput(std::string arg) {_arg = arg;};
            const std::string msg() const throw();
    };
};

#endif

