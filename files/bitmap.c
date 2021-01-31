/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:34:25 by secullod          #+#    #+#             */
/*   Updated: 2020/12/14 18:46:52 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	write_image_data(t_cub3d *c, int fd)
{
	int				i;
	int				j;
	unsigned char	rgb[4];

	i = c->res_x * (c->res_y - 1);
	while (i >= 0)
	{
		j = 0;
		while (j < c->res_x)
		{
			rgb[0] = (unsigned char)(c->addr[i] % 256);
			rgb[1] = (unsigned char)(c->addr[i] / 256 % 256);
			rgb[2] = (unsigned char)(c->addr[i] / 256 / 256 % 256);
			rgb[3] = (unsigned char)(0);
			write(fd, rgb, 4);
			i++;
			j++;
		}
		i -= 2 * c->res_x;
	}
}

void	write_info_header(t_cub3d *c, int fd)
{
	int				n;
	unsigned char	info_header[40];

	n = 0;
	while (n < 40)
		info_header[n++] = (unsigned char)(0);
	info_header[0] = (unsigned char)(40);
	n = c->res_x;
	info_header[4] = (unsigned char)(n % 256);
	info_header[5] = (unsigned char)(n / 256 % 256);
	info_header[6] = (unsigned char)(n / 256 / 256 % 256);
	info_header[7] = (unsigned char)(n / 256 / 256 / 256);
	n = c->res_y;
	info_header[8] = (unsigned char)(n % 256);
	info_header[9] = (unsigned char)(n / 256 % 256);
	info_header[10] = (unsigned char)(n / 256 / 256 % 256);
	info_header[11] = (unsigned char)(n / 256 / 256 / 256);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(32);
	write(fd, info_header, 40);
}

void	write_file_header(t_cub3d *c, int fd)
{
	int				n;
	unsigned char	file_header[14];

	n = 0;
	while (n < 14)
		file_header[n++] = (unsigned char)(0);
	file_header[0] = (unsigned char)(66);
	file_header[1] = (unsigned char)(77);
	n = c->res_x * c->res_y * 4 + 54;
	file_header[2] = (unsigned char)(n % 256);
	file_header[3] = (unsigned char)(n / 256 % 256);
	file_header[4] = (unsigned char)(n / 256 / 256 % 256);
	file_header[5] = (unsigned char)(n / 256 / 256 / 256);
	file_header[10] = (unsigned char)(54);
	write(fd, file_header, 14);
}

void	ft_bitmap(t_cub3d *c)
{
	int		fd;

	fd = open("bitmap.bmp", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	write_file_header(c, fd);
	write_info_header(c, fd);
	write_image_data(c, fd);
	close(fd);
	ft_close(c);
}

int		is_nul(int i, char *line, void **img_ptr)
{
	if (line[i + 2] == ' ' && *img_ptr == NULL)
		return (1);
	else
		return (0);
}
