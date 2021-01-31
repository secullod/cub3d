/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:34:09 by secullod          #+#    #+#             */
/*   Updated: 2020/12/14 11:54:28 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_cub3d *c)
{
	float	movestep;
	float	xnew;
	float	ynew;

	movestep = c->walk_dir * SPEED;
	xnew = c->x + cos(c->p_angle + HALF_PI * c->strafe) * movestep;
	ynew = c->y + sin(c->p_angle + HALF_PI * c->strafe) * movestep;
	c->p_angle += c->turn_dir * c->turn_speed;
	if (!detect_wall(c, xnew, ynew))
	{
		c->x = xnew;
		c->y = ynew;
	}
	c->strafe = 0;
	c->turn_dir = 0;
	c->walk_dir = 0;
}

int		key_press(int keycode, t_cub3d *c)
{
	if (keycode == ESC)
		ft_close(c);
	else if (keycode == KEY_W)
		c->walk_dir = 1;
	else if (keycode == KEY_S)
		c->walk_dir = -1;
	else if (keycode == KEY_D)
	{
		c->walk_dir = 1;
		c->strafe = 1;
	}
	else if (keycode == KEY_A)
	{
		c->walk_dir = 1;
		c->strafe = -1;
	}
	else if (keycode == KEY_LEFT)
		c->turn_dir = -1;
	else if (keycode == KEY_RIGHT)
		c->turn_dir = 1;
	draw(c);
	return (0);
}

int		p_error(char *message, char **file, int fd)
{
	if (file != NULL)
	{
		free(*file);
		*file = NULL;
	}
	close(fd);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

int		ft_close(t_cub3d *c)
{
	int	i;

	i = 0;
	if (c->map != NULL)
	{
		while (i < c->map_y)
			free(c->map[i++]);
		free(c->map);
	}
	if (c->win_ptr != NULL)
	{
		mlx_destroy_image(c->mlx_ptr, c->s_ptr);
		mlx_destroy_image(c->mlx_ptr, c->n_ptr);
		mlx_destroy_image(c->mlx_ptr, c->e_ptr);
		mlx_destroy_image(c->mlx_ptr, c->w_ptr);
		mlx_destroy_image(c->mlx_ptr, c->spr_ptr);
		mlx_destroy_window(c->mlx_ptr, c->win_ptr);
		free(c->mlx_ptr);
	}
	exit(0);
	return (1);
}

void	scale_minimap(t_cub3d *c)
{
	c->winx = c->map_x * TILE;
	c->winy = c->map_y * TILE;
	c->xscale = ((float)c->res_x / (float)c->winx);
	c->yscale = ((float)c->res_y / (float)c->winy);
	if (c->yscale > c->xscale)
		c->scale = ((float)c->winx / (float)c->res_x) * (float)SCALE;
	else
		c->scale = ((float)c->winy / (float)c->res_y) * (float)SCALE;
	c->scale++;
	if (c->scale < 2)
		c->scale = 2;
}
