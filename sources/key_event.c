/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 13:19:17 by npirard           #+#    #+#             */
/*   Updated: 2023/12/20 11:28:52 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <X11/keysym.h>
#include <libft.h>

static void	handle_close(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_window(data->mlx, data->win);
	data->img = NULL;
	mlx_loop_end(data->mlx);
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

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		handle_close(data);
	else if (keycode == 65451)
		handle_plus(data);
	else if (keycode == 65453)
		handle_minus(data);
	else if (keycode == XK_p || keycode == XK_o)
		handle_zoom(keycode, data);
	return (0);
}

