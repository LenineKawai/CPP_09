# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgolinva <mgolinva@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/25 10:15:07 by mgolinva          #+#    #+#              #
#    Updated: 2023/05/11 16:20:22 by mgolinva         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	main.cpp	\
			BitcoinExchange.cpp

INCL	=   BitcoinExchange.hpp

CC		= c++

FLAGS	= -Wall -Wextra -Werror -std=c++98 -pedantic -fsanitize=address -g3

RM		= rm -f

OBJS	= $(SRCS:.cpp=.o)

NAME	= BTC

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