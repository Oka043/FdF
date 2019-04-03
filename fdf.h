/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaktion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 14:52:08 by olaktion          #+#    #+#             */
/*   Updated: 2018/08/23 14:52:17 by olaktion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include "get_next_line.h"
# include <math.h>

typedef struct		s_cord
{
	double		x;
	double		y;
	double		z;
	double		z_b;
	int			x_max;
	int			no_ex;
}					t_cord;

typedef struct		s_map
{
	int			x;
	int			y;
	double		z;
	double		x1;
	double		y1;
	double		z1;
}					t_map;

typedef struct		s_env
{
	int				min;
	int				max;
	int				count_y;
	int				count_x;
	int				wu;
	int				t;
	int				dep_x;
	int				dep_y;
	int				bpp;
	int				size_line;
	int				endian;
	unsigned int	color;
	double			a;
	double			b;
	double			s;
	double			z;
	double			zp;
	double			dep_mp;
	char			***tab_z;
	void			*ptr;
	void			*win;
	void			*img;
	char			*pixl;
	t_cord			**xy;
	t_cord			**xy2;
	char			*text;
}					t_env;

typedef struct		s_line
{
	float			grad;
	float			intery;
	float			interx;
	int				dx;
	int				dy;
	int				x;
	int				y;
	int				x0;
	int				x1;
	int				y0;
	int				y1;
}					t_line;

char				***read_file(char *file, int count);
void				count_i(char *file, t_env *str);
int					**ft_tab_xy(char ***map, int count);
t_cord				**malloc_struct(t_env *str);
void				line_rightup(t_cord **xy, t_env str);
void				put_horisontal(t_cord **xy, t_env str);
int					words(char *str, char c);
void				put_segment(t_cord **xy, t_env str);
void				map_action(t_env *str, t_cord **xy,
	t_cord **xy2);
float				fpart(float x);
void				draw_line(t_env *str, t_line line);
void				draw_line_hor(t_env *str, t_line line);
void				draw_lines_wu(t_cord **xy, t_env *str);
void				draw_lines_wu_upright(t_cord **xy, t_env *str);
float				f_part(float x);
int					key_function(int keycode, void *param);
void				key_function1(int keycode, t_env *str);
void				str_init(t_env *str);
void				put_text(t_env *str);
void				put_text2(t_env *str);
void				map_begin(t_env *str);
void				add_point(t_env *str, int x, int y);
void				free_map(t_env *str);
float				f_part(float x);
void				img_action(t_env *str);
void				max_min(int z, t_env *str);
int					words(char *str, char c);
void				fdf_error(char *file);

#endif
