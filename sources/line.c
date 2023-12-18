/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:35:57 by npirard           #+#    #+#             */
/*   Updated: 2023/12/15 17:43:33 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

void	rec_draw_line(t_line *line)
{
	if (line->it.x == line->b.x && line->it.y == line->b.y)
		return ;
	draw_pxl(line->data, line->it, line->color);
	if (line->dir.x && is_inside(line->it.x + line->dir.x, line->data->size_x)
		&& inter_line(line->it.x + line->dir.x, line->it.y, line))
		line->it.x += line->dir.x;
	else if (line->dir.y
		&& is_inside(line->it.y + line->dir.y, line->data->size_y)
		&& inter_line(line->it.x, line->it.y + line->dir.y, line))
		line->it.y += line->dir.y;
	rec_draw_line(line);
}
