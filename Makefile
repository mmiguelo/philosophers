# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmiguelo <mmiguelo@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/01 22:37:03 by mmiguelo          #+#    #+#              #
#    Updated: 2025/06/01 22:37:03 by mmiguelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#==============================================================================#
#                                    NAMES                                     #
#==============================================================================#

NAME = philo
CC = cc
FLAGS = -g -Wall -Wextra -Werror
INC = -I./includes
RM = rm -rf

VAL = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --errors-for-leak-kinds=definite

GENERAL := dinner.c
GENERAL +=	getters_setters.c
GENERAL +=	init.c
GENERAL +=	main.c
GENERAL +=	monitor.c
GENERAL +=	parsing.c
GENERAL +=	safe_function.c
GENERAL +=	syncro_utils.c
GENERAL +=	utils.c
GENERAL +=	write.c

#==============================================================================#
#                                    PATHS                                     #
#==============================================================================#

VPATH += src

#==============================================================================#
#                                    FILES                                     #
#==============================================================================#

SRC +=	$(GENERAL)

OBJ_DIR = obj
OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

#==============================================================================#
#                                    RULES                                     #
#==============================================================================#

all: $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : %.c | $(OBJ_DIR)
	$(CC) $(FLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

rv: all
	$(VAL) ./$(NAME) $(ARGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(OBJ_DIR)

re: fclean all