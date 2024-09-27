# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mprofett <mprofett@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/19 20:31:23 by mprofett          #+#    #+#              #
#    Updated: 2024/09/26 23:27:11 by mprofett         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_malcom

SRC			= ft_malcom.c DataUtils.c PrintInfos.c ParseArgs.c

OBJ			= ${SRC:.c=.o}

HEAD		= ft_malcom.h

CC			= gcc

RM			= rm -f

LIBFT		= libft.a

LIBFT_PATH	= libft

C_FLAGS	= -Wall -Wextra -Werror -O3

%.o: %.c
	$(CC) $(C_FLAGS) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJ} ${LIBFT} ${HEAD}
	${CC} ${OBJ} -o ${NAME} ${LIBFT}

${LIBFT}:
	${MAKE} bonus -C ${LIBFT_PATH}
	mv ${LIBFT_PATH}/${LIBFT} .

clean:
	${RM} ${OBJ} ${OBJ_BONUS}
	${MAKE} clean -C ${LIBFT_PATH}

fclean: clean
	${RM} ${NAME} ${LIBFT}
	${MAKE} fclean -C ${LIBFT_PATH}

re:	fclean all

.PHONY:	all clean fclean re