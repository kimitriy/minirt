# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburton <rburton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/28 11:32:38 by rburton           #+#    #+#              #
#    Updated: 2021/01/16 15:25:20 by rburton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC 		= ft_mnrt_main.c ft_mnrt_utls.c ft_mnrt_atof.c ft_mnrt_strct.c ft_mnrt_lst.c ft_mnrt_prsr.c ft_mnrt_mlx.c ft_mnrt_vctr.c ft_mnrt_cnvs.c ft_mnrt_rays.c
#SRC 		= ft_mnrt_main.c ft_mnrt_utls.c ft_mnrt_atof.c ft_mnrt_strct.c ft_mnrt_lst.c ft_mnrt_prsr.c mlx_window.c ft_mnrt_print_nscn.c
#SRC 		= ft_mnrt_main.c ft_mnrt_utls.c ft_mnrt_atof.c ft_mnrt_strct.c ft_mnrt_lst.c ft_mnrt_prsr.c mlx_window.c

OBJS		= ${SRC:.c=.o}

NAME		= mnrt.out

GCC			= gcc

#OPTFLAGS	= -O2

CFLAGS		= -g -Wall -Wextra -Werror

#MLX		= -Imlx

OPENGL		= -L. libmlx.a -framework OpenGL -framework AppKit

RM			= rm -f

#ARRC		= ar rc

FT_H		= ft_minirt.h

#LIB			= libminirt.a

all:	${NAME}

#bonus:	all

#сопоставление *.c и *.o файлов
.c.o:
		${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:${OBJS}
		${GCC} ${CFLAGS} -o ${NAME} ${OBJS} ${OPENGL}
#		${ARRC} ${LIB} ${OBJS}
#		${ARRC} ${LIB} ${FT_H}

#main:
#		${GCC} ${CFLAGS} ${LIB} ft_mnrt_main.c

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		${RM} ${LIB}

re:		fclean all
