# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: safernan <safernan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/02 10:57:19 by safernan          #+#    #+#              #
#    Updated: 2021/12/19 18:56:08 by safernan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

INCLUDES = ./include

SRC = 	srcs/init.c \
		srcs/parse.c \
		srcs/philo.c \
		srcs/routine.c \
		srcs/thread.c \
		srcs/utils.c \


FLAGS = -Werror -Wall -Wextra -pthread 

CC = gcc $(FLAGS)


OBJ = $(SRC:.c=.o)

.PHONY: all re clean fclean 

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L $(INCLUDES)
	@printf "\n\e[36msuccessfully\e[0m_\e[33m compiled \e[92mis ready !\e[0m\e[?25h\n"

%.o: %.c
	@$(CC) $(FLAGS) -I $(INCLUDES) -c $< -o $@
	@printf "\e[?25l\e[JCreated \e[92m$(notdir $@)\e[0m\r"

clean:
	@$(RM) -f $(OBJ)
	@printf "All object files [\033[31mX\033[0m]\n"

fclean: clean
	@$(RM) -f $(NAME)
	@printf "$(NAME) [\033[31mX\033[0m]\n"

re : fclean all

