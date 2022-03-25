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
INCLUDE_DIRS := includes \
				life \
				utils \
				.
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
NAME := philo
SRCS := philo.c \
		life/life.c \
		life/init_sim.c \
		life/forks.c \
		life/finish_sim.c \
		utils/utils.c \
		utils/utils2.c \
		utils/utils3.c \
		utils/mutexes.c

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