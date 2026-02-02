#include "cub3D.h"

/* ************************************************************************** */
/*                                  MAP UTILS                                  */
/* ************************************************************************** */

/**
 * Vérifie si une ligne lue est une ligne de map
 */
int is_map_line(char *line)
{
    int i = 0;

    if (!line)
        return (0);
    while (line[i] == ' ' || line[i] == '\t')
        i++;
    return (line[i] == '1' || line[i] == '0');
}

/**
 * Vérifie si la map contient uniquement des caractères valides
 */
int parsing_map(t_map *map)
{
    int y;
    int player_count = 0;
    int rows;
size_t x, len;

    if (!map->grid)
        return (0);

    rows = 0;
    while (map->grid[rows])
        rows++;

    for (y = 0; y < rows; y++)
    {
       len = ft_strlen(map->grid[y]);
		for (x = 0; x < len; x++)
		{
			char c = map->grid[y][x];
			if (!ft_strchr("01NSEWD ", c))
				return 0;
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
			if (x == 0 || x == len - 1)
				if (c != '1')
					return 0;
		}

        // vérifier la première et dernière ligne
        if (y == 0 || y == rows - 1)
        {
            for (x = 0; x < ft_strlen(map->grid[y]); x++)
                if (map->grid[y][x] != '1')
                    return (0);
        }
    }

    if (player_count != 1)
        return (0);

    return (1);
}


/* ************************************************************************** */
/*                               CONFIG PARSING                                */
/* ************************************************************************** */

/**
 * Lit les textures depuis le fichier
 */
void parsing_textures(int fd, t_path *path)
{
    char *line;

    ft_bzero(path, sizeof(t_path));
    while ((line = get_next_line(fd)))
    {
        if (is_map_line(line))
            return (free(line));
        if (!ft_strncmp(line, "NO ", 3))
            path->north = ft_strtrim(line + 3, " \n");
        else if (!ft_strncmp(line, "SO ", 3))
            path->south = ft_strtrim(line + 3, " \n");
        else if (!ft_strncmp(line, "WE ", 3))
            path->west = ft_strtrim(line + 3, " \n");
        else if (!ft_strncmp(line, "EA ", 3))
            path->east = ft_strtrim(line + 3, " \n");
        free(line);
        if (path->north && path->south && path->west && path->east)
            return ;
    }
}

/**
 * Lit les couleurs du sol et du plafond
 */
void parsing_colors(int fd, t_color *color)
{
    char *line;

    ft_bzero(color, sizeof(t_color));
    while ((line = get_next_line(fd)))
    {
        if (is_map_line(line))
            return (free(line));
        if (!ft_strncmp(line, "F ", 2))
            color->floor = ft_strtrim(line + 2, " \n");
        else if (!ft_strncmp(line, "C ", 2))
            color->ceiling = ft_strtrim(line + 2, " \n");
        free(line);
        if (color->floor && color->ceiling)
            return ;
    }
}

/* ************************************************************************** */
/*                               MAP READING                                   */
/* ************************************************************************** */

/**
 * Ajoute une ligne à la map
 */
char **append_line(char **map, char *line)
{
    int i = 0;
    char **new;

    while (map && map[i])
        i++;
    new = malloc(sizeof(char *) * (i + 2));
    if (!new)
        return (free(line), NULL);
    for (int j = 0; j < i; j++)
        new[j] = map[j];
    new[i] = ft_strdup(line);
    new[i + 1] = NULL;
    free(map);
    free(line);
    return (new);
}

/**
 * Lit la map complète depuis le fichier
 */
char **read_map(int fd)
{
    char *line;
    char **map = NULL;

    while ((line = get_next_line(fd)))
    {
        if (is_map_line(line))
            break;
        free(line);
    }
    if (!line)
        return (NULL);
    map = append_line(map, line);
    while ((line = get_next_line(fd)))
        map = append_line(map, line);
    return (map);
}

/* ************************************************************************** */
/*                               GAMEPLAY INIT                                  */
/* ************************************************************************** */

/**
 * Ajoute une porte dans la map
 */
void add_door(t_data *cub3d, int x, int y)
{
    t_door *door;

    door = &cub3d->map.doors[cub3d->map.door_count++];
    door->x = x;
    door->y = y;
    door->openness = 0.0;
    door->opening = 0;
    cub3d->map.grid[y][x] = '2';
}

/**
 * Définit la direction du joueur
 */
void set_player_dir(t_player *p, char c)
{
    if (c == 'N')      (p->dir.x = 0, p->dir.y = -1);
    else if (c == 'S') (p->dir.x = 0, p->dir.y = 1);
    else if (c == 'E') (p->dir.x = 1, p->dir.y = 0);
    else if (c == 'W') (p->dir.x = -1, p->dir.y = 0);
}

/**
 * Initialise le plan du joueur pour le raycasting
 */
void init_player_plane(t_player *player)
{
    double fov = 0.66;

    if (player->dir.x == 0 && player->dir.y == -1)
        (player->plane.x = fov, player->plane.y = 0);
    else if (player->dir.x == 0 && player->dir.y == 1)
        (player->plane.x = -fov, player->plane.y = 0);
    else if (player->dir.x == 1 && player->dir.y == 0)
        (player->plane.x = 0, player->plane.y = fov);
    else if (player->dir.x == -1 && player->dir.y == 0)
        (player->plane.x = 0, player->plane.y = -fov);
}

/**
 * Initialise la position et la direction du joueur depuis la map
 */
void init_player_from_map(t_data *cub3d, int x, int y, char c)
{
    cub3d->player.pos.x = x + 0.5;
    cub3d->player.pos.y = y + 0.5;
    set_player_dir(&cub3d->player, c);
    init_player_plane(&cub3d->player);
    cub3d->map.grid[y][x] = '0';
}

/* ************************************************************************** */
/*                               MAP GRID PARSING                               */
/* ************************************************************************** */

static void parse_cell(t_data *cub3d, int x, int y, char c)
{
    if (c == 'D')
        add_door(cub3d, x, y);
    else if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        init_player_from_map(cub3d, x, y, c);
}

static void parse_map_grid(t_data *cub3d)
{
    for (int y = 0; cub3d->map.grid[y]; y++)
        for (int x = 0; cub3d->map.grid[y][x]; x++)
            parse_cell(cub3d, x, y, cub3d->map.grid[y][x]);
}

/* ************************************************************************** */
/*                               UTILITIES                                      */
/* ************************************************************************** */

/**
 * Convertit une chaîne "R,G,B" en entier RGB
 */
int convert_rgb_string(char *str)
{
    int r, g, b;

    if (!str)
        return (0);
    r = ft_atoi(str);
    str = ft_strchr(str, ',');
    if (!str)
        return (0);
    g = ft_atoi(++str);
    str = ft_strchr(str, ',');
    if (!str)
        return (0);
    b = ft_atoi(++str);
    return ((r << 16) | (g << 8) | b);
}

/* ************************************************************************** */
/*                               TEXTURE LOADING                                 */
/* ************************************************************************** */

/**
 * Charge toutes les textures (stub)
 */
static int	load_texture(void *mlx_ptr, char *path, t_img *tex)
{
	tex->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &tex->width,
			&tex->height);
	if (!tex->img_ptr)
		return (1);
	tex->pixels_ptr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->pixels_ptr)
		return (1);
	return (0);
}

int	load_all_textures(t_data *cub3d)
{
	if (load_texture(cub3d->mlx.ptr, cub3d->map.path.north,
			&cub3d->map.texture.north))
		return (1);
	if (load_texture(cub3d->mlx.ptr, cub3d->map.path.south,
			&cub3d->map.texture.south))
		return (1);
	if (load_texture(cub3d->mlx.ptr, cub3d->map.path.west,
			&cub3d->map.texture.west))
		return (1);
	if (load_texture(cub3d->mlx.ptr, cub3d->map.path.east,
			&cub3d->map.texture.east))
		return (1);
	return (0);
}


/* ************************************************************************** */
/*                               ENTRY POINT                                     */
/* ************************************************************************** */

/**
 * Parsing principal du projet
 */
int parsing(t_data *cub3d, int argc, char **argv)
{
    int fd;

    if (argc != 2)
        return (ft_putendl_fd("Usage: ./cub3D map.cub", 2), 1);

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (ft_putendl_fd("Cannot open file", 2), 1);

    parsing_textures(fd, &cub3d->map.path);
    parsing_colors(fd, &cub3d->map.color);

    cub3d->map.grid = read_map(fd);
    close(fd);
    if (!cub3d->map.grid || !parsing_map(&cub3d->map))
        return (ft_putendl_fd("Invalid map", 2), 1);

    cub3d->map.doors = malloc(sizeof(t_door) * MAX_DOORS);
    cub3d->map.door_count = 0;
    parse_map_grid(cub3d);

    cub3d->map.color.floor_rgb =
        convert_rgb_string(cub3d->map.color.floor);
    cub3d->map.color.ceiling_rgb =
        convert_rgb_string(cub3d->map.color.ceiling);

    if (load_all_textures(cub3d))
        return (ft_putendl_fd("Texture loading failed", 2), 1);

    return (0);
}
