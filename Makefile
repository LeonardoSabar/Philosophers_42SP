# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: leobarbo <leobarbo@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/01 08:24:07 by leobarbo          #+#    #+#              #
#    Updated: 2024/07/03 14:52:31 by leobarbo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
CFLAGS		:= -Wextra -Wall -Werror -pthread
SRCS_PATH	:= ./src/
.SILENT:

HEADERS		:= -I ./include

SRCS		:= $(addprefix $(SRCS_PATH), \
				action.c \
				get_set.c \
				init.c \
				main.c \
				mutex.c \
				parsing.c \
				synch.c \
				threads.c \
				utils.c)

OBJS		:= $(SRCS:$(SRCS_PATH)%.c=obj/%.o)

all: ${NAME}

${NAME}: ${OBJS}
	@cc ${CFLAGS} ${HEADERS} ${OBJS} -o ${NAME}

obj/%.o: ${SRCS_PATH}%.c | obj_dirs
	@cc ${CFLAGS} -c ${HEADERS} $< -o $@
	@printf "Compiling: ${notdir $<}\n"

obj_dirs:
	@mkdir -p $(dir ${OBJS})

clean:
	@rm -rf obj

fclean: clean
	@rm -f ${NAME}

re: fclean all

.PHONY: all clean fclean re
