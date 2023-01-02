# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fluchten <fluchten@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 10:35:06 by fluchten          #+#    #+#              #
#    Updated: 2023/01/02 07:43:12 by fluchten         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
NAME_CL	= client
NAME_SV	= server

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

INC_DIR	= includes
SRCS_DIR = srcs

SRCS_CL = client.c utils1.c utils2.c
SRCS_SV = server.c utils2.c

OBJS_CL = $(addprefix $(SRCS_DIR)/, $(SRCS_CL:%.c=%.o))
OBJS_SV = $(addprefix $(SRCS_DIR)/, $(SRCS_SV:%.c=%.o))

%.o: %.c
	${CC} ${CFLAGS} -I${INC_DIR} -c $< -o $@

all: ${NAME}

${NAME}: ${NAME_CL} ${NAME_SV}

${NAME_CL}: ${OBJS_CL}
	${CC} ${CFLAGS} ${OBJS_CL} -o ${NAME_CL}

${NAME_SV}: ${OBJS_SV}
	${CC} ${CFLAGS} ${OBJS_SV} -o ${NAME_SV}

clean:
	${RM} ${OBJS_CL} ${OBJS_SV}

fclean: clean
	${RM} ${NAME_CL} ${NAME_SV}

re: fclean all

.PHONY: all clean fclean re