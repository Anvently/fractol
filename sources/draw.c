/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:05:12 by npirard           #+#    #+#             */
/*   Updated: 2023/12/18 18:46:05 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <math.h>

void	draw_pxl(t_data *data, t_coord coord, int color)
{
	*(long *)(data->addr + (coord.y * data->len_line
				+ coord.x * (data->bbp / 8))) = color;
}

void	draw_line(t_data *data, t_coord a, t_coord b, int color)
{
	t_line	line;

	line.dir.x = get_sign(b.x - a.x);
	line.dir.y = get_sign(b.y - a.y);
	if (!line.dir.x && !line.dir.y)
		return ;
	line.it.x = a.x;
	line.it.y = a.y;
	line.a = a;
	line.b = b;
	line.color = color;
	line.data = data;
	rec_draw_line(&line);
}

void	draw_rect(t_data *data, t_coord a, t_coord b, int color)
{
	t_coord	pxl;

	pxl.x = a.x;
	while (pxl.x < b.x)
	{
		pxl.y = a.y;
		while (pxl.y < b.y)
		{
			draw_pxl(data, pxl, color);
			pxl.y++;
		}
		pxl.x++;
	}
}

static double	mod(t_complex z)
{
	return (z.re * z.re + z.img * z.img);
}

static double	mod2(t_complex z)
{
	return sqrt((z.re * z.re + z.img * z.img));
}

static t_complex calc_next(t_complex current, t_complex constant)
{
	t_complex	new;

	new.re = (current.re * current.re) - (current.img * current.img);
	new.img = 2 * current.re * current.img;
	new.re += constant.re;
	new.img += constant.img;
	return (new);
}

static long	calc_color(int i, t_complex z)
{
	double			n;
	long	color;

	n = log2(mod(z));
	if (n > 1.f)
		color = (long)((float) i - log2(log2(mod(z))));
	else
		color = (long)((float) i - log2(1.f));
	color *= 633;
	/* if (color > 71)
		return (color);
	else if (color > 155)
		return (color | 0x0000FF00);
	else
		return (color | 0x00FF0000); */
	return (color);
}

static void	julia_check_pixel(t_data *data, t_coord coord, t_complex constant)
{
	t_complex	current;
	int			i;

	current.re = 1.5 * (coord.x - data->size_x / 2.f)
		/ (data->size_x * 0.5 * data->zoom) + data->move_x;
	current.img = (coord.y - data->size_y / 2.f)
		/ (data->size_y * 0.5 * data->zoom) + data->move_y;
	i = 0;
	while (i < 300)
	{
		current = calc_next(current, constant);
		if (mod2(current) > 2)
			break ;
		i++;
	}
	long color = calc_color(i, current);
	draw_pxl(data, coord, color);
}

void	draw_fract_julia(t_data *data, t_complex constant)
{
	t_coord	coord;

	coord.y = 0;
	while (coord.y < data->size_y)
	{
		coord.x = 0;
		while (coord.x < data->size_x)
		{
			julia_check_pixel(data, coord, constant);
			coord.x++;
		}
		coord.y++;
	}
}


