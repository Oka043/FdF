/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   act_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaktion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 19:42:13 by olaktion          #+#    #+#             */
/*   Updated: 2018/08/23 19:42:15 by olaktion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		malloc_struct2(t_cord **xy, t_env *str, t_map st)
{
	if (str->tab_z[st.y][st.x])
	{
		xy[st.y][st.x].z = ft_getnbr(str->tab_z[st.y][st.x]);
		max_min(xy[st.y][st.x].z, str);
		xy[st.y][st.x].z_b = xy[st.y][st.x].z;
		xy[st.y][st.x].z /= 3;
		xy[st.y][st.x].no_ex = 0;
	}
	else
		xy[st.y][st.x].no_ex = 1;
	xy[st.y][st.x].x = st.x;
	xy[st.y][st.x].y = st.y;
}

t_cord		**malloc_struct(t_env *str)
{
	t_map		st;
	t_cord		**xy;

	st.x = 0;
	st.y = 0;
	xy = malloc(sizeof(t_cord *) * str->count_y);
	while (st.y < str->count_y)
	{
		xy[st.y] = malloc(sizeof(t_cord) * str->count_x);
		while (st.x < str->count_x)
		{
			malloc_struct2(xy, str, st);
			st.x++;
		}
		st.x = 0;
		st.y++;
	}
	return (xy);
}

void		map_begin(t_env *str)
{
	str->dep_x = 100;
	str->dep_y = 400;
	str->dep_mp = 1;
	str->a = 0;
	str->b = 0;
	str->s = 0;
	str->zp = 1;
}

float		f_part(float x)
{
	while (x >= 0)
		x--;
	x++;
	return (x);
}
