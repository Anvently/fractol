/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_tree.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 16:46:14 by npirard           #+#    #+#             */
/*   Updated: 2023/12/20 18:02:34 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <libft.h>
#include <math.h>

static void	clear_image(t_data *data)
{
	t_coord	coord;

	coord.x = 0;
	while (coord.x < data->size_x)
	{
		coord.y = 0;
		while (coord.y < data->size_y)
		{
			draw_pxl(data, coord, 0);
			coord.y++;
		}
		coord.x++;
	}
}

static int	get_orientation(t_segment seg)
{
	if (seg.b.x - seg.a.x >= 1)
		return (HORIZONTAL);
	else
		return (VERTICAL);
}

static t_segment	get_segment(t_coord p, int dimension, int orientation)
{
	t_segment	seg;

	if (orientation == HORIZONTAL)
	{
		seg.a.x = p.x - dimension / 2;
		seg.a.y = p.y;
		seg.b.x = p.x + dimension / 2;
		seg.b.y = p.y;
		return (seg);
	}
	seg.a.x = p.x;
	seg.a.y = p.y - dimension / 2;
	seg.b.x = p.x;
	seg.b.y = p.y + dimension / 2;
	return (seg);
}

static void	rec_tree(t_data *data, t_segment seg, int color)
{
	int			dimension;
	int			orientation;
	t_segment	seg1;
	t_segment	seg2;

	dimension = ft_max(seg.b.x - seg.a.x, seg.b.y - seg.a.y);
	draw_line(data, seg.a, seg.b, color);
	if (dimension < 1 || dimension < (data->nbr_iterations / 10))
		return ;
	orientation = get_orientation(seg);
	seg1 = get_segment(seg.a, dimension / sqrt(2), !orientation);
	seg2 = get_segment(seg.b, dimension / sqrt(2), !orientation);
	rec_tree(data, seg1, color * data->color_factor);
	rec_tree(data, seg2, color * data->color_factor);
}

int	draw_tree(t_data *data)
{
	t_segment	seg;
	int			dimension;

	if (!data->img)
		return (0);
	if (PRINT_FPS)
		pfps();
	dimension = data->size_x / 2;
	seg.a.x = (data->size_x - dimension) / 2;
	seg.a.y = data->size_y / 2;
	seg.b.x = dimension + (data->size_x - dimension) / 2;
	seg.b.y = data->size_y / 2;
	clear_image(data);
	rec_tree(data, seg, 0x00FF00FF);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
