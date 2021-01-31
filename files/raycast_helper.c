/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:34:45 by secullod          #+#    #+#             */
/*   Updated: 2020/12/11 09:34:47 by secullod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	reset_angle(double angle)
{
	angle = remainder(angle, 2 * PI);
	if (angle < 0)
		angle = 2 * PI + angle;
	return (angle);
}

void	face_direction(t_cub3d *c, double rayangle)
{
	c->face_down = 0;
	c->face_right = 0;
	if (rayangle > 0 && rayangle < PI)
		c->face_down = 1;
	if (rayangle < HALF_PI || rayangle > (PI + HALF_PI))
		c->face_right = 1;
}

void	face_direction_by_ray(t_cub3d *c, double ray_angle, int ray_num)
{
	c->face_down = 0;
	c->face_right = 0;
	c->rays[ray_num].face_down = 0;
	c->rays[ray_num].face_right = 0;
	if (ray_angle > 0 && ray_angle < PI)
	{
		c->face_down = 1;
		c->rays[ray_num].face_down = 1;
	}
	if (ray_angle < HALF_PI || ray_angle > (PI + HALF_PI))
	{
		c->face_right = 1;
		c->rays[ray_num].face_right = 1;
	}
}

int		detect_wall(t_cub3d *c, double x, double y)
{
	if (c->map[to_map_index(y)][to_map_index(x)] == '1')
		return (1);
	return (0);
}

int		to_map_index(double postion)
{
	return (int)floor(postion / TILE);
}
