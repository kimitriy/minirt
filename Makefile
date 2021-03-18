# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburton <rburton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/28 11:32:38 by rburton           #+#    #+#              #
#    Updated: 2021/03/18 17:37:56 by rburton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

HEADER		= ft_minirt.h

SRC 		= 	ft_mnrt_main.c \
				ft_mnrt_utls.c \
				ft_mnrt_atof.c \
				ft_mnrt_strct.c \
				ft_mnrt_lst.c \
				ft_mnrt_prsr.c \
				ft_mnrt_point.c \
				ft_mnrt_vctr2d.c \
				ft_mnrt_vctr3d.c \
				ft_mnrt_cnvs.c \
				ft_mnrt_mtrx.c \
				ft_mnrt_lookat.c \
				ft_mnrt_print_nscn.c \
				ft_mnrt_rays.c \
				ft_mnrt_sphr.c \
				ft_mnrt_pln.c \
				ft_mnrt_sqr.c \
				ft_mnrt_trngl.c \
				ft_mnrt_cyl.c \
				ft_mnrt_intrsct.c \
				ft_mnrt_lum.c \
				ft_mnrt_nrml.c \
				ft_mnrt_color.c \
				ft_mnrt_mlx.c \
				ft_mnrt_bmp_1.c \
				ft_mnrt_bmp_2.c \
				ft_mnrt_check.c \


OBJS		= ${SRC:.c=.o}

GCC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

# MLXST		= make -C ./mlx_st/

MLXDY		= make -C ./mlx_dy/

# LIB			= libmlx.a libmlx.dylib
LIB			= libmlx.dylib

OPENGL		= -framework OpenGL -framework AppKit

RM			= rm -f

all:		${NAME}

.c.o:		=
				${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS} ${HEADER}
				# ${MLXST}
				# cp ./mlx_st/libmlx.a .
				${MLXDY}
				cp ./mlx_dy/libmlx.dylib .
				${GCC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB} ${OPENGL}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		${RM} ${LIB}
		# make clean -C ./mlx_st/
		make clean -C ./mlx_dy/
		${RM} img.bmp

re:		fclean all
