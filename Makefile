# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rburton <rburton@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/28 11:32:38 by rburton           #+#    #+#              #
#    Updated: 2021/03/20 13:01:24 by rburton          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

HEADER		= ft_minirt.h

SRC 		= 	ft_mnrt_main.c \
				ft_mnrt_utls_1.c \
				ft_mnrt_utls_2.c \
				ft_mnrt_utls_3.c \
				ft_mnrt_utls_4.c \
				ft_mnrt_atof.c \
				ft_mnrt_strct_1.c \
				ft_mnrt_strct_2.c \
				ft_mnrt_strct_3.c \
				ft_mnrt_strct_4.c \
				ft_mnrt_lst.c \
				ft_mnrt_prsr_1.c \
				ft_mnrt_prsr_2.c \
				ft_mnrt_prsr_3.c \
				ft_mnrt_prsr_4.c \
				ft_mnrt_prsr_5.c \
				ft_mnrt_prsr_6.c \
				ft_mnrt_point_1.c \
				ft_mnrt_point_2.c \
				ft_mnrt_vctr2d_1.c \
				ft_mnrt_vctr2d_2.c \
				ft_mnrt_vctr3d_1.c \
				ft_mnrt_vctr3d_2.c \
				ft_mnrt_vctr3d_3.c \
				ft_mnrt_vctr3d_4.c \
				ft_mnrt_cnvs.c \
				ft_mnrt_mtrx.c \
				ft_mnrt_lookat_1.c \
				ft_mnrt_lookat_2.c \
				ft_mnrt_lookat_3.c \
				ft_mnrt_rays_1.c \
				ft_mnrt_rays_2.c \
				ft_mnrt_sphr.c \
				ft_mnrt_pln_1.c \
				ft_mnrt_pln_2.c \
				ft_mnrt_sqr_1.c \
				ft_mnrt_sqr_2.c \
				ft_mnrt_trngl_1.c \
				ft_mnrt_trngl_2.c \
				ft_mnrt_cyl_1.c \
				ft_mnrt_cyl_2.c \
				ft_mnrt_cyl_3.c \
				ft_mnrt_cyl_4.c \
				ft_mnrt_intrsct.c \
				ft_mnrt_lum_1.c \
				ft_mnrt_lum_2.c \
				ft_mnrt_lum_3.c \
				ft_mnrt_nrml.c \
				ft_mnrt_color_1.c \
				ft_mnrt_color_2.c \
				ft_mnrt_mlx_1.c \
				ft_mnrt_mlx_2.c \
				ft_mnrt_bmp_1.c \
				ft_mnrt_bmp_2.c \
				ft_mnrt_check_1.c \
				ft_mnrt_check_2.c \
				ft_mnrt_check_val_1.c \
				ft_mnrt_check_val_2.c \
				ft_mnrt_check_val_3.c \


OBJS		= ${SRC:.c=.o}

GCC			= gcc

CFLAGS		= -g -Wall -Wextra -Werror

MLXDY		= make -C ./mlx_dy/

LIB			= libmlx.dylib

OPENGL		= -framework OpenGL -framework AppKit

RM			= rm -f

all:		${NAME}

.c.o:		=
				${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:		${OBJS} ${HEADER}
				${MLXDY}
				cp ./mlx_dy/libmlx.dylib .
				${GCC} ${CFLAGS} -o ${NAME} ${OBJS} ${LIB} ${OPENGL}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}
		${RM} ${LIB}
		make clean -C ./mlx_dy/
		${RM} img.bmp

re:		fclean all
