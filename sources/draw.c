/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:05:12 by npirard           #+#    #+#             */
/*   Updated: 2023/12/21 11:59:11 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <math.h>

void	draw_pxl(t_data *data, t_coord coord, int color)
{
	*(int *)(data->addr + (coord.y * data->len_line
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

void	draw_segment(t_data *data, t_segment seg, int color)
{
	t_coord	dir;

	if ((seg.a.x < 0 && seg.b.x < 0) || (seg.a.y < 0 && seg.b.y < 0)
		|| (seg.a.x > data->size_x && seg.b.x > data->size_x)
		|| (seg.a.y > data->size_y && seg.b.y > data->size_y)
		|| ((seg.a.x != seg.b.x ) && (seg.a.y != seg.b.y)))
		return ;
	dir.x = get_sign(seg.b.x - seg.a.x);
	dir.y = get_sign(seg.b.y - seg.a.y);
	while (seg.a.x != seg.b.x || seg.a.y != seg.b.y)
	{
		if (is_inside(seg.a.x, data->size_x)
			&& is_inside(seg.a.y, data->size_y))
			draw_pxl(data, seg.a, color);
		seg.a.y += dir.y;
		seg.a.x += dir.x;
	}
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
	else if (data->fractal == 1)
		draw_fract_mandal(data);
	else if (data->fractal == 2)
		draw_tree(data);
	if (PRINT_FPS)
		pfps();
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
