# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburton <rburton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/28 11:32:38 by rburton           #+#    #+#              #
#    Updated: 2021/01/27 01:42:50 by rburton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#SRC 		= 	ft_mnrt_main.c \
				ft_mnrt_utls.c \
				ft_mnrt_atof.c \
				ft_mnrt_strct.c \
				ft_mnrt_lst.c \
				ft_mnrt_prsr.c \
				ft_mnrt_vctr.c \
				ft_mnrt_cnvs.c \
				ft_mnrt_mtrx.c \
				ft_mnrt_lookat.c \
				ft_mnrt_print_nscn.c \
				ft_mnrt_rays.c \
				ft_mnrt_intrsct.c \
				ft_mnrt_mlx.c \

SRC 		= 	ft_mnrt_main.c \
				ft_mnrt_utls.c \
				ft_mnrt_atof.c \
				ft_mnrt_strct.c \
				ft_mnrt_lst.c \
				ft_mnrt_prsr.c \
				ft_mnrt_vctr.c \
				ft_mnrt_cnvs.c \
				ft_mnrt_mtrx.c \
				ft_mnrt_lookat.c \
				ft_mnrt_print_nscn.c \
				ft_mnrt_rays.c \
				ft_mnrt_intrsct.c \
				ft_mnrt_lum.c \
				ft_mnrt_nrml.c \
				ft_mnrt_color.c \
				ft_mnrt_mlx.c \


OBJS		= ${SRC:.c=.o}

NAME		= mnrt.out

GCC			= gcc

#OPTFLAGS	= -O2

#CFLAGS		= -g -Wall -Wextra -Werror
CFLAGS		= -g

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
