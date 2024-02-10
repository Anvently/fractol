/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 11:29:40 by npirard           #+#    #+#             */
/*   Updated: 2024/02/10 18:14:35 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

/* static double	mod(t_complex z)
{
	return (z.re * z.re + z.img * z.img);
}

static t_complex	calc_next(t_complex current, t_complex constant)
{
	t_complex	new;

	new.re = (current.re * current.re) - (current.img * current.img);
	new.img = 2 * current.re * current.img;
	new.re += constant.re;
	new.img += constant.img;
	return (new);
} */

static void	fractal_check_pixel(t_data *data, t_coord coord,
				t_complex current, t_complex constant)
{
	int			i;
	double		re2;
	double		img2;

	re2 = current.re * current.re;
	img2 = current.img * current.img;
	i = 0;
	while (i < data->nbr_iterations && re2 + img2 < 4)
	{
		current.img = 2 * current.re * current.img - constant.img;
		current.re = re2 - img2 + constant.re;
		re2 = current.re * current.re;
		img2 = current.img * current.img;
		i++;
	}
	draw_pxl(data, coord, calc_color(data, i));
}

void	draw_fract_julia(t_data *data, t_complex constant, t_coord *start,
			t_coord *dimensions)
{
	t_coord		coord;
	t_complex	current;

	coord.y = start->y;
	while (coord.y < (dimensions->y + start->y))
	{
		coord.x = start->x;
		while (coord.x < (dimensions->x + start->x))
		{
			current.re = data->size_ratio * (coord.x - data->size_x * 0.5)
				* data->zoom_ratio_x + data->move_x;
			current.img = (coord.y - data->size_y * 0.5)
				* data->zoom_ratio_y + data->move_y;
			fractal_check_pixel(data, coord, current, constant);
			coord.x++;
		}
		coord.y++;
	}
}

void	draw_fract_mandal(t_data *data, t_coord *start,
			t_coord *dimensions)
{
	t_coord		coord;
	t_complex	constant;
	t_complex	current;

	coord.y = start->y;
	while (coord.y < (dimensions->y + start->y))
	{
		coord.x = start->x;
		while (coord.x < (dimensions->x + start->x))
		{
			constant.re = data->size_ratio * (coord.x - data->size_x * 0.5)
				* data->zoom_ratio_x + data->move_x;
			constant.img = (coord.y - data->size_y * 0.5)
				* data->zoom_ratio_y + data->move_y;
			current.re = 0.0;
			current.img = 0.0;
			fractal_check_pixel(data, coord, current, constant);
			coord.x++;
		}
		coord.y++;
	}
}
