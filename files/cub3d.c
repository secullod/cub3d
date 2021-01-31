/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:20:56 by secullod          #+#    #+#             */
/*   Updated: 2020/12/14 11:44:36 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_cub3d *c)
{
	int	i;

	i = -1;
	move_player(c);
	cast_rays(c);
	draw_view_3d(c);
	ft_sprite(c);
	draw_map_2d(c);
	draw_player_2d(c, c->x, c->y, PCOLOR);
	draw_view_2d(c);
	while (++i < c->numspr)
		draw_player_2d(c, c->sprite[i].x, c->sprite[i].y, SCOLOR);
	mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, c->img_ptr, 0, 0);
	free(c->rays);
}

void	init_helper_2(t_cub3d *c)
{
	c->map_err = 0;
	c->t_width = 0;
	c->t_height = 0;
	c->t_bits_per_pixel = 0;
	c->t_size_line = 0;
	c->t_endian = 0;
}

void	init_helper(t_cub3d *c)
{
	c->turn_dir = 0;
	c->turn_speed = 2 * PI / 180;
	c->walk_dir = 0;
	c->strafe = 0;
	c->map_y = 0;
	c->map_x = 0;
	c->res_y = 0;
	c->res_x = 0;
	c->numspr = 0;
	c->north = NULL;
	c->south = NULL;
	c->west = NULL;
	c->east = NULL;
	c->spr = NULL;
	c->floor = NONE;
	c->ceiling = NONE;
	c->win_ptr = NULL;
	c->map = NULL;
	c->p_angle = 0;
	c->n_ptr = 0;
	c->s_ptr = 0;
	c->w_ptr = 0;
	c->e_ptr = 0;
	c->spr_ptr = 0;
	init_helper_2(c);
}

int		init(char *cub, int bmp)
{
	t_cub3d	c;

	c.sprite = NULL;
	c.rays = NULL;
	c.filename = cub;
	c.mlx_ptr = mlx_init();
	c.fov = PI / 3;
	init_helper(&c);
	if (parse_cub_file(&c) == -1)
		return (ft_close(&c));
	scale_minimap(&c);
	c.win_ptr = mlx_new_window(c.mlx_ptr, c.res_x, c.res_y, "cub3D");
	c.img_ptr = mlx_new_image(c.mlx_ptr, c.res_x, c.res_y);
	c.addr = (unsigned int*)mlx_get_data_addr(c.img_ptr,
	&c.bits_per_pixel, &c.line_length, &c.endian);
	c.d_plane = (c.res_x / 2) / tan(c.fov / 2);
	c.angle_inc = c.fov / c.res_x;
	draw(&c);
	if (bmp == 1)
		ft_bitmap(&c);
	mlx_hook(c.win_ptr, 2, 1L << 0, key_press, &c);
	mlx_hook(c.win_ptr, 17, 1L << 17, ft_close, &c);
	mlx_loop(c.mlx_ptr);
	return (0);
}

int		main(int ac, char **av)
{
	if (ac == 3 && name_check(av[1], "cub") && save_check(av[2], "--save"))
		init(av[1], 1);
	else if (ac == 2 && name_check(av[1], "cub"))
		init(av[1], 0);
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
