/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:19:17 by npirard           #+#    #+#             */
/*   Updated: 2024/02/11 14:14:55 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <X11/keysym.h>
#include <pthread.h>
#include <libft.h>

int	handle_close(t_data *data)
{
	pthread_mutex_destroy(&data->init_mutex);

	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	mlx_loop_end(data->mlx);
	free(data->mlx);
	data->img = NULL;
	data->mlx = NULL;
	data->win = NULL;
	exit(0);
}

static void	handle_plus(t_data *data)
{
	data->nbr_iterations += 50;
	ft_printf("Nbr iterations = %d\n", data->nbr_iterations);
}

static void	handle_minus(t_data *data)
{
	data->nbr_iterations -= 50;
	ft_printf("Nbr iterations = %d\n", data->nbr_iterations);
}

static void	handle_zoom(int keycode, t_data *data)
{
	if (keycode == XK_p && data->color_factor)
		data->color_factor *= 2.5;
	else if (keycode == XK_p)
		data->color_factor = 1;
	else if (keycode == XK_o && data->color_factor)
		data->color_factor /= 2.5;
	else if (keycode == XK_o)
		data->color_factor = -1;
	ft_printf("Color factor = %d\n", data->color_factor);
}

static void	handle_threads_nbr(int keycode, t_data *data)
{
	if (keycode == 33)
	{
		if (data->nbr_threads == 0)
			data->nbr_threads = 1;
		else if (data->nbr_threads != 1024)
			data->nbr_threads *= 4;
	}
	else if (keycode == 58)
		data->nbr_threads /= 4;
	printf("%d threads\n", data->nbr_threads);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		handle_close(data);
	else if (keycode == 65451 || keycode == XK_plus || keycode == 61)
		handle_plus(data);
	else if (keycode == 65453 || keycode == XK_minus || keycode == 41)
		handle_minus(data);
	else if (keycode == XK_p || keycode == XK_o)
		handle_zoom(keycode, data);
	else if (keycode == XK_t)
		data->paint_mode = !data->paint_mode;
	else if (keycode == XK_g)
		switch_fractal(0, 0, data, 2);
	else if (keycode == XK_Right)
		data->move_x += 0.2 / data->zoom;
	else if (keycode == XK_Left)
		data->move_x -= 0.2 / data->zoom;
	else if (keycode == XK_Up)
		data->move_y -= 0.2 / data->zoom;
	else if (keycode == XK_Down)
		data->move_y += 0.2 / data->zoom;
	else if (keycode == 33 || keycode == 58)
		handle_threads_nbr(keycode, data);
	return (0);
}
