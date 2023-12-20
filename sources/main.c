/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:10:44 by npirard           #+#    #+#             */
/*   Updated: 2023/12/20 17:36:12 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>

int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	data.fractal = 1;
	data.size_x = 1000;
	data.size_y = 1000;
	data.size_ratio = (float) data.size_x / (float) data.size_y;
	data.move_x = 0;
	data.move_y = 0;
	data.zoom = 1;
	data.zoom_ratio_x = 1.f / (data.size_x * 0.5 * data.zoom);
	data.zoom_ratio_y = 1.f / (data.size_y * 0.5 * data.zoom);
	data.mouse_pressed = false;
	data.z.re = -0.7;
	data.z.img = 0.45;
	data.nbr_iterations = NBR_ITERATION;
	data.color_factor = 200;
	data.img = mlx_new_image(data.mlx, data.size_x, data.size_y);
	data.win = mlx_new_window(data.mlx, data.size_x, data.size_y, "Fractol");
	data.addr = mlx_get_data_addr(data.img, &data.bbp,
			&data.len_line, &data.endian);

	mlx_hook(data.win, ButtonPress, ButtonPressMask, handle_button_press, &data);
	mlx_hook(data.win, ButtonRelease, ButtonReleaseMask, handle_button_release, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, handle_key_release, &data);
	mlx_hook(data.win, MotionNotify, PointerMotionMask, handle_mouse_move, &data);
	mlx_loop_hook(data.mlx, draw_tree, &data);
	mlx_loop(data.mlx);
	//mlx_destroy_display(data.mlx);
	return (0);
}
