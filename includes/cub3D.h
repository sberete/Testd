#ifndef CUB3D_H
# define CUB3D_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include "libft.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

/* ************************************************************************** */
/*                                   DEFINES                                  */
/* ************************************************************************** */

# define WIDTH 1280
# define HEIGHT 720

# define MINIMAP_SCALE 0.2
# define MINIMAP_OFFSET_X 10
# define MINIMAP_OFFSET_Y 10

# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define GRAY 0x00808080

# define COLOR_WALL GRAY
# define COLOR_FLOOR WHITE
# define MAX_DOORS 64

/* ************************************************************************** */
/*                                  STRUCTS                                   */
/* ************************************************************************** */

typedef struct s_point
{
	int			x;
	int			y;
}				t_point;

typedef struct s_img
{
	void		*img_ptr;
	char		*pixels_ptr;
	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_path
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
}				t_path;

typedef struct s_texture
{
	t_img		north;
	t_img		south;
	t_img		west;
	t_img		east;
}				t_texture;

typedef struct s_color
{
	char		*floor;
	char		*ceiling;
	int			floor_rgb;
	int			ceiling_rgb;
}				t_color;

typedef struct s_door
{
	int			x;
	int			y;
	double		openness;
	int			opening;
}				t_door;

typedef struct s_direction
{
	double		x;
	double		y;
}				t_direction;

typedef struct s_position
{
	double		x;
	double		y;
}				t_position;

typedef struct s_plane
{
	double		x;
	double		y;
}				t_plane;

typedef struct s_move
{
	int			forward;
	int			backward;
	int			left;
	int			right;
	int			rotate_left;
	int			rotate_right;
}				t_move;

typedef struct s_map
{
	char		*name;
	char		**grid;
	int			width;
	int			height;
	t_path		path;
	t_texture	texture;
	t_color		color;
	t_door		*doors;
	int			door_count;

	// pour le parsing et flood-fill
	int			player_x;
	int			player_y;
	char		player_dir;
}				t_map;

typedef struct s_player
{
	t_move		move;
	t_direction	dir;
	t_plane		plane;
	t_position	pos;
}				t_player;

typedef struct s_ray
{
	double		ray_dir_x;
	double		ray_dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	int			side;
}				t_ray;

typedef struct s_mlx
{
	void		*ptr;
	void		*win;
}				t_mlx;

typedef struct s_texinfo
{
	t_img		*tex;
	int			tex_x;
}				t_texinfo;

typedef struct s_col
{
	int			start;
	int			end;
	int			line_h;
	int			x;
}				t_col;

typedef struct s_data
{
	t_mlx		mlx;
	t_map		map;
	t_img		img;
	t_player	player;
	t_ray		ray;
}				t_data;

/* ************************************************************************** */
/*                                PARSING                                      */
/* ************************************************************************** */

int				parsing(t_data *cub3d, int argc, char **argv);

/* map read */
char			**read_map(int fd);
char			**append_line(char **map, char *line);

/* map utils */
int				is_map_line(char *line);
int				is_line_empty(char *line);
int				get_max_width(char **map);
int				get_height(char **map);
char			**normalize_map(char **map);
char			**copy_map(t_map *grid);
int				flood_fill(char **map, int x, int y, t_map *grid);
int				check_map_closed(t_map *grid);
int				check_map_char(t_map *map);
int				check_map_player(t_map *map);
int				check_map_empty_lines(t_map *map);

/* config parsing */
void			parsing_textures(int fd, t_path *path);
void			parsing_colors(int fd, t_color *color);

/* utils */
int				convert_rgb_string(char *str);
void			free_map(char **map);

/* gameplay init */
void			add_door(t_data *cub3d, int x, int y);
void			set_player_dir(t_player *p, char c);
void			init_player_plane(t_player *player);
void			init_player_from_map(t_data *cub3d, int x, int y, char c);
void			parse_map_grid(t_data *cub3d);

/* textures */
int				load_all_textures(t_data *cub3d);

/* render / mlx */
void			mlx_hookes(t_data *cub3d);
int				key_press(int keycode, t_data *cub3d);
int				key_release(int keycode, t_data *cub3d);
int				mouse_move(int x, int y, t_data *cub3d);

/* game helpers */
int				free_all_and_exit(t_data *cub3d);
void			put_pixel(t_img *img, int x, int y, int color);
void			mlx_failure(t_data *cub3D, char *str);
void			param_available(void);
void			cub3d_init(t_data *cub3d);
void			update_doors(t_map *map);
void			interact(t_data *cub3d);
t_door			*find_door(t_map *map, int x, int y);
void			update_player_position(t_data *cub3d);
void			move_player(t_data *cub3d, double dir_x, double dir_y,
					double speed);
void			rotate_player(t_data *cub3d, double angle);
void			draw_scene(t_data *cub3d);
void			draw_scene_3d(t_data *cub3d);
void			perform_dda(t_data *cub3d, t_ray *ray);
void			init_ray(t_data *cub3d, int x, t_ray *ray);
void			init_step(t_data *cub3d, t_ray *ray);
double			compute_perp_dist(t_data *cub3d, t_ray *ray);
double			compute_wall_x(t_data *cub3d, t_ray *ray, double perp_dist);
t_img			*get_texture(t_data *cub3d, t_ray *ray);
void			draw_tex_stripe(t_data *cub3d, t_texinfo t, t_col c);
void			compute_draw_limits(double dist, int *line_h, int *start,
					int *end);
void			draw_minimap(t_data *cub3d);
int				is_wall(t_data *cub3d, double x, double y);

#endif
