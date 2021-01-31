/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:21:08 by secullod          #+#    #+#             */
/*   Updated: 2020/12/11 09:22:05 by secullod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		map(t_cub3d *c, char *line, int *i)
{
	char	**tmp;
	int		j;

	c->map_err = 1;
	if (!(tmp = malloc(sizeof(char *) * (c->map_y + 2))))
		return (error("Error : Malloc fail (map table)"));
	j = -1;
	while (++j < c->map_y)
		tmp[j] = c->map[j];
	if ((tmp[c->map_y] = insert_row(c, line, i)) == NULL)
	{
		free(tmp);
		return (-1);
	}
	tmp[c->map_y + 1] = NULL;
	if (c->map_y > 0)
		free(c->map);
	c->map = tmp;
	c->map_y++;
	if (c->map_y <= 1)
		c->map_x = line_length(line);
	if (c->map_x != line_length(line))
		return (error("Error : incomplete map (map table)"));
	return (0);
}

int		map_check(t_cub3d *c)
{
	if (map_check_h(c) == -1)
		return (error("Error : Map isn't surrounded by walls (X)"));
	else if (map_check_y(c) == -1)
		return (error("Error : Map isn't surrounded by walls (Y)"));
	else
		return (1);
}

int		map_check_h(t_cub3d *c)
{
	int		i;
	int		j;
	int		x;
	int		y;

	x = 0;
	i = 0;
	while (i < c->map_y)
	{
		y = 0;
		j = 0;
		while (j < c->map_x && c->map[i][j] != '\0')
		{
			if (check_map_enclosed(c->map[i][j], &x, &y) == -1)
				return (-1);
			j++;
		}
		if (x == 0)
			return (-1);
		i++;
	}
	return (1);
}

int		map_check_y(t_cub3d *c)
{
	int		i;
	int		j;
	int		x;
	int		y;

	x = 0;
	i = 0;
	while (i < c->map_x)
	{
		y = 0;
		j = 0;
		while (j < c->map_y && c->map[j][i] != '\0')
		{
			if (check_map_enclosed(c->map[j][i], &x, &y) == -1)
				return (-1);
			j++;
		}
		if (x == 0)
			return (-1);
		i++;
	}
	return (1);
}

int		check_map_enclosed(char c, int *x, int *y)
{
	if (c == '1')
	{
		*x = 1;
		(*y)++;
	}
	else if (c == '0')
	{
		if (*y < 1)
			return (-1);
		*x = 0;
	}
	else if (c == ' ' && *x == 0 && *y > 0)
		return (-1);
	return (0);
}
