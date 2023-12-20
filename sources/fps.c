/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 13:42:03 by npirard           #+#    #+#             */
/*   Updated: 2023/12/20 17:10:14 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>

void	pfps(void)
{
	static clock_t	tick;
	static int		fps;
	clock_t			tack;

	if (!tick)
	{
		tick = clock();
		fps++;
		return ;
	}
	tack = clock();
	if (tack - tick >= CLOCKS_PER_SEC)
	{
		tick = tack - ((tack - tick) - CLOCKS_PER_SEC);
		printf("%d FPS\n", fps);
		fps = 0;
	}
	else
		fps++;
}
