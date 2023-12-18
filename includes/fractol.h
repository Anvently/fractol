/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:02:15 by npirard           #+#    #+#             */
/*   Updated: 2023/12/18 17:42:43 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <mlx_int.h>
# include <stdbool.h>

typedef struct s_complex {
	double	re;
	double	img;
}			t_complex;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bbp;
	int		len_line;
	int		endian;
	int		size_x;
	int		size_y;
	double	zoom;
	double	move_x;
	double	move_y;
}			t_data;

typedef struct s_coord {
	int		x;
	int		y;
}			t_coord;

typedef struct s_line {
	t_coord	a;
	t_coord	b;
	t_coord	it;
	t_coord	dir;
	t_data	*data;
	int		color;
}			t_line;

void	draw_pxl(t_data *data, t_coord coord, int color);
void	draw_line(t_data *data, t_coord a, t_coord b, int color);
void	draw_rect(t_data *data, t_coord a, t_coord b, int color);
void 	draw_julia(t_data *data);
void	draw_fract_julia(t_data *data, t_complex constant);

void	rec_draw_line(t_line *line);
bool	inter_line(int x, int y, t_line *line);

bool	is_inside(int pos, int size);
int		get_sign(int n);

#endif
