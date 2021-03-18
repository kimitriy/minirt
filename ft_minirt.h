/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:54:23 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/18 13:12:22 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINIRT_H
# define FT_MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "mlx_dy/mlx.h"

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

typedef struct		s_cmyk
{
	float			c;
	float			m;
	float			y;
	float			k;
}					t_cmyk;

//geometry
typedef struct 		s_point
{
	float			x;
	float			y;
	float			z;
}					t_point;

typedef struct		s_2d_point
{
	float				x;
	float				y;
}					t_2d_point;

typedef struct 		s_vxy
{
	float			x;
	float			y;
}					t_vxy;

typedef struct 		s_vctr2d
{
	t_vxy			xy;
	float			lngth;
}					t_vctr2d;

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
	t_point			hit_p;
	float			dist;
	//float			l;
	char			obj;
	char			shdw;
	t_color			obj_trgb;
	t_color			sum_trgb;
	t_color			p_trgb;
	t_list			*nrst;
}					t_ray;

/*
obj:
r - res
a - amb
o - cam
l - light
p - pln;
s - sphr;
c - cyl;
q - sqr;
t - trngl;
shdw:
y - yes;
\0 - no;
*/

typedef struct 		s_plnx
{
	t_point			_o; //projection of RO
	t_vctr			orth; //orthogonal from RO to _ro
	float			t; //distan
}					t_plnx;

//mtrx
typedef struct		s_mtrx4x4
{
	float			m[4][4];
}					t_mtrx4x4;

//look_at_mtrx
typedef struct		s_look_at
{
	char			tmp;
	t_vctr			v_f;
	t_vctr			v_tmp;
	t_vctr			v_r;
	t_vctr			v_up;
	t_mtrx4x4		m;
}					t_look_at;

typedef struct 		s_trigon
{
	t_point			xp;
	t_vctr			v_ab;
	t_vctr			v_ac;
	t_vctr			v_op;
	t_vctr			v_minus_f;
	t_look_at		lkt;
	t_2d_point		_a;
	t_2d_point		_b;
	t_2d_point		_c;
	t_2d_point		_xp;
	t_vctr2d		_ab;
	t_vctr2d		_ac;
	t_vctr2d		_axp;
	t_vctr2d		_bc;
	t_vctr2d		_ba;
	t_vctr2d		_bxp;
	t_vctr2d		_ca;
	t_vctr2d		_cb;
	t_vctr2d		_cxp;
	float			t;
	// char			f; //flag; if (f == '\0') make_plgn() hasn't been called yet, if (f == 'f') it has
	char			xp_in; //if (p_in == '\0') .p is not in trngl, if (p_in == '+') .p is in trngl
}					t_trigon;

typedef struct 		s_qdron
{
	t_point			xp; //intersection point at which the ray intersects the pln
	t_vctr			v_tmp;
	t_vctr			v_r;
	t_vctr			v_up;
	t_vctr			v_cxp; //vctr on the pln from .C (which is the point which is given to build the pln) to .i (which is an intersection point on the pln)
	float			alpha; //rad, angle between vR и vpi
	float			t;
	float			x;
	float			y;
	char			xp_in;
}					t_qdron;

typedef struct		s_pln
{
	t_point			p;
	t_vctr			v;
	t_color			trgb;
	struct s_pln	*nxt;
}					t_pln;

typedef struct 		s_cylon
{
	t_point			o; //ray origin
	t_point			_o; //projection of the ray origin point
	t_point			o_nb; //conversed .O
	t_point			c; //center of the cyl
	t_point			_c; //projection of the cyl's center point
	t_point			d; 
	t_point			_d; //necessary to build a projection line
	t_2d_point		d_nb; //conversed .D'
	t_point			xp1;
	t_point			xp2;
	t_point			p;	//intersection point with the cyl's cap plane
	t_vctr2d		v_od_nb; //projection of the vD vctr
	t_vctr2d		v_oc_nb; //vctr from _RO to _C
	t_vctr			v_d;
	t_vctr			v_od; //projection of v_d
	t_vctr			v_oxp1;
	t_vctr			v_oxp2;
	t_vctr			v_o_c; //vctr from _o' to _c'
	t_vctr			v_p_c; //vctr from .plnXP' to _c'
	t_pln			pln; //a pln where the cap 1 lies
	float			_ch; //length of a perpendicular from .c to the projection of vD
	float			t1; //length of the vOXP1 vctr
	float			t2; //length of the vOXP2 vctr
	float			_oh; //distance from _RO to the point where projection of vOXP intersects with CH
	float			_hxp; //distance from the point where projection of vOXP intersects with CH to XP
	float			_oxp1; //projection of v_oxp1
	float			_oxp2; //projection of v_oxp2
	float			angle; //angle between vD of the ray and _vOC
	float			sin_alpha; //angle between vN of the cyl and vD of the ray
}					t_cylon;

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
	char			shdw;
	t_color			l_trgb;
}					t_lum;

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

// typedef struct		s_pln
// {
// 	t_point			p;
// 	t_vctr			v;
// 	t_color			trgb;
// 	struct s_pln	*nxt;
// }					t_pln;

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
	t_vctr			n;
	// t_vctr			n2;
	float			d;
	float			h;
	t_color			trgb;
	struct s_cyl	*nxt;
}					t_cyl;

typedef struct		s_sqr
{
	t_point			p;
	t_vctr			v;
	t_vctr			v_tmp;
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
	t_trigon		trgn;
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
	char			save;
}					t_scn;

typedef struct		s_prsr
{
	int				i;
	int				j;
	int				n;
	char			rx[6];
	char			ry[6];
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
	char			r[4];
	char			g[4];
	char			b[4];
	char			fov[4];
	char			lvl[42];
	char			side[42];
	char			d[42];
	char			h[42];
}					t_prsr;

typedef struct 		s_vldt
{
	int				r_cnt;
	int				a_cnt;
	
}					t_vldt;


//ft_mnrt_main.c
void				check_argv(int argc, char **argv, char *save);
void				make_scn_arr(t_list **head, int size, char save);

//ft_mnrt_strct.c
void				make_t_rsltn(t_scn *nscn);
void				make_t_ambnt(t_scn *nscn);
void				make_t_cam(t_scn *nscn);
void				t_lght_null(t_lght *lght);
void				make_t_lght(t_scn *nscn);
void				make_t_pln(t_scn *nscn);
void				make_t_sphr(t_scn *nscn);
void				make_t_cyl(t_scn *nscn);
void				make_t_sqr(t_scn *nscn);
void				make_t_trngl(t_scn *nscn);
void				make_t_cntr(t_scn *nscn);
void				null_frst(t_scn *scn);
t_scn				*make_t_scn(char save);
void				nprsr_reset_counters(t_prsr *nprsr);
void				nprsr_nullt_fields(t_prsr *nprsr);
t_prsr				make_t_prsr(void);
void				strct_node(char **scn_arr, int size, char save);


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
float				ft_atof(const char *str);


//ft_mnrt_utls.c
void				ft_bzero(void *s, size_t n);
size_t				ft_strlen(const char *s);
void				*ft_calloc(size_t count, size_t size);
char				*ft_strjoin(char const *s1, char const *s2);
int					w2l(int fd, char *buf, char **line);
int					get_next_line(int fd, char **line);
long int			ft_atoi(const char *str);
int					ft_isalpha(int c);
int					ft_isdigit(int c);
float				max_2floats(float f1, float f2);
float				max_3floats(float a, float b, float c);
float				min_2floats(float a, float b);
void				err_message(char *error);
int					ft_strcmp(char *s1, char *s2);
void				ft_putchar(int fd, char c);
void				ft_putnbr(int fd, unsigned int nbr, int base, char *dgts);
char				*ft_strchr(const char *s, int c);


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

//ft_mnrt_point.c
void				p2d_make(t_2d_point *out, int x, int y);
void				p_make(t_point *output, float x, float y, float z);
void				p_calc(t_point *out, t_vxyz *vctr, t_point *tail);
void				p_copy(t_point *out, t_point *in);
int					p_is_equal(t_point *p1, t_point *p2);
void				p2pln_prjctn(t_plnx *plnx, t_pln *pln, t_point *p);

//ft_mnrt_vctr2d.c
void				v_xy(t_vxy *out, t_2d_point *tail, t_2d_point *head);
void				v2d_null(t_vctr2d *vctr);
void				v2d_lngth(t_vctr2d *vctr);
void				v2d_make(t_vctr2d *out, t_2d_point *tail, t_2d_point *head);
float				v2d_d_prdct(t_vxy *xy1, t_vxy *xy2);
float				v2d_pd_prdct(t_vctr2d *_vD, t_vctr2d *_vOC);

//ft_mnrt_vctr3d.c
void				v_xyz(t_vxyz *out, t_point *tail, t_point *head);
void				v_lngth(t_vctr *vctr);
void				v_n(t_vctr *vctr);
void				v_null(t_vctr *nvctr);
void				v_fill(t_vctr *nvctr);
void				v_make(t_vctr *out, t_point *tail, t_point *head);
void				v_copy(t_vctr *out, t_vctr *in);
void				v_sum(t_vxyz *out, t_vxyz *vctr1, t_vxyz *vctr2);
void				v_sbtrct(t_vxyz *out, t_vxyz *vctr1, t_vxyz *vctr2);
void    			v_n_prdct(t_vxyz *out, t_vxyz *vxyz, float num);
float				v_d_prdct(t_vxyz *xyz1, t_vxyz *xyz2);
float				v_x_point_prdct(t_vxyz *xyz, t_point *p);
void				v_crss_prdct(t_vxyz *out, t_vxyz *xyz1, t_vxyz *xyz2);
float				v_angle(t_vctr *vctr1, t_vctr *vctr2);
void				v_opposite(t_vctr *vctr);
float				v_are_collinear(t_vctr *v1, t_vctr *v2);
void				v_node(void);

//ft_mnrt_cnvs.c
void				cnvs_node(t_scn *lscn);
void				cnvrse2crtsn(t_scn *lscn,t_2d_point *xy);
void				cnvrse2ncrtsn(t_scn *lscn,t_2d_point *xy);
void				cnvrse2xyz(t_point *out, t_scn *lscn, t_2d_point *xy);

//ft_mnrt_rays.c
void				rays_node(t_scn *lscn, t_scn *nscn);
void				trace_ray(t_scn *lscn, t_ray *ray);
void				ray_null(t_ray *ray);
unsigned long 		cnvrse2trgb(t_color *trgb);
unsigned int		**make_rays_array(t_scn *lscn);
void				launch_rays(t_scn *lscn, unsigned int **rays_arr, t_ray *ray);

//ft_mnrt_mtrx.c
void				mtrx4_x_vctr(t_vctr *out, t_mtrx4x4 *mtrx, t_vxyz *in);
void				mtrx4_x_point(t_point *out, t_mtrx4x4 *mtrx, t_point *in);

//ft_mnrt_lookat.c
void				null_lookat(t_look_at *lookat);
void				v_tmp_make(t_vctr *vf, t_vctr *tmp, t_look_at *lookat);
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
void				check_objcts(t_scn *lscn, t_ray *ray);
void				check_lghts(t_scn *lscn, t_ray *ray);

//ft_mnrt_lum.c
void				l_ambnt(t_lum *lum);
void				l_dffse(t_lum *lum);
void				l_spclr(t_lum *lum);
void				l_all(t_scn *lscn, t_lum *lum);
void				make_lum(t_lum *lum, t_scn *lscn, t_lght *lght, t_ray *ray);
void    			lum_sphr(t_scn *lscn, t_lght *lght, t_ray *ray);
void				lum_pln(t_scn *lscn, t_lght *lght, t_ray *ray);
void				lum_node(t_scn *lscn, t_lght *lght, t_ray *ray);

//ft_mnrt_nrml.c
void				nrml_sphr(t_vctr *nrml, t_ray *ray, t_sphr *sphr);
void				nrml_trngl(t_trngl *trngl, t_ray *ray);
void				nrml_pln(t_pln *pln, t_ray *ray);
void				nrml_sqr(t_sqr *sqr, t_ray *ray);
void				nrml_cyl(t_cyl *cyl, t_ray *ray);

//ft_mnrt_sphr.c
float				q_equation(float *root, float a, float b, float c);
void				sphr_intrsct(t_scn *lscn, t_sphr *sphr, t_ray *ray);
void 				check_sphrs(t_scn *lscn, t_ray *ray);

//ft_mnrt_pln.c
// float				pln_equation(t_point *p, t_point *r_orgn, t_vctr *nrml, t_vctr *ray);
t_plnx				pln_equation(t_point *p, t_point *r_orgn, t_vctr *nrml, t_vctr *ray);
void				pln_intrsct(t_scn *lscn, t_pln *pln, t_ray *ray);
void 				check_plns(t_scn *lscn, t_ray *ray);
void				pln_null(t_pln *pln);
void				plnx_null(t_plnx *plnx);

//ft_mnrt_sqr.c
void				qdron_null(t_qdron *qdrn);
void				qdron_make(t_qdron *qdrn, t_sqr *sqr);
void				is_in_sqr(t_qdron *qdrn,t_sqr *sqr);
void				sqr_intrsct(t_scn *lscn, t_sqr *sqr, t_ray *ray);
void 				check_sqrs(t_scn *lscn, t_ray *ray);

//ft_mnrt_trngl.c
void				trgn_null(t_trigon *trgn);
void				trgn_prmtr(t_trigon *trgn);
void				trgn_area(t_trigon *trgn);
void				is_in_trngl(t_trngl *trngl);
void				trgn_make(t_trngl *trngl, t_ray *ray);
void				trngl_intrsct(t_scn *lscn, t_trngl *trngl, t_ray *ray);
void 				check_trngls(t_scn *lscn, t_ray *ray);

//ft_mnrt_cyl.c
void				cylon_null(t_cylon *cln);
void				cylon_cnvrse(t_cylon *cln, t_look_at *lkt);
void				cylon_make(t_cylon *cln, t_ray *ray, t_cyl *cyl);
void				cylon_make1(t_cylon *cln, t_ray *ray, t_cyl *cyl, t_look_at *lkt);
void				cylon_make2(t_cylon *cln, t_ray *ray, t_cyl *cyl, t_look_at	*lkt);
void				cylon_make3(t_cylon *cln, t_cyl *cyl);
void				cyl_intrsct(t_scn *lscn, t_cyl *cyl, t_ray *ray);
void 				check_cyls(t_scn *lscn, t_ray *ray);

//ft_mnrt_color.c
void				color_make(t_color *color, unsigned int r, unsigned int g, unsigned int b);
void				color_null(t_color *color);
void				color_calc(t_color *out, t_color *in, t_lum *lum);
void				color_copy(t_color *to, t_color *from);
void    			color_node(t_scn *lscn, t_ray *ray, t_lum *lum);

//ft_mnrt_bmp.c
void    			bmp_node(t_scn *nscn, unsigned int **arr);
void				img2pic(t_scn *nscn, unsigned int **arr, unsigned int pddng, int fd);
void				bmp_hdr(t_scn *nscn, int file_size, int fd);
unsigned int		get_pddng(t_scn *nscn);

//ft_mnrt_check.c
void    			check_node(char	**scn_arr, int size);
void				vldt_null(t_vldt *v);
void				check_keys(char *l, t_vldt *v);
void				p_marks_hndlr(char *l, int i);
void				check_delimeters(char *l);
void				n_arg(char *l, int n);
void				check_args(char *l);
void				check_line(char *line, t_vldt *v);

void				check_values_node(t_prsr *np, char obj);
void				check_resolution(t_prsr *np);

#endif
