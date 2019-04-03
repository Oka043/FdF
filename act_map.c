/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaktion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 19:41:50 by olaktion          #+#    #+#             */
/*   Updated: 2018/08/23 19:41:53 by olaktion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		img_action(t_env *str)
{
	mlx_destroy_image(str->ptr, str->img);
	mlx_clear_window(str->ptr, str->win);
	str->img = mlx_new_image(str->ptr, 1200, 800);
	map_action(str, str->xy, str->xy2);
	draw_lines_wu(str->xy2, str);
	draw_lines_wu_upright(str->xy2, str);
	put_text(str);
	mlx_put_image_to_window(str->ptr, str->win, str->img, 400, 0);
}

void		key_function1(int keycode, t_env *str)
{
	if (keycode == 0)
		str->b -= 0.1;
	else if (keycode == 2)
		str->b += 0.1;
	else if (keycode == 14)
		str->s -= 0.1;
	else if (keycode == 12)
		str->s += 0.1;
	else if (keycode == 7)
		str->zp -= 0.3;
	else if (keycode == 8)
		str->zp += 0.3;
	else if (keycode == 48)
		map_begin(str);
	else if (keycode == 27)
	{
		if (str->dep_mp - 0.3 > 0)
			str->dep_mp -= 0.3;
	}
	else if (keycode == 31)
		str->wu = 0;
	else if (keycode == 35)
		str->wu = 1;
	else if (keycode == 53)
		exit(0);
}

int			key_function(int keycode, void *param)
{
	t_env		*str;

	str = (t_env *)param;
	if (keycode == 1)
		str->a -= 0.1;
	else if (keycode == 13)
		str->a += 0.1;
	else if (keycode == 123)
		str->dep_x -= 50;
	else if (keycode == 124)
		str->dep_x += 50;
	else if (keycode == 125)
		str->dep_y += 50;
	else if (keycode == 126)
		str->dep_y -= 50;
	else if (keycode == 24)
		str->dep_mp += 0.3;
	else
		key_function1(keycode, str);
	img_action(str);
	return (0);
}

void		map_action2(t_env *str, t_cord **s, t_cord **s2, t_map m)
{
	if (s[m.y][m.x].z > 0 && (s[m.y][m.x].z + str->zp) >= s[m.y][m.x].z)
	{
		m.y1 = s[m.y][m.x].y * cos(str->a) -
		(s[m.y][m.x].z + str->zp) * sin(str->a);
		m.z1 = s[m.y][m.x].y * sin(str->a) +
		cos(str->a) * (s[m.y][m.x].z + str->zp);
	}
	else
	{
		if (s[m.y][m.x].z + str->zp < s[m.y][m.x].z)
			str->zp = 0;
		m.y1 = s[m.y][m.x].y * cos(str->a) - s[m.y][m.x].z * sin(str->a);
		m.z1 = s[m.y][m.x].y * sin(str->a) + cos(str->a) * s[m.y][m.x].z;
	}
	s2[m.y][m.x].x = m.x1;
	s2[m.y][m.x].y = m.y1;
	s2[m.y][m.x].z = m.z1;
	m.x1 = s2[m.y][m.x].x * cos(str->b) + s2[m.y][m.x].z * sin(str->b);
	m.z1 = s2[m.y][m.x].x * (-sin(str->b)) + s2[m.y][m.x].z * cos(str->b);
	s2[m.y][m.x].x = m.x1;
	s2[m.y][m.x].z = m.z1;
}

void		map_action(t_env *str, t_cord **s, t_cord **s2)
{
	t_map		m;

	m.x = 0;
	m.y = 0;
	while (m.y < str->count_y)
	{
		while (m.x < str->count_x)
		{
			m.x1 = s[m.y][m.x].x;
			map_action2(str, s, s2, m);
			m.x1 = s2[m.y][m.x].x * cos(str->s) - sin(str->s) * s2[m.y][m.x].y;
			m.y1 = s2[m.y][m.x].x * sin(str->s) + cos(str->s) * s2[m.y][m.x].y;
			s2[m.y][m.x].x = str->dep_x + str->dep_mp *
			(700 / str->count_x) * m.x1;
			s2[m.y][m.x].y = str->dep_y - (str->count_y *
				(400 / str->count_x)) + str->dep_mp *
			(700 / str->count_x) * m.y1;
			m.x++;
		}
		m.x = 0;
		m.y++;
	}
}
