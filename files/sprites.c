/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:25:58 by secullod          #+#    #+#             */
/*   Updated: 2020/12/11 09:26:01 by secullod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	order_sprites(t_cub3d *c)
{
	t_spr	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < c->numspr - 1)
	{
		j = i + 1;
		while (j < c->numspr)
		{
			if (c->sprite[i].d < c->sprite[j].d)
			{
				tmp = c->sprite[i];
				c->sprite[i] = c->sprite[j];
				c->sprite[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int		sprite_positions(t_cub3d *c)
{
	int		i;
	int		j;
	int		k;

	if (c->sprite != NULL)
		free(c->sprite);
	if (!(c->sprite = malloc(sizeof(t_spr) * c->numspr)))
		return (error("sprite position malloc"));
	i = 0;
	j = 0;
	while (j < c->map_y)
	{
		k = 0;
		while (k < c->map_x && c->map[j][k] != '\0')
		{
			if (c->map[j][k] == '2')
			{
				c->sprite[i].y = ((double)j + 0.5) * TILE;
				c->sprite[i++].x = ((double)k + 0.5) * TILE;
			}
			k++;
		}
		j++;
	}
	return (1);
}

void	draw_sprite(t_cub3d *c)
{
	int i;
	int y;
	int x;

	order_sprites(c);
	i = 0;
	while (i < c->numspr)
	{
		x = c->sprite[i].center_x - c->sprite[i].h / 2;
		c->x_offset = -1;
		while (++c->x_offset < c->sprite[i].h)
		{
			c->y_offset = -1;
			y = (c->res_y - c->sprite[i].h) / 2;
			while (++c->y_offset < c->sprite[i].h)
				draw_sprite_helper(c, y++, x, i);
			x++;
		}
		i++;
	}
}

void	draw_sprite_helper(t_cub3d *c, int y, int x, int i)
{
	double	texty;
	double	textx;

	if (y >= 0 && y < c->res_y && x >= 0 && x < c->res_x &&
	c->sprite[i].d < c->rays[x].dist)
	{
		texty = c->y_offset * (double)TILE / c->sprite[i].h;
		textx = c->x_offset * (double)TILE / c->sprite[i].h;
		if (!(c->spr[(int)texty * TILE + (int)textx] == BLANKPIX))
			draw_pixel(c, c->spr[(int)texty * TILE + (int)textx], y, x);
	}
}

void	ft_sprite(t_cub3d *c)
{
	double	pangle;
	double	start_angle;
	int		i;

	i = 0;
	while (i < c->numspr)
	{
		c->sprite[i].dx = c->sprite[i].x - c->x;
		c->sprite[i].dy = c->y - c->sprite[i].y;
		c->sprite[i].d = hypot(c->sprite[i].dy, c->sprite[i].dx);
		pangle = reset_angle(c->p_angle);
		c->sprite[i].angle = reset_angle(2 * PI -
		atan2(c->sprite[i].dy, c->sprite[i].dx));
		c->sprite[i].h = (int)(TILE / c->sprite[i].d *
		(c->res_x / 2) / tan(c->fov / 2));
		start_angle = reset_angle(pangle - c->fov / 2);
		if (c->sprite[i].angle < HALF_PI && start_angle > 1.5 * PI)
			c->sprite[i].angle += 2 * PI;
		else if (start_angle < HALF_PI && c->sprite[i].angle > 1.5 * PI)
			c->sprite[i].angle -= 2 * PI;
		c->sprite[i].delta = c->sprite[i].angle - start_angle;
		c->sprite[i].center_x = c->sprite[i].delta / c->angle_inc;
		i++;
	}
	draw_sprite(c);
}
