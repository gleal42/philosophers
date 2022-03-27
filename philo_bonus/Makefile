# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gleal <gleal@student.42lisboa.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 20:26:39 by gleal             #+#    #+#              #
#    Updated: 2022/03/07 20:32:07by gleal            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
FLAGS := -Wall -Wextra -Werror -pthread
INCLUDE_DIRS := includes_bonus \
				life_bonus \
				utils_bonus \
				.
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
NAME := philo_bonus
SRCS := philo_bonus.c \
		life_bonus/life_bonus.c \
		life_bonus/eating_bonus.c \
		life_bonus/prepare_life_bonus.c \
		utils_bonus/gen_utils_bonus.c \
		utils_bonus/input_utils_bonus.c \
		utils_bonus/sim_utils_bonus.c
OBJS := $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $^ -o $@ $(INCLUDES)

$(NAME) : $(OBJS) 
	$(CC) $(FLAGS) $^ -o $@ $(INCLUDES)

clean:
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re