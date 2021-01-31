/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:36:08 by secullod          #+#    #+#             */
/*   Updated: 2020/12/11 09:36:10 by secullod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		space_skip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
	|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

int		element_skip(char *line, int *i)
{
	int x;

	x = (*i);
	while ((line[x] == ' ' || line[x] == '\t')
	|| (line[x] == '\r' || line[x] == '\v' || line[x] == '\f'))
		x++;
	if (line[x] == 'N' || line[x] == 'W' || line[x] == 'E' || line[x] == 'S'
	|| line[x] == 'F' || line[x] == 'C' || line[x] == 'R')
		*i = x;
	return (1);
}

int		line_skip(char *line, int *i)
{
	while ((line[*i] == '\t' || line[*i] == '\n')
	|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

int		error(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (-1);
}

char	*cerror(char *msg)
{
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}
