/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:54:23 by mspinnet          #+#    #+#             */
/*   Updated: 2021/01/16 18:03:49 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINIRT_H
# define FT_MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
//# include <stdarg.h>

typedef struct		s_rsltn
{
	unsigned int	x;
	unsigned int	y;
}					t_rsltn;

typedef struct		s_ambnt
{
	float			lvl;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_ambnt;

typedef struct		s_cam
{
	float			x;
	float			y;
	float			z;
	float			nx;
	float			ny;
	float			nz;
	int				fov;
	struct s_cam	*nxt;
}					t_cam;

typedef struct		s_lght
{
	float			x;
	float			y;
	float			z;
	float			lvl;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	struct s_lght	*nxt;
}					t_lght;

typedef struct		s_pln
{
	float			x;
	float			y;
	float			z;
	float			nx;
	float			ny;
	float			nz;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	struct s_pln	*nxt;
}					t_pln;

typedef struct		s_sphr
{
	float			x;
	float			y;
	float			z;
	float			d;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	struct s_sphr	*nxt;
}					t_sphr;

typedef struct		s_cyl
{
	float			x;
	float			y;
	float			z;
	float			nx;
	float			ny;
	float			nz;
	float			d;
	float			h;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	struct s_cyl	*nxt;
}					t_cyl;

typedef struct		s_sqr
{
	float			x;
	float			y;
	float			z;
	float			nx;
	float			ny;
	float			nz;
	float			side;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	struct s_sqr	*nxt;
}					t_sqr;

typedef struct		s_trngl
{
	float			x1;
	float			y1;
	float			z1;
	float			x2;
	float			y2;
	float			z2;
	float			x3;
	float			y3;
	float			z3;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	struct s_trngl	*nxt;
}					t_trngl;

typedef struct		s_cntr
{
	int				cam;
	int				lght;
	int				pln;
	int				sphr;
	int				cyl;
	int				sqr;
	int				trngl;
}					t_cntr;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_scn
{
	t_rsltn			n_rsltn;
	t_ambnt			n_ambnt;
	t_list			*n_cam;
	t_list			*n_lght;
	t_list			*n_pln;
	t_list			*n_sphr;
	t_list			*n_cyl;
	t_list			*n_sqr;
	t_list			*n_trngl;
	t_cntr			n_cntr;	
}					t_scn;

typedef struct		s_prsr
{
	int				i;
	int				j;
	int				n;
	char			rx[5];
	char			ry[5];
	char			x[42];
	char			y[42];
	char			z[42];
	char			x2[42];
	char			y2[42];
	char			z2[42];
	char			x3[42];
	char			y3[42];
	char			z3[42];
	char			nx[42];
	char			ny[42];
	char			nz[42];
	char			r[5];
	char			g[5];
	char			b[5];
	char			fov[5];
	char			lvl[42];
	char			side[42];
	char			d[42];
	char			h[42];
}					t_prsr;

typedef struct		s_atof
{
	unsigned int	i;
	unsigned int	j;
	double			r;
	double			int_part;
	int				fract_part;
	int				sign;
	char			digits[11];
	char			dot;
	double			rv;
}					t_atof;

//mlx
typedef struct 		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pix;
	int				line_lngth;
	int				endian;
}					t_data;

typedef struct 		s_draw_sqr
{
	int				start_x;
	int				start_y;
	int				side;
	int				color;
}					t_draw_sqr;

typedef struct 		s_draw_crcl
{
	int				start_x;
	int				start_y;
	int				r;
	int				color;
	int				root1;
	int				root2;
}					t_draw_crcl;

//geometry

typedef struct 		s_point
{
	float			x;
	float			y;
	float			z;
}					t_point;

typedef struct 		s_vctr
{
	float			x;
	float			y;
	float			z;
	float			nx;
	float			ny;
	float			nz;
	float			lngth;
}					t_vctr;

typedef struct 		s_cnvs_xy
{
	t_rsltn			rsltn;
	int				x_crtsn;
	int				y_crtsn;
	int				x_ncrtsn;
	int				y_ncrtsn;
}					t_cnvs_xy;

typedef struct 		s_ray
{
	t_cnvs_xy		cnvs_xy;
	t_point			*tail_point;
	t_point			*head_point;
	t_vctr			vctr[3];
	t_point			hit_point[3];
	float			dstnce;
}					t_ray;

//color
typedef struct 		s_color
{
	int			x;
	int			y;
	int			z;
}					t_color;

//ft_mnrt_main.c
void				make_scn_arr(t_list **head, int size);

//ft_mnrt_strct.c
void				make_t_rsltn(t_scn *nscn);
void				make_t_ambnt(t_scn *nscn);
void				make_t_cam(t_scn *nscn);
void				make_t_lght(t_scn *nscn);
void				make_t_pln(t_scn *nscn);
void				make_t_sphr(t_scn *nscn);
void				make_t_cyl(t_scn *nscn);
void				make_t_sqr(t_scn *nscn);
void				make_t_trngl(t_scn *nscn);
void				make_t_cntr(t_scn *nscn);
t_scn				make_t_scn(void);
void				nprsr_reset_counters(t_prsr *nprsr);
void				nprsr_nullt_fields(t_prsr *nprsr);
t_prsr				make_t_prsr(void);
void				strct_node(char **scn_arr, int size);


//ft_mnrt_prsr.c
void				prsr(char **scn_arr, int size, t_scn *nscn, t_prsr *np);
void				prsr_rsltn(char *line, t_scn *nscn, t_prsr *np);
void				prsr_ambnt(char *line, t_scn *nscn, t_prsr *np);
void				prsr_cam(char *line, t_scn *nscn, t_prsr *np);
void				prsr_lght(char *line, t_scn *nscn, t_prsr *np);
void				prsr_sphr(char *line, t_scn *nscn, t_prsr *np);
void				prsr_pln(char *line, t_scn *nscn, t_prsr *np);
void				prsr_sqr(char *line, t_scn *nscn, t_prsr *np);
void				prsr_cyl(char *line, t_scn *nscn, t_prsr *np);
void				prsr_trngl(char *line, t_scn *nscn, t_prsr *np);
void				prsr_assist(char *line, t_prsr *np, char *field, int n);
void				write_rsltn(t_scn *nscn, t_prsr *np);
void				write_ambnt(t_scn *nscn, t_prsr *np);
void				write_cam(t_scn *nscn, t_prsr *np);
void				write_lght(t_scn *nscn, t_prsr *np);
void				write_pln(t_scn *nscn, t_prsr *np);
void				write_sphr(t_scn *nscn, t_prsr *np);
void				write_cyl(t_scn *nscn, t_prsr *np);
void				write_sqr(t_scn *nscn, t_prsr *np);
void				write_trngl(t_scn *nscn, t_prsr *np);


//ft_mnrt_atof.c
void				reset_ns(t_atof *ns);
t_atof				make_t_atof(void);
void				atof_prsr(const char *str, t_atof *ns);
int					nbr_length(long long int n, int base);
int					ft_iterative_power(int nb, int power);
float				ft_atof(const char *str);


//ft_mnrt_utls.c
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *s);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
int					w2l(int fd, char *buf, char **line);
int					get_next_line(int fd, char **line);
int					ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);

//ft_mnrt_list.c
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);

//ft_mnrt_mlx.c
void				call_node(void);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				draw_sqr(t_data *data, t_draw_sqr *sqr);
void				make_new_sqr(t_draw_sqr *new_sqr);
void				img2win(void);

//ft_mnrt_print_nscn.c
void				print_node(t_scn *nscn);
void    			print_cam(t_scn *nscn);
void    			print_light(t_scn *nscn);
void    			print_pln(t_scn *nscn);
void    			print_sphr(t_scn *nscn);
void    			print_cyl(t_scn *nscn);
void    			print_sqr(t_scn *nscn);
void    			print_trngl(t_scn *nscn);

//ft_mnrt_vctr.c
t_point				*p_make(float x, float y, float z);
void				v_xyz(t_vctr *vctr, t_point *tail, t_point *head);
void				v_lngth(t_vctr *vctr);
void				v_nxyz(t_vctr *vctr);
t_vctr				*v_make(t_point *tail, t_point *head);
t_vctr				*v_sum(t_vctr *vctr1, t_vctr *vctr2);
void    			v_n_prdct(t_vctr *vctr, float num);
void    			nv_n_prdct(t_vctr *vctr, float num);
float				v_dt_prdct(t_vctr *vctr1, t_vctr *vctr2);
float				v_angle(t_vctr *vctr1, t_vctr *vctr2);
void				v_node(void);

//ft_mnrt_cnvs.c
void				cnvs_node(t_scn *nscn);
void				cnvrse2crtsn(t_cnvs_xy *xy);
void				cnvrse2ncrtsn(t_cnvs_xy *xy);
t_point				*cnvrse2xyz(t_scn *nscn, t_cnvs_xy *xy);

//ft_mnrt_rays.c
void				rays_node(t_scn *nscn);
void				ray_eqtn(t_ray *ray, int dstnce, int gen);
void   				*make_ray(t_scn *nscn, int x, int y);

#endif
