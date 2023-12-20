/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npirard <npirard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 19:02:15 by npirard           #+#    #+#             */
/*   Updated: 2023/12/20 17:23:39 by npirard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define NBR_ITERATION 150
# define PRINT_FPS 1
# define HORIZONTAL 0
# define VERTICAL 1

# include <mlx.h>
# include <mlx_int.h>
# include <stdbool.h>

typedef struct s_coord {
	int		x;
	int		y;
}			t_coord;

typedef struct s_segment {
	t_coord	a;
	t_coord	b;
}			t_segment;

typedef struct s_complex {
	double	re;
	double	img;
}			t_complex;

typedef struct s_data {
	void			*img;
	void			*mlx;
	void			*win;
	char			*addr;
	int				bbp;
	int				len_line;
	int				endian;
	int				size_x;
	int				size_y;
	float			size_ratio;
	double			zoom;
	double			zoom_ratio_x;
	double			zoom_ratio_y;
	double			move_x;
	double			move_y;
	int				fractal;
	bool			mouse_pressed;
	t_coord			dnd;
	t_complex		z;
	int				nbr_iterations;
	unsigned int	color_factor;
}				t_data;

typedef struct s_line {
	t_coord	a;
	t_coord	b;
	t_coord	it;
	t_coord	dir;
	t_data	*data;
	int		color;
}			t_line;

void		draw_pxl(t_data *data, t_coord coord, int color);
void		draw_line(t_data *data, t_coord a, t_coord b, int color);
void		draw_rect(t_data *data, t_coord a, t_coord b, int color);
void		draw_fract_julia(t_data *data, t_complex constant);
void		draw_fract_mandal(t_data *data);
int			draw_fractal(t_data *data);
int			draw_tree(t_data *data);

int			calc_color(t_data *data, int i);

void		rec_draw_line(t_line *line);
bool		inter_line(int x, int y, t_line *line);

bool		is_inside(int pos, int size);
int			get_sign(int n);

int			handle_key_release(int keycode, t_data *data);
int 		handle_mouse_move(int x, int y, t_data *data);
int			handle_button_press(int keycode, int x, int y, t_data *data);
int			handle_button_release(int keycode, int x, int y, t_data *data);

void		pfps(void); //to remove

#endif
