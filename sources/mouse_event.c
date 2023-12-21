/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:56:56 by npirard           #+#    #+#             */
/*   Updated: 2023/12/21 16:16:34 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <X11/keysym.h>

void	switch_fractal(int x, int y, t_data *data, int fractal)
{
	if (fractal < 2)
	{
		data->z.re = data->size_ratio * (x - data->size_x * 0.5)
			* data->zoom_ratio_x + data->move_x;
		data->z.img = (y - data->size_y * 0.5)
			* data->zoom_ratio_y + data->move_y;
	}
	if (fractal == 2 && data->fractal == 2)
		data->fractal = 1;
	else
	{
		data->move_x = DFT_MOVE_X - 2;
		data->fractal = fractal;
	}
	data->zoom = DFT_ZOOM;
	data->move_x = DFT_MOVE_X * (data->fractal == 1);
	data->move_y = 0.0;
	data->zoom_ratio_x = 1.f / (data->size_x * 0.5 * data->zoom);
	data->zoom_ratio_y = 1.f / (data->size_y * 0.5 * data->zoom);
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
		data->move_x += ((2.f * x) / (float) data->size_x - 1)
			/ data->zoom * data->size_ratio;
		data->move_y += ((2.f * y) / (float) data->size_y - 1) / data->zoom;
		data->zoom *= 1.5;
		data->zoom_ratio_x = 1.f / (data->size_x * 0.5 * data->zoom);
		data->zoom_ratio_y = 1.f / (data->size_y * 0.5 * data->zoom);
	}
	else if (keycode == Button5)
	{
		data->move_x += ((2.f * x) / (float) data->size_x - 1)
			/ data->zoom * data->size_ratio;
		data->move_y += ((2.f * y) / (float) data->size_y - 1) / data->zoom;
		data->zoom /= 1.5;
		data->zoom_ratio_x = 1.f / (data->size_x * 0.5 * data->zoom);
		data->zoom_ratio_y = 1.f / (data->size_y * 0.5 * data->zoom);
	}
	return (0);
}

int	handle_button_release(int keycode, int x, int y, t_data *data)
{
	if (keycode == Button1)
		data->mouse_pressed = false;
	else if (keycode == Button3 && data->fractal < 2)
		switch_fractal(x, y, data, data->fractal != 1);
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
