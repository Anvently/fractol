/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:56:56 by npirard           #+#    #+#             */
/*   Updated: 2023/12/20 15:21:00 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <X11/keysym.h>

static void	switch_fractal(int x, int y, t_data *data)
{
	data->fractal = data->fractal != 1;
	data->zoom = 1;
	data->move_x = 0.0;
	data->move_y = 0.0;
	data->z.re = ((float) data->size_x / (float) data->size_y)
		* (x - data->size_x / 2.f)
		/ (data->size_x * 0.5 * data->zoom) + data->move_x;
	data->z.img = (y - data->size_y / 2.f)
		/ (data->size_y * 0.5 * data->zoom) + data->move_y;
}

int	handle_button_press(int keycode, int x, int y, t_data *data)
{
	if (keycode == Button1)
	{
		data->mouse_pressed = true;
		data->dnd.x = x;
		data->dnd.y = y;
	}
	else if (keycode == Button4)
	{
		data->move_x += ((2.f * x) / (float) data->size_x - 1) / data->zoom;
		data->move_y += ((2.f * y) / (float) data->size_y - 1) / data->zoom;
		data->zoom *= 2;
		data->zoom_ratio_x = 1.f / (data->size_x * 0.5 * data->zoom);
		data->zoom_ratio_y = 1.f / (data->size_y * 0.5 * data->zoom);
	}
	return (0);
}

int	handle_button_release(int keycode, int x, int y, t_data *data)
{
	if (keycode == Button1)
		data->mouse_pressed = false;
	else if (keycode == Button3)
		switch_fractal(x, y, data);
	else if (keycode == Button5)
	{
		data->move_x += ((2.f * x) / (float) data->size_x - 1) / data->zoom;
		data->move_y += ((2.f * y) / (float) data->size_y - 1) / data->zoom;
		data->zoom /= 2;
		data->zoom_ratio_x = 1.f / (data->size_x * 0.5 * data->zoom);
		data->zoom_ratio_y = 1.f / (data->size_y * 0.5 * data->zoom);
	}
	return (0);
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	if (data->mouse_pressed)
	{
		data->move_x -= ((double)(x - data->dnd.x)
				/ data->size_x / 2.f) / data->zoom;
		data->move_y -= ((double)(y - data->dnd.y)
				/ data->size_y / 2.f) / data->zoom;
		data->dnd.x = x;
		data->dnd.y = y;
	}
	return (0);
}
