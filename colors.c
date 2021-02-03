typedef struct		s_color
{
	unsigned int	t;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}					t_color;

typedef struct		s_cmyk
{
	unsigned int	c;
	unsigned int	m;
	unsigned int	y;
	unsigned int	k;
}					t_cmyk;

unsigned int	max(unsigned int a, unsigned int b, unsigned int c)
{
	if (a > b && a > c)
		return (a);
	if (b > a && b > c)
		return (b);
	if (c > a && c > b)
		return (c);
}

void	to_cmyk(t_cmyk *out, t_color *trgb)
{
	float r_;
	float g_;
	float b_;

	r_ = trgb->r / 255;
	g_ = trgb->g / 255;
	b_ = trgb->b / 255;
	out->k = 1 - max(trgb->r, trgb->g, trgb->b);
	out->c = (1 - r_ - out->k) / (1 - out->k);
	out->m = (1 - g_ - out->k) / (1 - out->k);
	out->y = (1 - b_ - out->k) / (1 - out->k);
}

void	to_rgb(t_color *out, t_cmyk *cmyk)
{
	out->r = 255 * (1 - cmyk->c) * (1 - cmyk->k);
	out->g = 255 * (1 - cmyk->m) * (1 - cmyk->k);
	out->b = 255 * (1 - cmyk->y) * (1 - cmyk->k);
}

void	add_color(t_color *out, t_color *surface, t_color *light)
{
	t_cmyk	srfc;
	t_cmyk	lght;

	to_cmyk(&srfc, surface);
	to_cmyk(&lght, light);


}