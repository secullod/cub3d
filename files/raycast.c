/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:33:39 by secullod          #+#    #+#             */
/*   Updated: 2020/12/11 09:33:42 by secullod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		cast_rays(t_cub3d *c)
{
	double	ray_angle;
	int		raynum;
	int		numrays;

	raynum = 0;
	ray_angle = c->p_angle - c->fov / 2;
	numrays = c->res_x;
	if (!(c->rays = malloc(sizeof(t_ray) * numrays)))
		return (-1);
	while (raynum < numrays)
	{
		cast_ray(c, raynum, ray_angle);
		ray_angle += c->angle_inc;
		raynum++;
	}
	return (0);
}

void	cast_ray(t_cub3d *c, int ray_num, double ray_angle)
{
	c->hit_x = 0;
	c->hit_y = 0;
	c->hit_dist_x = (float)INT_MAX;
	c->hit_dist_y = (float)INT_MAX;
	ray_angle = reset_angle(ray_angle);
	face_direction(c, ray_angle);
	face_direction_by_ray(c, ray_angle, ray_num);
	wall_intersection_h(c, ray_angle);
	wall_intersection_v(c, ray_angle);
	if (c->hit_x == TRUE)
		c->hit_dist_x = hypot(c->touch_hx - c->x, c->touch_hy - c->y);
	if (c->hit_y == TRUE)
		c->hit_dist_y = hypot(c->touch_vx - c->x, c->touch_vy - c->y);
	set_ray_values(c, ray_num, ray_angle);
}

void	wall_intersection_h(t_cub3d *c, double ray_angle)
{
	c->touch_hy = to_map_index(c->y) * TILE + (c->face_down ? TILE : 0);
	c->touch_hx = c->x + (c->touch_hy - c->y) / tan(ray_angle);
	c->y_step = TILE * (c->face_down ? 1 : -1);
	c->x_step = TILE / tan(ray_angle);
	c->x_step *= (c->face_right && c->x_step < 0) ? -1 : 1;
	c->x_step *= (!c->face_right && c->x_step > 0) ? -1 : 1;
	while (c->touch_hx > 0 && c->touch_hx < c->winx && c->touch_hy > 0
	&& c->touch_hy < c->winy)
	{
		c->touch_hy = c->touch_hy + (c->face_down ? 0 : -.0001);
		if (detect_wall(c, c->touch_hx, c->touch_hy))
		{
			c->wall_cont_h = c->map[to_map_index(c->touch_hy)]
			[to_map_index(c->touch_hx)];
			c->hit_x = 1;
			break ;
		}
		else
		{
			c->touch_hx += c->x_step;
			c->touch_hy += c->y_step;
		}
	}
}

void	wall_intersection_v(t_cub3d *c, double ray_angle)
{
	c->touch_vx = to_map_index(c->x) * TILE + (c->face_right ? TILE : 0);
	c->touch_vy = c->y + (c->touch_vx - c->x) * tan(ray_angle);
	c->x_step = TILE * (c->face_right ? 1 : -1);
	c->y_step = TILE * tan(ray_angle);
	c->y_step *= (c->face_down && c->y_step < 0) ? -1 : 1;
	c->y_step *= (!c->face_down && c->y_step > 0) ? -1 : 1;
	while (c->touch_vx > 0 && c->touch_vx < c->winx && c->touch_vy > 0
	&& c->touch_vy < c->winy)
	{
		c->touch_vx = c->touch_vx + (c->face_right ? 0 : -.0001);
		if (detect_wall(c, c->touch_vx, c->touch_vy))
		{
			c->wall_cont_v = c->map[to_map_index(c->touch_vy)]
			[to_map_index(c->touch_vx)];
			c->hit_y = 1;
			break ;
		}
		else
		{
			c->touch_vx += c->x_step;
			c->touch_vy += c->y_step;
		}
	}
}

void	set_ray_values(t_cub3d *c, int ray_num, double ray_angle)
{
	if (c->hit_dist_y < c->hit_dist_x)
	{
		c->rays[ray_num].dist = c->hit_dist_y;
		c->rays[ray_num].wall_hit_x = c->touch_vx;
		c->rays[ray_num].wall_hit_y = c->touch_vy;
		c->rays[ray_num].hit_v = TRUE;
	}
	else
	{
		c->rays[ray_num].dist = c->hit_dist_x;
		c->rays[ray_num].wall_hit_x = c->touch_hx;
		c->rays[ray_num].wall_hit_y = c->touch_hy;
		c->rays[ray_num].hit_v = FALSE;
	}
	c->rays[ray_num].angle = ray_angle;
}
