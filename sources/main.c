/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 09:10:44 by npirard           #+#    #+#             */
/*   Updated: 2023/12/18 18:04:11 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	void	*mlx;
	void	*mlx_img;
	void	*mlx_win;
	t_data	data;

	mlx = mlx_init();
	data.size_x = 1920;
	data.size_y = 1080;
	data.move_x = 0.000;
	data.move_y = 0.000;
	data.zoom = 1;
	t_complex constant = {-0.78, 0.15};
	mlx_img = mlx_new_image(mlx, data.size_x, data.size_y);
	mlx_win = mlx_new_window(mlx, data.size_x, data.size_y, "Fractol");
	data.addr = mlx_get_data_addr(mlx_img, &data.bbp,
			&data.len_line, &data.endian);

/* 	t_coord a = {1920, 0};
	t_coord b = {0, 1080};
	draw_line(&data, a, b, 0x000000FF);
	t_coord a1 = {0, 0};
	t_coord b1 = {1920, 1080};
	draw_line(&data, a1, b1, 0x000000FF);
	t_coord sqrA = {50, 50};
	t_coord sqrB = {550, 550};
	draw_rect(&data, sqrA, sqrB, 0x00FF0000); */
	//draw_julia(&data);
	draw_fract_julia(&data, constant);
	mlx_put_image_to_window(mlx, mlx_win, mlx_img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
