/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaktion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 19:42:53 by olaktion          #+#    #+#             */
/*   Updated: 2018/08/23 19:42:55 by olaktion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	choose_color(t_env *str, int diff)
{
	if (str->z >= str->min && str->z <= str->min + diff / 10)
		str->color = mlx_get_color_value(str->ptr, 0x81b8e1);
	else if (str->z >= str->min + diff / 10 && str->z < str->min + diff / 5)
		str->color = mlx_get_color_value(str->ptr, 0x94c8ef);
	else if (str->z >= str->min + diff / 5 &&
		str->z < str->min + 5 * diff / 10)
		str->color = mlx_get_color_value(str->ptr, 0xd8f3fe);
	else if (str->z >= str->min + 5 * diff / 10 &&
		str->z < str->min + 6 * diff / 10)
		str->color = mlx_get_color_value(str->ptr, 0xc0dbba);
	else if (str->z >= str->min + 6 * diff / 10 &&
		str->z < str->min + 7 * diff / 10)
		str->color = mlx_get_color_value(str->ptr, 0xacd3a6);
	else if (str->z >= str->min + 7 * diff / 10 &&
		str->z < str->min + 8 * diff / 10)
		str->color = mlx_get_color_value(str->ptr, 0xf6f2c3);
	else if (str->z >= str->min + 8 * diff / 10 &&
		str->z < str->min + 9 * diff / 10)
		str->color = mlx_get_color_value(str->ptr, 0xd3c692);
	else if (str->z >= str->min + 9 * diff / 10 &&
		str->z <= str->min + 10 * diff / 10)
		str->color = mlx_get_color_value(str->ptr, 0x806133);
}

void	add_point(t_env *str, int x, int y)
{
	int diff;

	diff = str->max - str->min;
	if (x >= 0 && y >= 0 && x < 1200 && y < 800)
	{
		choose_color(str, diff);
		*(unsigned int *)(str->pixl + x * (str->bpp / 8) +
			(y * str->size_line)) = str->color;
		str->pixl[x * (str->bpp / 8) + 3 + y * str->size_line] = str->t;
	}
}

void	draw_lines_wu(t_cord **xy, t_env *str)
{
	t_line l;

	l.x = 0;
	l.y = 0;
	while (l.y < str->count_y)
	{
		while (l.x < str->count_x - 1)
		{
			l.x0 = xy[l.y][l.x].x;
			l.x1 = xy[l.y][l.x + 1].x;
			l.y0 = xy[l.y][l.x].y;
			l.y1 = xy[l.y][l.x + 1].y;
			if (xy[l.y][l.x].z_b == 0)
				str->z = xy[l.y][l.x + 1].z_b;
			else
				str->z = xy[l.y][l.x].z_b;
			if (!xy[l.y][l.x].no_ex && !xy[l.y][l.x + 1].no_ex
				&& l.x0 < 1400 && l.x1 >= -100
				&& l.y0 < 1000 && l.y1 >= -100)
				draw_line(str, l);
			l.x++;
		}
		l.x = 0;
		l.y++;
	}
}

void	draw_lines_wu_upright(t_cord **xy, t_env *str)
{
	t_line l;

	l.x = 0;
	l.y = 0;
	while (l.y < str->count_y - 1)
	{
		while (l.x < str->count_x)
		{
			l.x0 = xy[l.y][l.x].x;
			l.x1 = xy[l.y + 1][l.x].x;
			l.y0 = xy[l.y][l.x].y;
			l.y1 = xy[l.y + 1][l.x].y;
			if (xy[l.y][l.x].z_b == 0)
				str->z = xy[l.y + 1][l.x].z_b;
			else
				str->z = xy[l.y][l.x].z_b;
			if (!xy[l.y][l.x].no_ex && !xy[l.y + 1][l.x].no_ex
				&& l.x0 < 1400 && l.x1 >= -100
				&& l.y0 < 1000 && l.y1 >= -100)
				draw_line(str, l);
			l.x++;
		}
		l.x = 0;
		l.y++;
	}
}

void	draw_line_hor(t_env *str, t_line line)
{
	if (line.x1 == line.x0)
	{
		if (line.y1 < line.y0)
			while (line.y1 < line.y0)
				add_point(str, line.x1, line.y1++);
		else if (line.y1 > line.y0)
			while (line.y1 > line.y0)
				add_point(str, line.x1, line.y1--);
	}
	else if (line.y1 == line.y0)
	{
		if (line.x1 < line.x0)
			while (line.x1 < line.x0)
				add_point(str, line.x1++, line.y1);
		else if (line.x1 > line.x0)
			while (line.x1 > line.x0)
				add_point(str, line.x1--, line.y1);
	}
}
