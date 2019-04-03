/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaktion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:18:27 by olaktion          #+#    #+#             */
/*   Updated: 2018/08/23 15:18:31 by olaktion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	draw_line2(t_env *str, t_line *line)
{
	if (line->x1 < line->x0)
	{
		line->x1 += line->x0;
		line->x0 = line->x1 - line->x0;
		line->x1 -= line->x0;
		line->y1 += line->y0;
		line->y0 = line->y1 - line->y0;
		line->y1 -= line->y0;
	}
	line->grad = (float)line->dy / line->dx;
	if (line->y1 < line->y0)
		line->intery = line->y0 - line->grad;
	else
		line->intery = line->y0 + line->grad;
	str->t = 0;
	add_point(str, line->x0, line->y0);
	line->x = line->x0 + 1;
}

void	draw_line3(t_env *str, t_line *line)
{
	while (line->x < line->x1)
	{
		if (str->wu)
		{
			str->t = (int)(f_part(line->intery) * 255);
			add_point(str, line->x, line->intery);
			str->t = (int)(255 - f_part(line->intery) * 255);
			add_point(str, line->x, line->intery + 1);
		}
		else
			add_point(str, line->x, line->intery);
		if (line->y1 < line->y0)
			line->intery -= line->grad;
		else
			line->intery += line->grad;
		line->x++;
	}
	str->t = 0;
	add_point(str, line->x1, line->y1);
}

void	draw_line4(t_env *str, t_line *line)
{
	if (line->y1 < line->y0)
	{
		line->x1 += line->x0;
		line->x0 = line->x1 - line->x0;
		line->x1 -= line->x0;
		line->y1 += line->y0;
		line->y0 = line->y1 - line->y0;
		line->y1 -= line->y0;
	}
	line->grad = (float)line->dx / line->dy;
	if (line->x1 < line->x0)
		line->interx = line->x0 - line->grad;
	else
		line->interx = line->x0 + line->grad;
	str->t = 0;
	add_point(str, line->x0, line->y0);
	line->y = line->y0 + 1;
}

void	draw_line5(t_env *str, t_line *line)
{
	while (line->y < line->y1)
	{
		if (str->wu)
		{
			str->t = (int)(f_part(line->interx) * 255);
			add_point(str, line->interx, line->y);
			str->t = (int)(255 - f_part(line->interx) * 255);
			add_point(str, line->interx + 1, line->y);
		}
		else
			add_point(str, line->interx, line->y);
		if (line->x1 < line->x0)
			line->interx -= line->grad;
		else
			line->interx += line->grad;
		line->y++;
	}
	str->t = 0;
	add_point(str, line->x1, line->y1);
}

void	draw_line(t_env *str, t_line line)
{
	line.dx = (line.x1 > line.x0) ? (line.x1 - line.x0) : (line.x0 - line.x1);
	line.dy = (line.y1 > line.y0) ? (line.y1 - line.y0) : (line.y0 - line.y1);
	if (line.dx == 0 || line.dy == 0)
	{
		draw_line_hor(str, line);
		return ;
	}
	if (line.dy < line.dx)
	{
		draw_line2(str, &line);
		draw_line3(str, &line);
	}
	else
	{
		draw_line4(str, &line);
		draw_line5(str, &line);
	}
}
