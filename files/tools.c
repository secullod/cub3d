/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:35:03 by secullod          #+#    #+#             */
/*   Updated: 2020/12/11 09:35:05 by secullod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		name_check(char *arg, char *ext)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
		i++;
	if ((i > 4 && arg[i - 1] == ext[2] && arg[i - 2] == ext[1])
		&& (arg[i - 3] == ext[0] && arg[i - 4] == '.'))
		return (1);
	return (0);
}

int		save_check(char *arg, char *save)
{
	int	i;

	i = 0;
	while (arg[i] == save[i])
	{
		if (arg[i] == '\0' && save[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int		parse_check(t_cub3d *c)
{
	if (c->res_x <= 0 || c->res_y <= 0)
		return (error("Error : No resolution specified"));
	else if ((c->north == NULL || c->south == NULL || c->east == NULL)
			|| (c->west == NULL || c->spr == NULL))
		return (error("Error : Missing texture"));
	else if (c->ceiling == NONE || c->floor == NONE)
		return (error("Error : Missing floor/ceiling color"));
	else if (c->start_pos == 0)
		return (error("Error : No starting position"));
	else if (c->start_pos > 1)
		return (error("Error : Multiple starting positions"));
	else if (map_check(c) == -1)
		return (-1);
	return (1);
}

int		ft_atoi(char *line, int *i)
{
	int	num;

	num = 0;
	space_skip(line, i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + (line[*i] - 48);
		(*i)++;
	}
	return (num);
}

void	ft_putstr_fd(char *s, int fd)
{
	size_t		len;

	len = 0;
	while (s[len])
		len++;
	write(fd, s, len);
}
