/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 17:35:42 by npirard           #+#    #+#             */
/*   Updated: 2023/12/18 17:56:57 by npirard          ###   ########.fr       */
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

void draw_julia(t_data *data)
{
	//each iteration, it calculates: new = old*old + c, where c is a constant and old starts at current pixel
	double cRe, cIm;           //real and imaginary part of the constant c, determinate shape of the Julia Set
	double newRe, newIm, oldRe, oldIm;   //real and imaginary parts of new and old
	double zoom = 1, moveX = 0, moveY = 0; //you can change these to zoom and change position
	int maxIterations = 300; //after how much iterations the function should stop
	unsigned int color;

	//pick some values for the constant c, this determines the shape of the Julia Set
	cRe = -0.78;
	cIm = 0.15;

	//loop through every pixel
	for(int y = 0; y < data->size_y; y++)
	for(int x = 0; x < data->size_x; x++)
	{

		//calculate the initial real and imaginary part of z, based on the pixel location and zoom and position values
		newRe = 1.5 * (x - data->size_x / 2) / (0.5 * zoom * data->size_x) + moveX;
		newIm = (y - data->size_y / 2) / (0.5 * zoom * data->size_y) + moveY;
		printf("re = %f | img = %f\n", newRe,newIm);
		//i will represent the number of iterations
		int i;
		//start the iteration process
		for(i = 0; i < maxIterations; i++)
		{
			//remember value of previous iteration
			oldRe = newRe;
			oldIm = newIm;
			//the actual iteration, the real and imaginary part are calculated
			newRe = oldRe * oldRe - oldIm * oldIm + cRe;
			newIm = 2 * oldRe * oldIm + cIm;
			//if the point is outside the circle with radius 2: stop
			if((newRe * newRe + newIm * newIm) > 4) break;
		}
		//use color model conversion to get rainbow palette, make brightness black if maxIterations reached
		color = i*175;
		//draw the pixel
	t_coord	coord;
	coord.x = x;
	coord.y = y;
		draw_pxl(data, coord, color);
	}
}
