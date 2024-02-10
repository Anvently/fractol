/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:05:12 by npirard           #+#    #+#             */
/*   Updated: 2024/02/10 18:44:06 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <math.h>
#include <pthread.h>
#include <libft.h>

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
		|| ((seg.a.x != seg.b.x) && (seg.a.y != seg.b.y)))
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

void	*draw_routine(void *data_ptr)
{
	t_data	*data = (t_data *)data_ptr;
	int		i;
	int		cells;
	t_coord	start;
	t_coord	dimensions;

	pthread_mutex_lock(&data->init_mutex);
	i = data->thread_i;
	data->thread_i = -1;
	pthread_mutex_unlock(&data->init_mutex);
	switch (data->nbr_threads)
	{
		case 4:
			cells = 2;
			break;
		case 16:
			cells = 4;
			break;
		case 64:
			cells = 8;
			break;
		case 256:
			cells = 16;
			break;
		case 1024:
			cells = 32;
			break;
		default:
		cells = 2;
			break;
	}
	dimensions.x = data->size_x / cells;
	dimensions.y = data->size_y / cells;
	start.x = (i % cells) * dimensions.x;
	start.y = (i / cells) * dimensions.y;
	draw_fractal(data, start, dimensions);
	return (NULL);
}

int	start_threads(t_data *data)
{
	unsigned int	i;
	int				thread_i;

	data->thread_ids = ft_calloc(data->nbr_threads, sizeof(pthread_t));
	if (!data->thread_ids && data->nbr_threads > 0)
		return (1);
	i = 0;
	while (i < data->nbr_threads)
	{
		data->thread_i = (int) i;
		if (pthread_create(&data->thread_ids[i++], NULL, draw_routine, data))
			return (1);
		do
		{
			usleep(10);
			pthread_mutex_lock(&data->init_mutex);
			thread_i = data->thread_i;
			pthread_mutex_unlock(&data->init_mutex);
		} while (thread_i >= 0);
	}
	return (0);
}

///Number of threads must be 1 or a multiple of 4.
int	threading_draw(t_data *data)
{
	unsigned int	i;

	if (data->nbr_threads == 0 || data->fractal == 2)
		draw_fractal(data, (t_coord){0, 0},
			(t_coord){data->size_x, data->size_y});
	if (data->fractal != 2)
	{
		if (data->nbr_threads > 1024
			|| (data->nbr_threads > 1 && data->nbr_threads % 4))
			return (1);
		start_threads(data);
		i = 0;
		while (i < data->nbr_threads && data->thread_ids[i])
			pthread_join(data->thread_ids[i++], NULL);
		if (data->thread_ids)
			free(data->thread_ids);
		data->thread_ids = NULL;
	}
	if (PRINT_FPS)
		pfps();
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}

int	draw_fractal(t_data *data, t_coord start, t_coord dimensions)
{
	if (data->img == NULL)
		return (0);
	if (data->fractal == 0)
		draw_fract_julia(data, data->z, &start, &dimensions);
	else if (data->fractal == 1)
		draw_fract_mandal(data, &start, &dimensions);
	else if (data->fractal == 2)
		draw_tree(data);
	return (0);
}
