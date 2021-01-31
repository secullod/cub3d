/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:12:11 by secullod          #+#    #+#             */
/*   Updated: 2020/12/11 09:19:22 by secullod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_cub_file(t_cub3d *c)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	if ((fd = open(c->filename, O_RDONLY)) == -1)
		return (error("Error : Couldn't open file (FD)"));
	while (ret == 1)
	{
		if ((ret = get_next_line(fd, &line)) == -1)
			return (p_error("Error : Couldn't parse file (GNL)", &line, fd));
		if (parse_line(c, line) == -1)
		{
			free(line);
			close(fd);
			return (-1);
		}
		free(line);
	}
	if (c->map_y <= 2 || c->map_x <= 2)
		return (error("Error: Only 2 or less Map row or columns"));
	player_position(c);
	return ((parse_check(c) == -1 || sprite_positions(c) == -1) ? -1 : 0);
}

int		parse_line(t_cub3d *c, char *line)
{
	int		i;

	i = 0;
	element_skip(line, &i);
	line_skip(line, &i);
	if ((line[i] == ' ' || line[i] == '1' || c->map_err == 1)
	&& line[i] != '\0')
		return (map(c, line, &i));
	else if (line[i] == 'N' && line[i + 1] == 'O' && is_nul(i, line, &c->n_ptr))
		return ((c->n_ptr = texture(c, &c->north, line, &i)) == NULL ? -1 : 0);
	else if (line[i] == 'S' && line[i + 1] == 'O' && is_nul(i, line, &c->s_ptr))
		return ((c->s_ptr = texture(c, &c->south, line, &i)) == NULL ? -1 : 0);
	else if (line[i] == 'W' && line[i + 1] == 'E' && is_nul(i, line, &c->w_ptr))
		return ((c->w_ptr = texture(c, &c->west, line, &i)) == NULL ? -1 : 0);
	else if (line[i] == 'E' && line[i + 1] == 'A' && is_nul(i, line, &c->e_ptr))
		return ((c->e_ptr = texture(c, &c->east, line, &i)) == NULL ? -1 : 0);
	else if (line[i] == 'S' && line[i + 1] == ' ' && c->spr_ptr == NULL)
		return ((c->spr_ptr = texture(c, &c->spr, line, &i)) == NULL ? -1 : 0);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		return (colors(&c->floor, line, &i));
	else if (line[i] == 'C' && line[i + 1] == ' ')
		return (colors(&c->ceiling, line, &i));
	else if (line[i] == 'R' && line[i + 1] == ' ')
		return (resolution(c, line, &i));
	return (line[i] != '\0' ? error("Error : invalid line") : 0);
}

char	*file_name(char *line, int *i)
{
	char	*filename;
	int		j;

	(*i) += 2;
	space_skip(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(filename = malloc(sizeof(char) * (*i - j + 1))))
		return (cerror("Error : Malloc fail (texture path)"));
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		filename[j++] = line[(*i)++];
	filename[j] = '\0';
	if (name_check(filename, "xpm") == 0)
	{
		free(filename);
		return (cerror("Error : texture extension name"));
	}
	return (filename);
}

int		line_length(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == '2' ||
		line[i] == ' ' || line[i] == 'N' || line[i] == 'S' || line[i] == 'W' ||
		line[i] == 'E')
			i++;
		else
			return (-1);
	}
	return (i);
}

char	*insert_row(t_cub3d *c, char *line, int *i)
{
	char	*row;
	int		x;

	x = 0;
	if ((x = line_length(line)) == -1)
		return (cerror("Error : Invalid map char"));
	if (!(row = malloc(sizeof(char) * (x + 1))))
		return (cerror("Error : Malloc fail (insert row)"));
	x = 0;
	while (line[*i] != '\0')
	{
		if (line[*i] == '2')
			c->numspr++;
		if (line[*i] == '0' || line[*i] == '1' || line[*i] == 'N' ||
		line[*i] == 'E' || line[*i] == 'S' || line[*i] == 'W' ||
		line[*i] == '2' || line[*i] == ' ')
			row[x++] = line[*i];
		(*i)++;
	}
	row[x] = '\0';
	return (row);
}
