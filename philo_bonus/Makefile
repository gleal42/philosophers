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
FLAGS := -Wall -Wextra -Werror -g 
INCLUDE_DIRS := includes \
				life \
				utils \
				.
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
NAME := philo_bonus
SRCS := philo_bonus.c \
		life/life_bonus.c \
		life/prepare_life_bonus.c \
		life/forks_bonus.c \
		life/finish_sim_bonus.c \
		utils/utils_bonus.c \
		utils/utils2_bonus.c \
		utils/utils3_bonus.c

OBJS := $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(FLAGS) -c $^ -o $@ $(INCLUDES)

$(NAME) : $(OBJS) 
	$(CC) $(FLAGS) $^ -o $@ $(INCLUDES)

clean:
	rm -f **/*.o
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re