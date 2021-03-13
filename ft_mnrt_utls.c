/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mnrt_utls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:05:55 by rburton           #+#    #+#             */
/*   Updated: 2021/03/13 12:19:59 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minirt.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*mem;

	mem = s;
	i = -1;
	while (++i < n)
		mem[i] = '\0';
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*pntr;

	pntr = (void *)malloc(count * size);
	if (NULL == pntr)
		return (NULL);
	ft_bzero(pntr, count * size);
	return (pntr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sjn;
	int		i;
	int		lens1;
	int		lens2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (!(sjn = (char*)malloc((lens1 + lens2 + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < lens1)
	{
		sjn[i] = s1[i];
		i++;
	}
	while (i < (lens1 + lens2))
	{
		sjn[i] = s2[i - lens1];
		i++;
	}
	sjn[i] = '\0';
	return (sjn);
}

int		w2l(int fd, char *buf, char **line)
{
	int		rv;
	char	*lineleak;

	while (1)
	{
		rv = read(fd, buf, 1);
		if (rv < 0)
			return (-1);
		else if (rv == 0)
			return (0);
		else
		{
			if (*buf == '\n')
				return (1);
			else
			{
				lineleak = *line;
				*line = ft_strjoin(*line, buf);
				free(lineleak);
			}
		}
	}
}

int		get_next_line(int fd, char **line)
{
	static char		buf;
	int				rv;

	if (!(*line = malloc(1)))
		return (-1);
	**line = 0;
	rv = w2l(fd, &buf, line);
	return (rv);
}

long int	ft_atoi(const char *str)
{
	size_t					i;
	int						sign;
	unsigned long long int	number;

	i = 0;
	number = 0;
	sign = 1;
	while (str[i] == 32 || str[i] == '\t' || str[i] == '\v' || str[i] == '\f' || str[i] == '\r' || str[i] == '\n')
		i++;
	if (str[i] == 45 || str[i] == 43)
	{
		if (str[i] == 45)
			sign *= (-1);
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		number = number * 10 + (str[i] - 48);
		i++;
	}
	number > 9223372036854775807 && sign > 0 ? number = -1 : 0;
	number > 9223372036854775807 && sign < 0 ? number = 0 : 0;
	return (sign * (long int)number);
}

int		ft_isalpha(int c)
{
	if ((c > 64 && c < 91) || (c > 96 && c < 123))
		return (1);
	else
		return (0);
}

int		ft_isdigit(int c)
{
	if (c > 47 && c < 58)
		return (1);
	else
		return (0);
}

float	max_2floats(float f1, float f2)
{
	if (f1 >= f2)
		return (f1);
	else
		return (f2);
}

float	max_3floats(float a, float b, float c)
{
	float	max;

	if (a >= b && a >= c)
		max = a;
	if (b >= a && b >= c)
		max = b;
	if (c >= a && c >= b)
		max = c;
	return (max);
}

// unsigned int	max_3uints(unsigned int a, unsigned int b, unsigned int c)
// {
// 	unsigned int	max;

// 	if (a >= b && a >= c)
// 		max = a;
// 	if (b >= a && b >= c)
// 		max = b;
// 	if (c >= a && c >= b)
// 		max = c;
// 	return (max);
// }

// unsigned int	min_2uints(unsigned int a, unsigned int b)
// {
// 	if (a <= b)
// 		return (a);
// 	else
// 		return (b);
// }

float	min_2floats(float a, float b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	err_message(char *error)
{
    write(1, error, ft_strlen(error));
    write(1, "\n", 1);
    exit(0);
}

int		ft_strcmp(char *s1, char *s2)
{
	int		i;
	int		output;

	i = 0;
	output = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			break ;
		else
			i++;
	}
	output = (unsigned char)s1[i] - (unsigned char)s2[i];
	return (output);
}