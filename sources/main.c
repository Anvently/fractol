/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:10:44 by npirard           #+#    #+#             */
/*   Updated: 2024/02/14 14:12:45 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <X11/X.h>

static void	data_init(t_data *data, int fractal)
{
	ft_memset(data, 0, sizeof(t_data));
	data->fractal = fractal;
	data->paint_mode = 0;
	data->size_x = SIZE_X;
	data->size_y = SIZE_Y;
	data->size_ratio = (float) data->size_x / (float) data->size_y;
	data->move_x = DFT_MOVE_X * (data->fractal == 1);
	data->move_y = 0;
	data->zoom = DFT_ZOOM;
	data->zoom_ratio_x = 1.f / (data->size_x * 0.5 * data->zoom);
	data->zoom_ratio_y = 1.f / (data->size_y * 0.5 * data->zoom);
	data->mouse_pressed = false;
	data->z.re = DFT_Z_RE;
	data->z.img = DFT_Z_IMG;
	data->nbr_iterations = DFT_ITERATION;
	data->color_factor = DFT_COLOR_FACTOR;
	data->nbr_threads = DFT_NBR_THREADS;
	pthread_mutex_init(&data->init_mutex, NULL);
}

static int	window_init(t_data *data)
{
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->img = mlx_new_image(data->mlx, data->size_x, data->size_y);
	data->win = mlx_new_window(data->mlx, data->size_x,
			data->size_y, "Fractol");
	data->addr = mlx_get_data_addr(data->img, &data->bbp,
			&data->len_line, &data->endian);
	if (!data->img || !data->win || !data->addr)
	{
		if (data->img)
			mlx_destroy_image(data->mlx, data->img);
		if (data->win)
			mlx_destroy_window(data->mlx, data->win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (1);
	}
	return (0);
}

static void	hook_init(t_data *data)
{
	mlx_hook(data->win, ButtonPress, ButtonPressMask,
		handle_button_press, data);
	mlx_hook(data->win, ButtonRelease, ButtonReleaseMask,
		handle_button_release, data);
	mlx_hook(data->win, KeyRelease, KeyReleaseMask, handle_key_release, data);
	mlx_hook(data->win, MotionNotify, PointerMotionMask,
		handle_mouse_move, data);
	mlx_hook(data->win, DestroyNotify, ButtonPressMask, handle_close, data);
	mlx_loop_hook(data->mlx, threading_draw, data);
}

static int	check_args(int argc, char **argv, int *fractal)
{
	if (argc != 2 || ft_strtoi(argv[1], fractal)
		|| *fractal < 0 || *fractal > 2)
	{
		ft_printf("Missing argument or invalid fractal number.\n"
			"Correct fractal number are :\n- 0 : julia set\n- 1 : mandelbrot\n"
			"- 2 : H tree\n");
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fractal;

	if (check_args(argc, argv, &fractal))
		return (0);
	data_init(&data, fractal);
	if (window_init(&data))
		return (1);
	ft_printf("\n\n%20s : %-20s\n%20s : %-20s\n%20s : %-20s\n%20s : %-20s\n"
		"%20s : %-20s\n%20s : %-20s\n%20s : %-20s\n%20s : %-20s\n%20s : %-20s\n\n",
		"Commands", "", "Left click", "Drag and drop",
		"Right click", "switch to a julia set's point", "Arrows <- ->",
		"navigate the fractal", "+/-", "increase/decrease iteration number.",
		":/! or [/]", "decrease/increase number of rendering threads",
		"o/p", "change color palette", "t", "switch paint mode for h_tree",
		"g", "switch to bonus fractal");
	hook_init(&data);
	mlx_loop(data.mlx);
	mlx_destroy_image(data.mlx, data.img);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
	return (0);
}
