# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dsenatus <dsenatus@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/12 16:32:48 by lusezett          #+#    #+#              #
#    Updated: 2024/01/11 19:01:01 by dsenatus         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= cub3d

LIBFT			= libft.a

DIR_SRCS		= srcs

DIR_OBJS		= objs

SRCS_NAMES		= 	exec/main.c \
					exec/map.c \
					exec/rendu3d.c\
					parsing/check_map.c \
					parsing/map_utils.c \
					utils/utils.c \

OBJS_NAMES		=	${SRCS_NAMES:.c=.o}

DEPS			=	${SRCS_NAMES:.c=.d}

SRCS			=	$(addprefix $(DIR_SRCS)/,$(SRCS_NAMES))

OBJS			=	$(addprefix $(DIR_OBJS)/,$(OBJS_NAMES))

INC				=	-Iincludes -Ilibft

LIB				=	-lm -Llibft -lft ./minilibx-linux/libmlx_Linux.a -g3 -lXext -lX11 -I ./minilibx-linux/

CC				=	cc

CDFLAGS 		=	-MMD -MP

CFLAGS			=	-g3 -Wall -Wextra -Werror

MAKEFLAGS		=	--no-print-directory

all:	${NAME}

${NAME}: $(DIR_OBJS) $(OBJS)
	make -C libft
	make -C minilibx-linux
	$(CC) -g3 ${INC} $(OBJS) $(LIB) -o $(NAME)

$(OBJS) : $(DIR_OBJS)/%.o : $(DIR_SRCS)/%.c
	$(CC) -g3 $(CDFLAGS) $(INC) -c $< -o $@

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)
	mkdir -p $(DIR_OBJS)/exec
	mkdir -p $(DIR_OBJS)/parsing
	mkdir -p $(DIR_OBJS)/utils

clean:
	make clean -C libft
	make clean -C minilibx-linux
	rm -rf ${DIR_OBJS}

fclean:	clean
	make fclean -C libft
	make clean -C minilibx-linux
	rm -rf ${LIBFT}
	rm -rf ${NAME}
	rm -rf ./minilibx-linux/libmlx_Linux.a
	rm -rf ./minilibx-linux/libmlx.a

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re