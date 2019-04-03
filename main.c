/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olaktion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 15:19:15 by olaktion          #+#    #+#             */
/*   Updated: 2018/08/23 15:19:17 by olaktion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	main2(t_env *s, t_cord **xy, t_cord **xy2)
{
	s->img = mlx_new_image(s->ptr, 1200, 800);
	s->pixl = mlx_get_data_addr(s->img, &s->bpp, &s->size_line, &s->endian);
	xy = malloc_struct(s);
	xy2 = malloc_struct(s);
	s->xy = xy;
	s->xy2 = xy2;
	map_action(s, xy, xy2);
	draw_lines_wu(xy2, s);
	draw_lines_wu_upright(xy2, s);
	put_text(s);
}

int		main(int argc, char **argv)
{
	t_env		s;
	t_cord		**xy;
	t_cord		**xy2;

	xy = NULL;
	xy2 = NULL;
	if (argc != 2)
	{
		ft_putstrn("fdf: you need to enter just one argument");
		return (0);
	}
	str_init(&s);
	count_i(argv[1], &s);
	s.tab_z = read_file(argv[1], s.count_y);
	if (!(s.ptr = mlx_init()) ||
		!(s.win = mlx_new_window(s.ptr, 1600, 800, "fdf")))
		return (0);
	main2(&s, xy, xy2);
	mlx_put_image_to_window(s.ptr, s.win, s.img, 400, 0);
	mlx_hook(s.win, 2, (1L << 0), key_function, &s);
	mlx_loop(s.ptr);
	return (0);
}

void	put_text2(t_env *str)
{
	str->text = "X-axis Min        - Button S";
	mlx_string_put(str->ptr, str->win, 20, 180, 0xFFFFFF, str->text);
	str->text = "Y-axis Left       - Button A";
	mlx_string_put(str->ptr, str->win, 20, 200, 0xFFFFFF, str->text);
	str->text = "Y-axis Right      - Button D";
	mlx_string_put(str->ptr, str->win, 20, 220, 0xFFFFFF, str->text);
	str->text = "Z-axis Left       - Button Q";
	mlx_string_put(str->ptr, str->win, 20, 240, 0xFFFFFF, str->text);
	str->text = "Z-axis Right      - Button E";
	mlx_string_put(str->ptr, str->win, 20, 260, 0xFFFFFF, str->text);
	str->text = "Map Zoom +        - Button +";
	mlx_string_put(str->ptr, str->win, 20, 280, 0xFFFFFF, str->text);
	str->text = "Map Zoom -        - Button -";
	mlx_string_put(str->ptr, str->win, 20, 300, 0xFFFFFF, str->text);
	str->text = "Map Reset         - Button Tab";
	mlx_string_put(str->ptr, str->win, 20, 320, 0xFFFFFF, str->text);
	str->text = "Exit              - Button Esc";
	mlx_string_put(str->ptr, str->win, 20, 340, 0xFFFFFF, str->text);
	str->text = "Bresenham's algo  - Button O";
	mlx_string_put(str->ptr, str->win, 20, 360, 0xFFFFFF, str->text);
	str->text = "Xiaolin Wu's algo - Button P";
	mlx_string_put(str->ptr, str->win, 20, 380, 0xFFFFFF, str->text);
}

void	put_text(t_env *str)
{
	str->text = "Menu:";
	mlx_string_put(str->ptr, str->win, 20, 20, 0xFFFFFF, str->text);
	str->text = "Height Up         - Button C";
	mlx_string_put(str->ptr, str->win, 20, 40, 0xFFFFFF, str->text);
	str->text = "Height Down       - Button X";
	mlx_string_put(str->ptr, str->win, 20, 60, 0xFFFFFF, str->text);
	str->text = "Up Map            - Up arrow Button";
	mlx_string_put(str->ptr, str->win, 20, 80, 0xFFFFFF, str->text);
	str->text = "Down Map          - Down arrow Button";
	mlx_string_put(str->ptr, str->win, 20, 100, 0xFFFFFF, str->text);
	str->text = "Left map          - Left arrow Button";
	mlx_string_put(str->ptr, str->win, 20, 120, 0xFFFFFF, str->text);
	str->text = "Right Map         - Right arrow Button";
	mlx_string_put(str->ptr, str->win, 20, 140, 0xFFFFFF, str->text);
	str->text = "X-axis Plus       - Button W";
	mlx_string_put(str->ptr, str->win, 20, 160, 0xFFFFFF, str->text);
	put_text2(str);
}

void	str_init(t_env *str)
{
	str->dep_x = 100;
	str->dep_y = 400;
	str->dep_mp = 1;
	str->a = 0;
	str->b = 0;
	str->s = 0;
	str->wu = 0;
	str->min = 0;
	str->max = 0;
	str->count_y = 0;
	str->count_x = 0;
	str->t = 0;
	str->bpp = 0;
	str->size_line = 0;
	str->endian = 0;
	str->color = 0;
	str->z = 0;
	str->zp = 0;
	str->tab_z = NULL;
	str->ptr = NULL;
	str->win = NULL;
	str->img = NULL;
	str->pixl = NULL;
	str->xy = NULL;
	str->xy2 = NULL;
}
