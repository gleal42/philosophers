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
		life/monitor.c \
		utils/sim_utils.c \
		utils/input_utils.c \
		utils/gen_utils.c \
		utils/mutex_create_destroy.c \
		utils/mutex_ops.c
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