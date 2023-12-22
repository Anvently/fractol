/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:35:42 by npirard           #+#    #+#             */
/*   Updated: 2023/12/22 12:02:30 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

bool	is_inside(int pos, int size)
{
	if (pos < 0 || pos > size)
		return (false);
	return (true);
}

int	get_sign(int n)
{
	if (n > 0)
		return (1);
	else if (n < 0)
		return (-1);
	else
		return (0);
}
