# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 10:15:07 by mgolinva          #+#    #+#              #
#    Updated: 2023/05/05 17:20:50 by mgolinva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.cpp	\
			PmergeMe.cpp	

INCL	=   PmergeMe.hpp

CC		= c++

FLAGS	= -Wall -Wextra -Werror -std=c++98 -pedantic #-fsanitize=address -g3

RM		= rm -f

OBJS	= $(SRCS:.cpp=.o)

NAME	= mis

%.o: %.cpp $(INCL) Makefile
	$(CC) -c $< -o $@ $(FLAGS)

all 	: $(NAME)

$(NAME)	: $(OBJS) $(INCL) Makefile
	$(CC) -o $(NAME) $(OBJS) $(FLAGS)

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re		: fclean $(NAME)

.PHONY	: make clean fclean all re