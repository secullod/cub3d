/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elements.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:23:23 by secullod          #+#    #+#             */
/*   Updated: 2020/12/11 18:11:43 by secullod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		*texture(t_cub3d *c, unsigned int **texture, char *line, int *i)
{
	int		fd;
	char	*file;
	void	*img_ptr;

	if ((file = file_name(line, i)) == NULL)
		return (NULL);
	if (*texture != NULL)
		return (t_error("Error : Texture path specified twice", &file));
	if ((fd = open(file, O_RDONLY)) == -1)
		return (t_error("Error : Couldn't open texture file", &file));
	close(fd);
	img_ptr = mlx_xpm_file_to_image(c->mlx_ptr, file,
	&c->t_width, &c->t_height);
	if (img_ptr == NULL || c->t_width != 64 || c->t_height != 64)
	{
		free(img_ptr);
		return (t_error("Error : xpm file (NULL or != 64)", &file));
	}
	*texture = (unsigned int *)mlx_get_data_addr(img_ptr, &c->t_bits_per_pixel,
	&c->t_size_line, &c->t_endian);
	free(file);
	return (img_ptr);
}

int			colors(unsigned int *color, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*color != NONE)
		return (error("Error : Floor/ceiling specified twice"));
	if (line[*i] == '\0')
		return (error("Error : Invalid floor/ceiling line"));
	(*i)++;
	r = ft_atoi(line, i);
	if (line[*i] == '\0')
		return (error("Error : Invalid floor/ceiling line"));
	(*i)++;
	g = ft_atoi(line, i);
	if (line[*i] == '\0')
		return (error("Error : Invalid floor/ceiling line"));
	(*i)++;
	b = ft_atoi(line, i);
	space_skip(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (error("Error : Invalid floor/ceiling line"));
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}

int			resolution(t_cub3d *c, char *line, int *i)
{
	if (c->res_x != 0 || c->res_y != 0)
		return (error("Error : Resolution specified twice"));
	(*i)++;
	c->res_x = ft_atoi(line, i);
	c->res_y = ft_atoi(line, i);
	if (c->res_x < 50)
		c->res_x = 50;
	if (c->res_y < 50)
		c->res_y = 50;
	if (c->res_x > 2560)
		c->res_x = 2560;
	if (c->res_y > 1400)
		c->res_y = 1400;
	space_skip(line, i);
	if (c->res_x <= 0 || c->res_y <= 0 || line[*i] != '\0')
		return (error("Error : Invalid resolution"));
	return (0);
}

void		player_position(t_cub3d *c)
{
	int		i;
	int		j;

	c->start_pos = 0;
	i = -1;
	while (++i < c->map_y)
	{
		j = -1;
		while (++j < c->map_x && c->map[i][j] != '\0')
			if ((c->map[i][j] == 'N' || c->map[i][j] == 'E' || c->map[i][j]
			== 'S' || c->map[i][j] == 'W') && c->map[i + 1][j] != ' ' &&
			c->map[i - 1][j] != ' ' && c->map[i][j + 1] != ' ' &&
			c->map[i][j - 1] != ' ')
			{
				c->y = ((double)i + .5) * TILE;
				c->x = ((double)j + .5) * TILE;
				if (c->map[i][j] == 'W')
					c->p_angle = PI;
				if (c->map[i][j] == 'S')
					c->p_angle = HALF_PI;
				if (c->map[i][j] == 'N')
					c->p_angle = PI * 1.5;
				c->start_pos++;
			}
	}
}
