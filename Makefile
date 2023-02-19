# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fluchten <fluchten@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/09 10:35:06 by fluchten          #+#    #+#              #
#    Updated: 2023/02/19 11:05:14 by fluchten         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
NAME_CL	= client
NAME_SV	= server

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

INC_DIR = includes
SRCS_DIR = srcs
OBJS_DIR = objs

SRCS_CL = client.c utils1.c utils2.c
SRCS_SV = server.c utils2.c

OBJS_CL = $(addprefix ${OBJS_DIR}/, ${SRCS_CL:%.c=%.o})
OBJS_SV = $(addprefix ${OBJS_DIR}/, ${SRCS_SV:%.c=%.o})

all: ${NAME}

${OBJS_DIR}/%.o: ${SRCS_DIR}/%.c
	@mkdir -p ${@D}
	${CC} ${CFLAGS} -I ${INC_DIR} -c $< -o $@

${NAME}: ${NAME_CL} ${NAME_SV}

${NAME_CL}: ${OBJS_CL}
	${CC} ${CFLAGS} ${OBJS_CL} -o ${NAME_CL}

${NAME_SV}: ${OBJS_SV}
	${CC} ${CFLAGS} ${OBJS_SV} -o ${NAME_SV}

clean:
	${RM} ${OBJS_DIR}

fclean: clean
	${RM} ${NAME_CL} ${NAME_SV}

re: fclean all

.PHONY: all clean fclean re