# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ctirions <ctirions@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 00:10:14 by ctirions          #+#    #+#              #
#    Updated: 2022/09/22 17:07:20 by ctirions         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK       = $(shell tput -Txterm setaf 0)
RED         = $(shell tput -Txterm setaf 1)
GREEN       = $(shell tput -Txterm setaf 2)
YELLOW      = $(shell tput -Txterm setaf 3)
LIGHTPURPLE	= $(shell tput -Txterm setaf 4)
PURPLE      = $(shell tput -Txterm setaf 5)
BLUE        = $(shell tput -Txterm setaf 6)
WHITE       = $(shell tput -Txterm setaf 7)
RESET       = $(shell tput -Txterm sgr0)

CXX   =	c++
CXXFLAGS =	-Wall -Wextra -Werror -std=c++98

SRC  =	ft_main.cpp

OBJ  =	$(SRC:.cpp=.o)

STD_SRC  =	std_main.cpp

STD_OBJ  =	$(STD_SRC:.cpp=.o)

NAME  =	ft_containers

STD_NAME  =	std_containers

.cpp.o:
		@$(CXX) $(FLAGS) -c -I ./ $< -o $(<:.cpp=.o)
		@echo "$(LIGHTPURPLE)$< compiled$(RESET)"

$(NAME):	${OBJ}
		@$(CXX) -o $(NAME) $(CXXFLAGS) $(OBJ)
		@echo "$(GREEN)$(NAME) created$(RESET)"

$(STD_NAME):	${STD_OBJ}
		@$(CXX) -o $(STD_NAME) $(CXXFLAGS) $(STD_OBJ)
		@echo "$(GREEN)$(STD_NAME) created$(RESET)"

all:		$(NAME)

ft:			$(NAME)

std:		$(STD_NAME)

clean:
		@rm -f $(OBJ) $(STD_OBJ)
		@echo "$(RED)Cleaned$(RESET)"

fclean:		clean
		@rm -f $(NAME)
		@rm -f $(STD_NAME)
		@echo "$(RED)Fcleaned$(RESET)"

re:			fclean all

.PHONY:		all fclean clean re ft std
