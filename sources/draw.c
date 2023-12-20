/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:05:12 by npirard           #+#    #+#             */
/*   Updated: 2023/12/20 15:30:26 by npirard          ###   ########.fr       */
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
	if (PRINT_FPS)
		pfps();
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
