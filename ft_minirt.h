/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:54:23 by mspinnet          #+#    #+#             */
/*   Updated: 2021/01/30 19:18:35 by rburton          ###   ########.fr       */
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

//t_list
typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

//color
typedef struct		s_color
{
	unsigned int	t;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_color;

//geometry
typedef struct 		s_point
{
	float			x;
	float			y;
	float			z;
}					t_point;

typedef struct		s_2d_point
{
	int				x;
	int				y;
}					t_2d_point;

typedef struct 		s_vxyz
{
	float			x;
	float			y;
	float			z;
}					t_vxyz;

typedef struct 		s_vctr
{
	t_vxyz			xyz;
	t_vxyz			nxyz;
	float			lngth;
}					t_vctr;

typedef struct 		s_ray
{
	int				sgm;
	t_point			tail_p;
	t_point			head_p;
	t_vctr			vctr[2];
	t_point			hit_p[2];
	float			dist[2];
	char			obj;
	t_color			trgb;
	t_list			*nrst;
}					t_ray;

/*
obj types:
p - pln;
s - sphr;
c - cyl;
q - sqr;
t - trngl;
*/

//lum
typedef struct 		s_lum
{
	float			alvl;
	float			lvl;
	t_vctr			op;
	t_vctr			nrml;
	t_vctr			ldir;
	t_vctr			hvctr;
	float			angl;
	float			dst;
	int				p;
	float			ka;
	float			kd;
	float			ks;
	float			la;
	float			ld;
	float			ls;
	float			l;
}					t_lum;

//mtrx
typedef struct		s_mtrx4x4
{
	float			m[4][4];
}					t_mtrx4x4;

//look_at_mtrx
typedef struct		s_look_at
{
	t_vctr			vF;
	t_vctr			vTMP;
	t_vctr			vR;
	t_vctr			vUP;
	t_mtrx4x4		m;
}					t_look_at;

//mlx

typedef struct  s_vars {
    void			*mlx; //pointer for mlx instance
    void			*win; //pointer for mlx window instance
}               t_vars;

typedef struct 		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pix;
	int				line_lngth;
	int				endian;
}					t_data;

//prsr
typedef struct		s_rsltn
{
	unsigned int	x;
	unsigned int	y;
}					t_rsltn;

typedef struct		s_ambnt
{
	float			lvl;
	t_color			trgb;
}					t_ambnt;

typedef struct		s_cam
{
	t_point			p;
	t_vctr			v;
	int				fov;
	struct s_cam	*nxt;
}					t_cam;

typedef struct		s_lght
{
	t_point			p;
	float			lvl;
	t_color			trgb;
	struct s_lght	*nxt;
}					t_lght;

typedef struct		s_pln
{
	t_point			p;
	t_vctr			v;
	t_color			trgb;
	struct s_pln	*nxt;
}					t_pln;

typedef struct		s_sphr
{
	t_point			p;
	float			d;
	t_color			trgb;
	struct s_sphr	*nxt;
}					t_sphr;

typedef struct		s_cyl
{
	t_point			p;
	t_vctr			v;
	float			d;
	float			h;
	t_color			trgb;
	struct s_cyl	*nxt;
}					t_cyl;

typedef struct		s_sqr
{
	t_point			p;
	t_vctr			v;
	float			side;
	t_color			trgb;
	struct s_sqr	*nxt;
}					t_sqr;

typedef struct		s_trngl
{
	t_point			p1;
	t_point			p2;
	t_point			p3;
	t_vctr			n;
	t_color			trgb;
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

typedef struct		s_scn
{
	t_rsltn			n_rsltn;
	t_ambnt			n_ambnt;
	t_list			*frst_cam;
	t_list			*n_cam;
	t_list			*frst_lght;
	t_list			*n_lght;
	t_list			*frst_pln;
	t_list			*n_pln;
	t_list			*frst_sphr;
	t_list			*n_sphr;
	t_list			*frst_cyl;
	t_list			*n_cyl;
	t_list			*frst_sqr;
	t_list			*n_sqr;
	t_list			*frst_trngl;
	t_list			*n_trngl;
	t_cntr			n_cntr;
	t_vars			vrs;
	t_data			dt;
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
void				null_frst(t_scn *scn);
t_scn				*make_t_scn(void);
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
float				max(float f1, float f2);


//ft_mnrt_list.c
t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);

//ft_mnrt_mlx.c
void				mlx_node(t_scn *lscn, unsigned int **arr);
void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				draw_from_arr(t_scn * nscn, t_data *data, unsigned int **arr);
void				img2win(t_scn *nscn, unsigned int **arr);
int					key_hook(int keycode, t_scn *lscn);
int					close_mlx_win(int keycode, t_vars *vrs);

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
void				p2d_make(t_2d_point *out, int x, int y);
void				p_make(t_point *output, float x, float y, float z);
void				p_calc(t_point *out, t_vctr *vctr, t_point *tail);
void				v_xyz(t_vxyz *out, t_point *tail, t_point *head);
void				v_lngth(t_vctr *vctr);
void				v_n(t_vctr *vctr);
void				v_null(t_vctr *nvctr);
void				v_fill(t_vctr *nvctr);
void				v_make(t_vctr *out, t_point *tail, t_point *head);
void				v_sum(t_vxyz *out, t_vxyz *vctr1, t_vxyz *vctr2);
void    			v_n_prdct(t_vxyz *out, t_vxyz *vxyz, float num);
//void    			nv_n_prdct(t_vctr *vctr, float num);
float				v_d_prdct(t_vxyz *xyz1, t_vxyz *xyz2);
float				v_x_point_prdct(t_vxyz *xyz, t_point *p);
void				v_crss_prdct(t_vxyz *out, t_vxyz *xyz1, t_vxyz *xyz2);
float				v_angle(t_vctr *vctr1, t_vctr *vctr2);
void				v_node(void);

//ft_mnrt_cnvs.c
void				cnvs_node(t_scn *lscn);
void				cnvrse2crtsn(t_scn *lscn,t_2d_point *xy);
void				cnvrse2ncrtsn(t_scn *lscn,t_2d_point *xy);
void				cnvrse2xyz(t_point *out, t_scn *lscn, t_2d_point *xy);

//ft_mnrt_rays.c
void				rays_node(t_scn *lscn, t_scn *nscn);
void				trace_ray_segment(t_ray *ray, t_scn *lscn);
void				trace_ray(t_scn *lscn, t_ray *ray, t_2d_point *xy);
void				ray_null(t_ray *ray);
unsigned long 		cnvrse2trgb(t_color *trgb);
unsigned int		**make_rays_array(t_scn *lscn);
void				launch_rays(t_scn *lscn, unsigned int **rays_arr, t_ray *ray);


//ft_mnrt_mtrx.c
void				mtrx4_x_vctr(t_vxyz *out, t_mtrx4x4 *mtrx, t_vxyz *in);
void				mtrx4_x_point(t_point *out, t_mtrx4x4 *mtrx, t_point *in);

//ft_mnrt_lookat.c
void				look_at_mtrx(t_look_at *lookat, t_vctr *vF, t_point *p);
void				get_cam_fov(t_scn *nscn, t_scn *lscn);
void				cnvrse_lght(t_scn *nscn, t_scn *lscn, t_look_at *lookat);
void				cnvrse_pln(t_scn *nscn, t_scn *lscn, t_look_at *lookat);
void				cnvrse_sphr(t_scn *nscn, t_scn *lscn, t_look_at *lookat);
void				cnvrse_cyl(t_scn *nscn, t_scn *lscn, t_look_at *lookat);
void				cnvrse_sqr(t_scn *nscn, t_scn *lscn, t_look_at *lookat);
void				cnvrse_trngl(t_scn *nscn, t_scn *lscn, t_look_at *lookat);
void				cnvrse2local(t_scn *lscn, t_scn *nscn);
void				lookat_node(t_scn *nscn);

//ft_mnrt_intrsct.c
void				intrsct_node(t_scn *lscn, t_ray *ray);
void 				check_sphrs(t_scn *lscn, t_ray *ray);
void 				check_plns(t_scn *lscn, t_ray *ray);
float				q_equation(float *root, float a, float b, float c);
void				sphr_intrsct(t_scn *lscn, t_sphr *sphr, t_ray *ray);
void				pln_intrsct(t_scn *lscn, t_pln *pln, t_ray *ray);

//ft_mnrt_lum.c
void				l_ambnt(t_lum *lum);
void				l_dffse(t_lum *lum);
void				l_spclr(t_lum *lum);
void				l_all(t_lum *lum);
void    			lum_sphr(t_scn *lscn, t_ray *ray);
void				lum_pln(t_scn *lscn, t_ray *ray);
void				lum_node(t_scn *lscn, t_ray *ray);

//ft_mnrt_nrml.c
void				nrml_sphr(t_vctr *nrml, t_ray *ray, t_sphr *sphr);
void				nrml_trngl(t_trngl *trn);
void				nrml_pln_sqr(t_vctr *nrml, t_vxyz *xyz);

//ft_mnrt_color.c
void				color_make(t_color *color, unsigned int r, unsigned int g, unsigned int b);
void				color_modify(t_color *color, t_lum *lum);
void				color_copy(t_color *to, t_color *from);

#endif
