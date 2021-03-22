/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minirt.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:54:23 by mspinnet          #+#    #+#             */
/*   Updated: 2021/03/22 16:24:54 by rburton          ###   ########.fr       */
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

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

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

typedef struct		s_point
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

typedef struct		s_vxy
{
	float			x;
	float			y;
}					t_vxy;

typedef struct		s_vctr2d
{
	t_vxy			xy;
	float			lngth;
}					t_vctr2d;

typedef struct		s_vxyz
{
	float			x;
	float			y;
	float			z;
}					t_vxyz;

typedef struct		s_vctr
{
	t_vxyz			xyz;
	t_vxyz			nxyz;
	float			lngth;
}					t_vctr;

typedef struct		s_ray
{
	int				sgm;
	t_point			tail_p;
	t_point			head_p;
	t_vctr			vctr[2];
	t_point			hit_p;
	float			dist;
	char			obj;
	char			shdw;
	t_color			obj_trgb;
	t_color			sum_trgb;
	t_color			p_trgb;
	t_list			*nrst;
}					t_ray;

typedef struct		s_plnx
{
	t_point			o;
	t_vctr			orth;
	float			t;
}					t_plnx;

typedef struct		s_mtrx4x4
{
	float			m[4][4];
}					t_mtrx4x4;

typedef struct		s_look_at
{
	char			tmp;
	t_vctr			v_f;
	t_vctr			v_tmp;
	t_vctr			v_r;
	t_vctr			v_up;
	t_mtrx4x4		m;
}					t_look_at;

typedef struct		s_trigon
{
	t_point			xp;
	t_vctr			v_ab;
	t_vctr			v_ac;
	t_vctr			v_op;
	t_vctr			v_minus_f;
	t_look_at		lkt;

	t_2d_point		p2_a;
	t_2d_point		p2_b;
	t_2d_point		p2_c;
	t_2d_point		p2_xp;
	t_vctr2d		v2_ab;
	t_vctr2d		v2_ac;
	t_vctr2d		v2_axp;
	t_vctr2d		v2_bc;
	t_vctr2d		v2_ba;
	t_vctr2d		v2_bxp;
	t_vctr2d		v2_ca;
	t_vctr2d		v2_cb;
	t_vctr2d		v2_cxp;
	float			t;
	char			xp_in;
}					t_trigon;

typedef struct		s_qdron
{
	t_point			xp;
	t_vctr			v_tmp;
	t_vctr			v_r;
	t_vctr			v_up;
	t_vctr			v_cxp;
	float			alpha;
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

typedef struct		s_cylon
{
	t_point			o;
	t_point			o_p;
	t_point			o_nb;
	t_point			c;
	t_point			c_p;
	t_point			d;
	t_point			d_p;
	t_2d_point		d_nb;
	t_point			xp1;
	t_point			xp2;
	t_point			p;
	t_vctr2d		v_od_nb;
	t_vctr2d		v_oc_nb;
	t_vctr			v_d;
	t_vctr			v_od;
	t_vctr			v_oxp1;
	t_vctr			v_oxp2;
	t_vctr			v_o_c;
	t_vctr			v_p_c;
	t_pln			pln;
	float			ch_p;
	float			t1;
	float			t2;
	float			oh_p;
	float			hxp_p;
	float			oxp1_p;
	float			oxp2_p;
	float			angle;
	float			sin_alpha;
}					t_cylon;

typedef struct		s_oxp_calc
{
	t_vctr			v_ort;
	t_point			ort;
	t_2d_point		ort_nb;
	t_2d_point		o_nb;
	t_2d_point		c_nb;
	t_vctr2d		v_ort_o;
	t_vctr2d		v_ort_d;
	t_vctr2d		v_ort_c;
	float			tmp;
}					t_oxp_calc;

typedef struct		s_cap_pln
{
	t_vctr			v_cc1;
	t_vctr			v_cc2;
	t_vctr			v_oc1;
	t_vctr			v_oc2;
	t_point			c1;
	t_point			c2;
}					t_cap_pln;

typedef struct		s_sphr_intrsct
{
	t_vctr			oc;
	float			a;
	float			b;
	float			c;
	float			dscr;
	float			root;
}					t_sphr_intrsct;

typedef struct		s_check_val_coordinates
{
	double			dx;
	double			dy;
	double			dz;
	t_point			tp;
	t_point			hp;
	t_vctr			tmp;
}					t_check_val_coordinates;

typedef struct		s_lum
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

typedef	struct		s_vars
{
	void			*mlx;
	void			*win;
}					t_vars;

typedef struct		s_data
{
	void			*img;
	char			*addr;
	int				bits_per_pix;
	int				line_lngth;
	int				endian;
}					t_data;

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

typedef struct		s_set_rsltn
{
	unsigned int	scr_w;
	unsigned int	scr_h;
	float			ratio;
	float			orx;
	float			ory;
}					t_set_rsltn;

typedef struct		s_vldt
{
	int				r_cnt;
	int				a_cnt;
}					t_vldt;

void				check_argv(int argc, char **argv, char *save);
void				make_scn_arr(t_list **head, int size, char save);

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
void				nprsr_null_4(t_prsr *nprsr);

void				nprsr_null_6(t_prsr *nprsr);
void				nprsr_null_42(t_prsr *nprsr);
void				nprsr_nullt_fields(t_prsr *nprsr);
t_prsr				make_t_prsr(void);
void				strct_node(char **scn_arr, int size, char save);

void				prsr_assist(char *line, t_prsr *np, char *field, int n);
void				write_p(t_point *p, t_prsr *np);
void				write_v(t_vctr *v, t_prsr *np);
void				write_color(t_color *c, t_prsr *np);

void				set_rsltn(t_scn *nscn);
void				write_rsltn(t_scn *nscn, t_prsr *np);
void				write_ambnt(t_scn *nscn, t_prsr *np);
void				write_cam(t_scn *nscn, t_prsr *np);
void				write_lght(t_scn *nscn, t_prsr *np);

void				write_pln(t_scn *nscn, t_prsr *np);
void				write_sphr(t_scn *nscn, t_prsr *np);
void				write_cyl(t_scn *nscn, t_prsr *np);
void				write_sqr(t_scn *nscn, t_prsr *np);
void				write_trngl(t_scn *nscn, t_prsr *np);

void				prsr_rsltn(char *line, t_scn *nscn, t_prsr *np);
void				prsr_ambnt(char *line, t_scn *nscn, t_prsr *np);
void				prsr_cam(char *line, t_scn *nscn, t_prsr *np);
void				prsr_lght(char *line, t_scn *nscn, t_prsr *np);
void				prsr_sphr(char *line, t_scn *nscn, t_prsr *np);

void				prsr_pln(char *line, t_scn *nscn, t_prsr *np);
void				prsr_sqr_if(char *line, t_prsr *np);
void				prsr_sqr(char *line, t_scn *nscn, t_prsr *np);
void				prsr_cyl_if(char *line, t_prsr *np);
void				prsr_cyl(char *line, t_scn *nscn, t_prsr *np);

void				prsr_trngl_if(char *line, t_prsr *np);
void				prsr_trngl(char *line, t_scn *nscn, t_prsr *np);
void				prsr(char **scn_arr, int size, t_scn *nscn, t_prsr *np);

double				ft_atof(const char *str);

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

t_list				*ft_lstnew(void *content);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);

void				my_mlx_pixel_put(t_data *data, int x, int y, int color);
void				draw_from_arr(t_scn *nscn, t_data *data,
					unsigned int **arr);
int					key_hook(int keycode, t_scn *lscn);
int					close_mlx_win(int keycode, t_vars *vrs);

int					stop_ex(t_vars *vrs);
void				img2win(t_scn *nscn, unsigned int **arr);
void				mlx_node(t_scn *lscn, unsigned int **arr);

void				print_node(t_scn *nscn);
void				print_cam(t_scn *nscn);
void				print_light(t_scn *nscn);
void				print_pln(t_scn *nscn);
void				print_sphr(t_scn *nscn);
void				print_cyl(t_scn *nscn);
void				print_sqr(t_scn *nscn);
void				print_trngl(t_scn *nscn);

void				p2d_make(t_2d_point *out, int x, int y);
void				p_make(t_point *output, float x, float y, float z);
void				p_calc(t_point *out, t_vxyz *vctr, t_point *tail);
void				p_copy(t_point *out, t_point *in);
void				p3dt2d_conv(t_2d_point *out, float x, float y);

int					p_is_equal(t_point *p1, t_point *p2);
void				p2pln_prjctn(t_plnx *plnx, t_pln *pln, t_point *p);

void				v_xy(t_vxy *out, t_2d_point *tail, t_2d_point *head);
void				v2d_null(t_vctr2d *vctr);
void				v2d_lngth(t_vctr2d *vctr);

void				v2d_make(t_vctr2d *out, t_2d_point *tail, t_2d_point *head);
float				v2d_d_prdct(t_vxy *xy1, t_vxy *xy2);
float				v2d_pd_prdct(t_vctr2d *v_d, t_vctr2d *v_oc);

void				v_xyz(t_vxyz *out, t_point *tail, t_point *head);
void				v_lngth(t_vctr *vctr);
void				v_n(t_vctr *vctr);
void				v_null(t_vctr *nvctr);

void				v_fill(t_vctr *nvctr);
void				v_make(t_vctr *out, t_point *tail, t_point *head);
void				v_copy(t_vctr *out, t_vctr *in);
void				v_sum(t_vxyz *out, t_vxyz *vctr1, t_vxyz *vctr2);

void				v_sbtrct(t_vxyz *out, t_vxyz *vctr1, t_vxyz *vctr2);
void				v_n_prdct(t_vxyz *out, t_vxyz *vxyz, float num);
float				v_d_prdct(t_vxyz *xyz1, t_vxyz *xyz2);
float				v_x_point_prdct(t_vxyz *xyz, t_point *p);

void				v_crss_prdct(t_vxyz *out, t_vxyz *xyz1, t_vxyz *xyz2);
float				v_angle(t_vctr *vctr1, t_vctr *vctr2);
void				v_opposite(t_vctr *vctr);
float				v_are_collinear(t_vctr *v1, t_vctr *v2);

void				cnvs_node(t_scn *lscn);
void				cnvrse2crtsn(t_scn *lscn, t_2d_point *xy);
void				cnvrse2ncrtsn(t_scn *lscn, t_2d_point *xy);
void				cnvrse2xyz(t_point *out, t_scn *lscn, t_2d_point *xy);

void				trace_ray(t_scn *lscn, t_ray *ray);
void				ray_null(t_ray *ray);
unsigned long		cnvrse2trgb(t_color *trgb);
unsigned int		**make_rays_array(t_scn *lscn);
void				arr_ground_color(t_scn *lscn, unsigned int **rays_arr);

void				launch_rays(t_scn *lscn, unsigned int **rays_arr,
					t_ray *ray);
void				rays_node(t_scn *lscn, t_scn *nscn);

void				mtrx4_x_vctr(t_vctr *out, t_mtrx4x4 *mtrx, t_vxyz *in);
void				mtrx4_x_point(t_point *out, t_mtrx4x4 *mtrx, t_point *in);

void				null_lookat(t_look_at *lookat);
void				v_tmp_make(t_vctr *vf, t_vctr *tmp, t_look_at *lookat);
void				look_at_mtrx(t_look_at *lookat, t_vctr *v_f, t_point *p);
void				get_cam_fov(t_scn *nscn, t_scn *lscn);

void				cnvrse_lght(t_scn *nscn, t_scn *lscn, t_look_at *lookat);
void				cnvrse_pln(t_scn *nscn, t_scn *lscn, t_look_at *lookat);
void				cnvrse_sphr(t_scn *nscn, t_scn *lscn, t_look_at *lookat);
void				cnvrse_cyl(t_scn *nscn, t_scn *lscn, t_look_at *lookat);

void				cnvrse_sqr(t_scn *nscn, t_scn *lscn, t_look_at *lookat);
void				cnvrse_trngl(t_scn *nscn, t_scn *lscn, t_look_at *lookat);
void				cnvrse2local(t_scn *lscn, t_scn *nscn, int h);
void				lookat_node(t_scn *nscn, int h);

void				intrsct_node(t_scn *lscn, t_ray *ray);
void				check_objcts(t_scn *lscn, t_ray *ray);
void				check_lghts(t_scn *lscn, t_ray *ray);

void				l_ambnt(t_lum *lum);
void				l_dffse(t_lum *lum);
void				l_spclr(t_lum *lum);
void				l_all(t_scn *lscn, t_lum *lum);

void				make_lum(t_lum *lum, t_scn *lscn, t_lght *lght, t_ray *ray);
void				lum_sphr(t_scn *lscn, t_lght *lght, t_ray *ray);
void				lum_pln(t_scn *lscn, t_lght *lght, t_ray *ray);
void				lum_trngl(t_scn *lscn, t_lght *lght, t_ray *ray);

void				lum_sqr(t_scn *lscn, t_lght *lght, t_ray *ray);
void				lum_cyl(t_scn *lscn, t_lght *lght, t_ray *ray);
void				lum_node(t_scn *lscn, t_lght *lght, t_ray *ray);

void				nrml_sphr(t_vctr *nrml, t_ray *ray, t_sphr *sphr);
void				nrml_trngl(t_trngl *trngl, t_ray *ray);
void				nrml_pln(t_pln *pln, t_ray *ray);
void				nrml_sqr(t_sqr *sqr, t_ray *ray);
void				nrml_cyl(t_cyl *cyl, t_ray *ray);

float				q_equation(float *root, float a, float b, float c);
void				sphr_intrsct(t_scn *lscn, t_sphr *sphr, t_ray *ray);
void				check_sphrs(t_scn *lscn, t_ray *ray);

void				pln_null(t_pln *pln);
void				plnx_null(t_plnx *plnx);
void				pln_make(t_pln *pln, t_point *p, t_vctr *v);
t_plnx				pln_equation(t_point *p, t_point *r_orgn,
					t_vctr *nrml, t_vctr *ray);

void				pln_intrsct(t_scn *lscn, t_pln *pln, t_ray *ray);
void				check_plns(t_scn *lscn, t_ray *ray);

void				qdron_null(t_qdron *qdrn);
void				qdron_make(t_qdron *qdrn, t_sqr *sqr);
void				is_in_sqr(t_qdron *qdrn, t_sqr *sqr);
void				is_in_shdw(t_qdron *qdrn, t_sqr *sqr, t_ray *ray);

void				sqr_intrsct(t_scn *lscn, t_ray *ray,
					t_sqr *sqr, t_qdron *qdrn);
void				check_sqrs(t_scn *lscn, t_ray *ray);

void				trgn_null(t_trigon *trgn);
void				nrml_make(t_trngl *trngl);
void				xp_calc(t_trngl *trngl, t_ray *ray);
void				trgn_converse(t_trngl *trngl);
void				vctr2d_make(t_trngl *trngl);

void				is_in_trngl(t_trngl *trngl);
void				trgn_make(t_trngl *trngl, t_ray *ray);
void				trngl_intrsct(t_scn *lscn, t_trngl *trngl, t_ray *ray);
void				check_trngls(t_scn *lscn, t_ray *ray);

void				cylon_null_1(t_cylon *cln);
void				cylon_null(t_cylon *cln);
void				cap_pln(t_cylon *cln, t_cyl *cyl);
void				cylon_fill(t_cylon *cln, t_ray *ray, t_cyl *cyl);
void				cylon_cnvrse(t_cylon *cln, t_look_at *lkt);

void				pln_calc(t_cylon *cln);
void				cln_angles(t_cylon *cln);
void				ch_calc(t_cylon *cln, t_look_at *lkt);
void				calc_nrml_cyl(t_cylon *cln, t_cyl *cyl);
void				xp_cyl(t_cylon *cln);

void				oxp_calc(t_cylon *cln, t_look_at *lkt);
void				case1_2(t_cylon *cln, t_look_at *lkt);
void				case3(t_cylon *cln);
void				case4(t_cylon *cln);
void				is_on_cyl(t_cylon *cln, t_cyl *cyl, t_look_at *lkt);

void				find_roots(t_cylon *cln, t_cyl *cyl, t_look_at *lkt);
void				cylon_make(t_cylon *cln, t_ray *ray, t_cyl *cyl);
void				cyl_intrsct(t_scn *lscn, t_ray *ray,
					t_cyl *cyl, t_cylon *cln);
void				check_cyls(t_scn *lscn, t_ray *ray);

void				color_make(t_color *color, unsigned int r,
					unsigned int g, unsigned int b);
void				color_null(t_color *color);
void				color_copy(t_color *to, t_color *from);
void				to_cmyk(t_cmyk *out, t_color *trgb);
void				to_rgb(t_color *out, t_cmyk *cmyk);

void				sum_color(t_color *out, t_color *surface, t_color *light);
void				lvl_apply(t_color *out, t_color *in, t_lum *lum);
void				color_node(t_scn *lscn, t_ray *ray, t_lum *lum);

unsigned int		get_pddng(t_scn *nscn);
void				make_bmp_hdr(t_scn *nscn, int file_size, int fd);
void				pxl_put(unsigned int **arr, unsigned int h,
					unsigned int w, int fd);

void				pddng_put(int fd);
void				img2pic(t_scn *nscn, unsigned int **arr,
					unsigned int pddng, int fd);
void				bmp_node(t_scn *nscn, unsigned int **arr);

void				vldt_null(t_vldt *v);
void				check_keys(char *l, t_vldt *v);
void				p_marks_hndlr(char *l, int i);
void				check_delimeters(char *l);

void				n_arg(char *l, int n);
void				check_args(char *l);
void				check_line(char *line, t_vldt *v);
void				check_node(char **scn_arr, int size);

void				check_val_color(t_prsr *np);
void				check_val_coordinates(char *x, char *y, char *z, char v);
void				check_val_uint(char *n, int lim, char *mssg);
void				check_val_float(char *n, char pos, char *mssg);

void				check_val_rsltn(t_prsr *np);
void				check_val_ambnt(t_prsr *np);
void				check_val_cam(t_prsr *np);
void				check_val_lght(t_prsr *np);
void				check_val_pln(t_prsr *np);

void				check_val_sphr(t_prsr *np);
void				check_val_cyl(t_prsr *np);
void				check_val_sqr(t_prsr *np);
void				check_val_trngl(t_prsr *np);
void				check_values_node(t_prsr *np, char obj);

#endif
