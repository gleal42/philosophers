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
				utils \
				.
INCLUDES := $(addprefix -I, $(INCLUDE_DIRS))
NAME := philo
SRCS := philo.c \
		utils/utils.c
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

.PHONY: libft all clean fclean re