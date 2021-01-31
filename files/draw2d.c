/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:26:41 by secullod          #+#    #+#             */
/*   Updated: 2020/12/14 11:45:52 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player_2d(t_cub3d *c, int pos_x, int pos_y, int color)
{
	int		x;
	int		y;

	x = -RADIUS;
	y = -RADIUS;
	while (y <= RADIUS)
	{
		while (x <= RADIUS)
		{
			if (x * x + y * y < RADIUS * RADIUS + RADIUS)
				draw_pixel(c, color, (y + pos_y) / c->scale, (x + pos_x)
				/ c->scale);
			x++;
		}
		x = -RADIUS;
		y++;
	}
}

void	draw_ray_2d(t_cub3d *c, int ray_num)
{
	int		i;
	float	x;
	float	y;
	int		dx;
	int		dy;

	dx = c->rays[ray_num].wall_hit_x - c->x;
	dy = c->rays[ray_num].wall_hit_y - c->y;
	c->steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	x = c->x;
	y = c->y;
	i = 0;
	while (i <= c->steps)
	{
		draw_pixel(c, RCOLOR, y / c->scale, x / c->scale);
		x += dx / (float)c->steps;
		y += dy / (float)c->steps;
		i++;
	}
}

void	draw_view_2d(t_cub3d *c)
{
	double	ray_angle;
	int		ray_num;
	int		num_rays;

	ray_num = 0;
	ray_angle = c->p_angle - c->fov / 2;
	num_rays = c->res_x;
	while (ray_num < num_rays)
	{
		draw_ray_2d(c, ray_num);
		ray_angle += c->angle_inc;
		ray_num++;
	}
}

void	draw_map_2d(t_cub3d *c)
{
	int		x;
	int		y;
	int		col;
	int		row;

	y = 2;
	row = -1;
	while (++row < c->map_y)
	{
		x = 2;
		col = -1;
		while (++col < c->map_x && c->map[row][col] != '\0')
		{
			if (c->map[row][col] != ' ')
			{
				c->color = BCOLOR;
				draw_tile_2d(c, y - 2, x - 2, TILE);
				c->color = c->map[row][col] == '1' ? WCOLOR : MCOLOR;
				draw_tile_2d(c, y, x, TILE_SIZE);
			}
			x += TILE;
		}
		y += TILE;
	}
}

void	draw_tile_2d(t_cub3d *c, int x, int y, int size)
{
	int		xmax;
	int		ymax;

	xmax = x + size;
	ymax = y + size;
	while (x <= xmax)
	{
		while (y <= ymax)
		{
			draw_pixel(c, c->color, x / c->scale, y / c->scale);
			y++;
		}
		x++;
		y -= size;
	}
}
