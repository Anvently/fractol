/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 14:43:09 by npirard           #+#    #+#             */
/*   Updated: 2023/12/15 17:06:13 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <stdbool.h>

static bool	inter_abcd(t_coord a, t_coord b, t_coord c, t_coord d)
{
	long	det;
	long	t;

	det = (b.x - a.x) * (c.y - d.y) - (c.x - d.x) * (b.y - a.y);
	if (det == 0)
	{
		if ((a.x == c.x && a.y == c.y) || (a.x == d.x && a.y == d.y)
			|| (b.x == c.x && b.y == c.y) || (b.x == d.x && b.y == d.y))
			return (true);
		return (false);
	}
	t = (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
	if (t && ((t > 0 != det > 0) || (t > 0 && t > det) || (t < 0 && t < det)))
		return (false);
	return (true);
}

bool	inter_line(int x, int y, t_line *line)
{
	t_coord	c;
	t_coord	d;

	c.x = x;
	c.y = y;
	d.x = x + 1;
	d.y = y;
	if (inter_abcd(line->a, line->b, c, d))
		return (true);
	d.x = x;
	d.y = y + 1;
	if (inter_abcd(line->a, line->b, c, d))
		return (true);
	c = d;
	d.x = x + 1;
	if (inter_abcd(line->a, line->b, c, d))
		return (true);
	c.x = x + 1;
	c.y = y;
	if (inter_abcd(line->a, line->b, c, d))
		return (true);
	return (false);
}
