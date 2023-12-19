/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:05:12 by npirard           #+#    #+#             */
/*   Updated: 2023/12/19 18:12:05 by npirard          ###   ########.fr       */
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

int		draw_fractal(t_data *data)
{
	if (data->img == NULL)
		return (0);
	if (data->fractal == 0)
		draw_fract_julia(data, data->z);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

/* static double	mod(t_complex z)
{
	return (z.re * z.re + z.img * z.img);
} */

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



static int	calc_color(int i)
{
/* 	int	r;
	int i2;
	int	g;
	int	b;

	i2 = ((double) i / (double) NBR_ITERATION) * ((double) i / (double) NBR_ITERATION);
	r = exp(((double) i / (double) NBR_ITERATION)) * 100;
	g = (int) (exp(((double) i / (double) NBR_ITERATION)) * 100) % 300;
	b =  i2 * 200;
	printf("r = %d, g = %d, b = %d, i = %d\n", r, g, b, i);
	printf("rgb = %#x\n", (r << 16) | (g << 8) | b);
	return ((r << 16) | (g << 8) | b); */
	return (i * 600);
}

static void	julia_check_pixel(t_data *data, t_coord coord, t_complex constant)
{
	t_complex	current;
	int			i;

	current.re = (coord.x - data->size_x / 2.f)
		/ (data->size_x * 0.5 * data->zoom) + data->move_x;
	current.img = (coord.y - data->size_y / 2.f)
		/ (data->size_y * 0.5 * data->zoom) + data->move_y;
	i = 0;
	while (i < data->nbr_iterations)
	{
		current = calc_next(current, constant);
		if (mod2(current) > 2)
			break ;
		i++;
	}
	int color = calc_color(i);
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


