/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:24:22 by secullod          #+#    #+#             */
/*   Updated: 2020/12/14 11:51:21 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			draw_pixel(t_cub3d *c, unsigned int color, int y, int x)
{
	c->addr[(int)(y) * c->res_x + (int)x] = color;
}

void			draw_view_3d(t_cub3d *c)
{
	int				x;
	int				y;
	unsigned int	*texture;

	x = 0;
	while (x < c->res_x)
	{
		c->dist_p = c->rays[x].dist * cos(c->rays[x].angle - c->p_angle);
		c->strip_h = (int)((TILE / c->dist_p) * c->d_plane);
		c->pixel_top = (c->res_y / 2) - (c->strip_h / 2);
		c->pixel_top = c->pixel_top < 0 ? 0 : c->pixel_top;
		c->pixel_bot = (c->res_y / 2) + (c->strip_h / 2);
		c->pixel_bot = c->pixel_bot > c->res_y ? c->res_y : c->pixel_bot;
		texture = get_texture(c, x);
		y = 0;
		while (y < c->res_y)
		{
			draw_view_3d_helper(c, x, y, texture);
			y++;
		}
		x++;
	}
}

void			draw_view_3d_helper(t_cub3d *c, int x, int y,
unsigned int *texture)
{
	if (c->rays[x].hit_v)
		c->text_offset_x = (int)c->rays[x].wall_hit_y % TILE;
	else
		c->text_offset_x = (int)c->rays[x].wall_hit_x % TILE;
	c->dist_top = y + (c->strip_h / 2) - (c->res_y / 2);
	c->text_offset_y = c->dist_top * ((float)TILE / c->strip_h);
	if (y < c->pixel_top)
		draw_pixel(c, c->ceiling, y, x);
	else if (y < c->pixel_bot)
		draw_pixel(c, texture[TILE * c->text_offset_y +
		c->text_offset_x], y, x);
	else
		draw_pixel(c, c->floor, y, x);
}

unsigned int	*get_texture(t_cub3d *c, int x)
{
	if (c->rays[x].hit_v == 0)
	{
		if (c->rays[x].face_down == 1)
			return (c->south);
		else if (c->rays[x].face_down == 0)
			return (c->north);
	}
	else if (c->rays[x].hit_v == 1)
	{
		if (c->rays[x].face_right == 1)
			return (c->east);
		else if (c->rays[x].face_right == 0)
			return (c->west);
	}
	return (0);
}

void			*t_error(char *message, char **file)
{
	if (file != NULL)
	{
		free(*file);
		*file = NULL;
	}
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}
