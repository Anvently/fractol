/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:10:44 by npirard           #+#    #+#             */
/*   Updated: 2023/12/21 15:37:12 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>

static void	data_init(t_data *data, int fractal)
{
	data->mlx = mlx_init();
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
	data->img = mlx_new_image(data->mlx, data->size_x, data->size_y);
	data->win = mlx_new_window(data->mlx, data->size_x,
			data->size_y, "Fractol");
	data->addr = mlx_get_data_addr(data->img, &data->bbp,
			&data->len_line, &data->endian);
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
	mlx_loop_hook(data->mlx, draw_fractal, data);
}

int	main(int argc, char **argv)
{
	t_data	data;
	int		fractal;

	if (argc != 2 || ft_strtoi(argv[1], &fractal) || fractal < 0 || fractal > 2)
	{
		ft_printf("Missing argument or invalid fractal number.\n"
			"Correct fractal number are :\n- 0 : julia set\n- 1 : mandelbrot\n"
			"- 2 : H tree\n");
		return (0);
	}
	ft_printf("\n\n%20s : %-20s\n%20s : %-20s\n%20s : %-20s\n"
		"%20s : %-20s\n%20s : %-20s\n%20s : %-20s\n%20s : %-20s\n\n",
		"Commands", "", "Left click", "Drag and drop",
		"Right click", "switch to a julia set's point",
		"Arrows <- ->", "navigate the fractal",
		"+/-", "increase/decrease iteration number.",
		"o/p", "change color palette", "t", "switch paint mode for h_tree",
		"g", "switch to bonus fractal");
	data_init(&data, fractal);
	hook_init(&data);
	mlx_loop(data.mlx);
	return (0);
}
