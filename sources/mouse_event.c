/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_event.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 17:56:56 by npirard           #+#    #+#             */
/*   Updated: 2023/12/19 18:00:36 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <X11/keysym.h>

int	handle_button_press(int keycode, int x, int y, t_data *data)
{
	(void) x;
	(void) y;
	if (keycode == Button1)
	{
		data->mouse_pressed = true;
		data->dnd.x = x;
		data->dnd.y = y;
	}
	else if (keycode == Button4)
	{
		data->move_x += ((double) x - ((double) data->size_x / 2.f))
			/ ((double) data->size_x / 2.f) / data->zoom;
		data->move_y += ((double) y - ((double) data->size_y / 2.f))
			/ ((double) data->size_y / 2.f) / data->zoom;
		data->zoom *= 1.33;
	}
	return (0);
}

int	handle_button_release(int keycode, int x, int y, t_data *data)
{
	(void) x;
	(void) y;
	if (keycode == Button1)
		data->mouse_pressed = false;
	else if (keycode == Button5)
	{
		data->move_x += ((double) x - ((double) data->size_x / 2.f))
			/ ((double) data->size_x / 2.f) / data->zoom;
		data->move_y += ((double) y - ((double) data->size_y / 2.f))
			/ ((double) data->size_y / 2.f) / data->zoom;
		data->zoom *= 0.66;
	}
	return (0);
}

int	handle_mouse_move(int x, int y, t_data *data)
{
	if (data->mouse_pressed)
	{
		data->move_x -= (((double) x - (double) data->dnd.x)
				/ (double) data->size_x / 2.f) / data->zoom;
		data->move_y -= (((double) y - (double) data->dnd.y)
				/ (double) data->size_y / 2.f) / data->zoom;
		data->dnd.x = x;
		data->dnd.y = y;
		//printf("Mouse move on %d, %d\nmove_x =  %f | move_y = %f\n", x, y, data->move_x, data->move_y);
	}
	return (0);
}
