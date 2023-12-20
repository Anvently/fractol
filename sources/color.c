/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 10:05:49 by npirard           #+#    #+#             */
/*   Updated: 2023/12/20 13:29:43 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>

/// @brief if i is great > zone is dark.
/// @param data
/// @param i
/// @return
int	calc_color(t_data *data, int i)
{
	return (i * data->color_factor);
}
