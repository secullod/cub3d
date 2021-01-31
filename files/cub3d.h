/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 09:35:22 by secullod          #+#    #+#             */
/*   Updated: 2020/12/14 18:47:14 by sean             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*
** Linux Include
** # include "../minilibx-linux/mlx.h"
** # include <X11/X.h>
*/

# include "../mlxopengl/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <stdint.h>

# define PI M_PI
# define HALF_PI M_PI_2

# define TILE 64
# define TILE_SIZE 60
# define TILE_SPACING 4
# define SCALE 2
# define RADIUS 15
# define FALSE 0
# define TRUE 1

# define NONE 0xFF000000
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define MAGENTA 0x00FF00FF
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF
# define MCOLOR BLUE
# define WCOLOR RED
# define PCOLOR YELLOW
# define SCOLOR RED
# define BCOLOR BLACK
# define RCOLOR GREEN
# define BLANKPIX BLACK

# define ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

/*
** Linux key code
** # define KEY_W 119
** # define KEY_A 97
** # define KEY_S 115
** # define KEY_D 100
** # define KEY_LEFT 65361
** # define KEY_RIGHT 65363
** # define ESC 65307
*/

# define SPEED 15
# define TURN 0.05

# define BUFFER_SIZE 4096

typedef struct		s_ray
{
	float			angle;
	float			wall_hit_x;
	float			wall_hit_y;
	float			dist;
	int				hit_v;
	int				face_down;
	int				face_right;
	int				wall_hit_content;
}					t_ray;

typedef struct		s_spr
{
	int				x;
	int				y;
	double			d;
	double			angle;
	double			dx;
	double			dy;
	double			pd;
	double			h;
	double			center_x;
	double			color;
	double			delta;
	int				ytop;
}					t_spr;

typedef struct		s_cub3d
{
	t_spr			*sprite;
	t_ray			*rays;
	int				x;
	int				y;
	int				res_x;
	int				res_y;
	int				map_x;
	int				map_y;
	void			*mlx_ptr;
	void			*win_ptr;
	unsigned int	*addr;
	void			*img_ptr;
	void			*w_ptr;
	void			*s_ptr;
	void			*n_ptr;
	void			*e_ptr;
	void			*spr_ptr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				t_width;
	int				t_height;
	int				t_bits_per_pixel;
	int				t_size_line;
	int				t_endian;
	double			p_angle;
	double			turn_dir;
	double			turn_speed;
	double			wall_hit_x;
	double			wall_hit_y;
	int				walk_dir;
	int				strafe;
	int				numspr;
	char			**map;
	unsigned int	*south;
	unsigned int	*north;
	unsigned int	*east;
	unsigned int	*west;
	unsigned int	*spr;
	unsigned int	ceiling;
	unsigned int	floor;
	int				face_right;
	int				face_down;
	int				error;
	int				start_pos;
	float			dist_p;
	float			d_plane;
	float			strip_h;
	int				pixel_top;
	int				pixel_bot;
	int				text_offset_x;
	int				text_offset_y;
	int				dist_top;
	float			y_step;
	float			x_step;
	float			hit_y;
	float			hit_x;
	float			hit_dist_x;
	float			hit_dist_y;
	float			check_x;
	float			check_y;
	char			*filename;
	int				bmp;
	int				map_err;
	int				wall_cont_v;
	int				wall_cont_h;
	double			touch_vy;
	double			touch_hy;
	double			touch_hx;
	double			touch_vx;
	float			tile;
	int				winx;
	int				winy;
	float			angle_inc;
	int				steps;
	int				color;
	int				x_offset;
	int				y_offset;
	double			fov;
	int				scale;
	float			xscale;
	float			yscale;
}					t_cub3d;

/*
** cub3d
*/

void				draw(t_cub3d *c);
void				init_helper(t_cub3d *c);
void				init_helper_2(t_cub3d *c);
int					init(char *cub, int bmp);

/*
** draw2d
*/

void				draw_tile_2d(t_cub3d *c, int x, int y, int size);
void				draw_map_2d(t_cub3d *c);
void				draw_player_2d(t_cub3d *c, int pos_x, int pos_y,
					int color);
void				draw_ray_2d(t_cub3d *c, int ray_num);
void				draw_view_2d(t_cub3d *c);

/*
** move.c
*/

int					key_press(int keycode, t_cub3d *c);
void				move_player(t_cub3d *c);
int					p_error(char *message, char **file, int fd);
void				scale_minimap(t_cub3d *c);
int					ft_close(t_cub3d *c);

/*
** draw3d
*/

void				draw_pixel(t_cub3d *c, unsigned int color, int y, int x);
void				draw_view_3d(t_cub3d *c);
unsigned int		*get_texture(t_cub3d *c, int x);
void				*t_error(char *message, char **file);
void				draw_view_3d_helper(t_cub3d *c, int x, int y,
					unsigned int *texture);

/*
** map
*/

int					map(t_cub3d *c, char *line, int *i);
int					map_check(t_cub3d *c);
int					map_check_y(t_cub3d *c);
int					map_check_h(t_cub3d *c);
int					check_map_enclosed(char ch, int *x, int *y);

/*
** parse
*/

int					parse_cub_file(t_cub3d *c);
int					parse_line(t_cub3d *c, char *line);
char				*file_name(char *line, int *i);
char				*insert_row(t_cub3d *c, char *line, int *i);
int					line_length(char *line);

/*
** elements
*/

void				*texture(t_cub3d *c, unsigned int **texture, char *line,
					int *i);
int					colors(unsigned int *color, char *line, int *i);
int					resolution(t_cub3d *c, char *line, int *i);
void				player_position(t_cub3d *c);

/*
** raycast
*/

double				reset_angle(double angle);
void				face_direction_by_ray(t_cub3d *c, double ray_angle,
					int ray_num);
void				face_direction(t_cub3d *c, double ray_angle);
int					detect_wall(t_cub3d *c, double x, double y);
int					to_map_index(double postion);

/*
** raycast_helper
*/

int					cast_rays(t_cub3d *c);
void				cast_ray(t_cub3d *c, int ray_num, double ray_angle);
void				wall_intersection_h(t_cub3d *c, double ray_angle);
void				wall_intersection_v(t_cub3d *c, double ray_angle);
void				set_ray_values(t_cub3d *c, int ray_num, double ray_angle);

/*
** tools
*/

int					name_check(char *arg, char *ext);
int					parse_check(t_cub3d *c);
int					save_check(char *arg, char *save);
int					ft_atoi(char *line, int *i);
void				ft_putstr_fd(char *s, int fd);

/*
** more_tools
*/

int					space_skip(char *line, int *i);
int					element_skip(char *line, int *i);
int					line_skip(char *line, int *i);
char				*cerror(char *msg);
int					error(char *msg);

/*
** get_next_line_utils
*/

char				*ft_strdup(const char *s);
char				*ft_strchr(char *s, int c);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *str);
char				*ft_substr(char const *s, unsigned int start, size_t len);

/*
** get_next_line
*/

int					append(char **str, char **line, int fd);
int					get_next_line(int fd, char **line);

/*
** sprites
*/

int					sprite_positions(t_cub3d *c);
void				ft_sprite(t_cub3d *c);
void				order_sprites(t_cub3d *c);
void				draw_sprite(t_cub3d *c);
void				draw_sprite_helper(t_cub3d *c, int y, int x, int i);

/*
** bitmap
*/

void				ft_bitmap(t_cub3d *c);
void				ft_bfile(t_cub3d *c, int fd);
void				ft_binfo(t_cub3d *c, int fd);
void				ft_bdata(t_cub3d *c, int fd);
int					is_nul(int i, char *line, void **img_ptr);

#endif
