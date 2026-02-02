// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   parse_color.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: sxriimu <sxriimu@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/11/26 09:49:48 by sberete           #+#    #+#             */
// /*   Updated: 2026/02/02 17:49:29 by sxriimu          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "cub3D.h"

// #include "cub3D.h"

// /* ************************************************************************** */
// /*                                  MAP UTILS                                  */
// /* ************************************************************************** */

// int is_map_line(char *line)
// {
//     int i = 0;
//     if (!line)
//         return 0;
//     while (line[i] == ' ' || line[i] == '\t')
//         i++;
//     return (line[i] == '1' || line[i] == '0');
// }

// int is_line_empty(char *line)
// {
//     int i = 0;
//     while (line[i])
//     {
//         if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
//             return 0;
//         i++;
//     }
//     return 1;
// }

// /* Normalise la map : toutes les lignes ont la même largeur */
// int get_max_width(char **map)
// {
//     int y = 0, len = 0, max = 0;
//     while (map[y])
//     {
//         len = 0;
//         while (map[y][len] && map[y][len] != '\n')
//             len++;
//         if (len > max)
//             max = len;
//         y++;
//     }
//     return max;
// }

// int get_height(char **map)
// {
//     int y = 0;
//     while (map[y])
//         y++;
//     return y;
// }

// char **normalize_map(char **map)
// {
//     int width = get_max_width(map);
//     int height = get_height(map);
//     char **new = malloc(sizeof(char *) * (height + 1));
//     if (!new) return NULL;

//     for (int y = 0; y < height; y++)
//     {
//         new[y] = malloc(sizeof(char) * (width + 1));
//         if (!new[y])
//         {
//             for (int i = 0; i < y; i++) free(new[i]);
//             free(new);
//             return NULL;
//         }
//         for (int x = 0; x < width; x++)
//             new[y][x] = map[y][x] && map[y][x] != '\n' ? map[y][x] : ' ';
//         new[y][width] = '\0';
//     }
//     new[height] = NULL;
//     return new;
// }

// char **copy_map(t_map *grid)
// {
//     char **copy = malloc(sizeof(char *) * (grid->height + 1));
//     if (!copy) return NULL;
//     for (int i = 0; i < grid->height; i++)
//     {
//         copy[i] = ft_strdup(grid->grid[i]);
//         if (!copy[i])
//         {
//             for (int j = 0; j < i; j++) free(copy[j]);
//             free(copy);
//             return NULL;
//         }
//     }
//     copy[grid->height] = NULL;
//     return copy;
// }

// /* Flood fill pour vérifier que la map est fermée */
// int flood_fill(char **map, int x, int y, t_map *grid)
// {
//     if (x < 0 || y < 0 || x >= grid->width || y >= grid->height) return 1;
//     if (map[y][x] == ' ') return 1;
//     if (map[y][x] == '1' || map[y][x] == 'V') return 0;

//     map[y][x] = 'V';

//     if (flood_fill(map, x + 1, y, grid)) return 1;
//     if (flood_fill(map, x - 1, y, grid)) return 1;
//     if (flood_fill(map, x, y + 1, grid)) return 1;
//     if (flood_fill(map, x, y - 1, grid)) return 1;

//     return 0;
// }

// int check_map_closed(t_map *grid)
// {
//     char **copy = copy_map(grid);
//     if (!copy) return 1;

//     int result = flood_fill(copy, grid->player_x, grid->player_y, grid);
//     for (int i = 0; i < grid->height; i++) free(copy[i]);
//     free(copy);
//     return result;
// }

// int check_map_char(t_map *map)
// {
//     for (int y = 0; y < map->height; y++)
//         for (int x = 0; x < map->width; x++)
//             if (!ft_strchr("01NSEWD ", map->grid[y][x]))
//                 return 1;
//     return 0;
// }

// int check_map_player(t_map *map)
// {
//     int count = 0;
//     for (int y = 0; y < map->height; y++)
//     {
//         for (int x = 0; x < map->width; x++)
//         {
//             if (ft_strchr("NSEW", map->grid[y][x]))
//             {
//                 map->player_x = x;
//                 map->player_y = y;
//                 map->player_dir = map->grid[y][x];
//                 count++;
//             }
//         }
//     }
//     return (count != 1);
// }

// int check_map_empty_lines(t_map *map)
// {
//     int map_started = 0;
//     for (int y = 0; y < map->height; y++)
//     {
//         if (is_map_line(map->grid[y])) map_started = 1;
//         else if (map_started && is_line_empty(map->grid[y])) return 1;
//     }
//     return 0;
// }

// /* ************************************************************************** */
// /*                               CONFIG PARSING                                */
// /* ************************************************************************** */

// void parsing_textures(int fd, t_path *path)
// {
//     char *line;
//     ft_bzero(path, sizeof(t_path));

//     while ((line = get_next_line(fd)))
//     {
//         if (is_map_line(line)) { free(line); return; }

//         if (!ft_strncmp(line, "NO ", 3)) path->north = ft_strtrim(line + 3, " \n");
//         else if (!ft_strncmp(line, "SO ", 3)) path->south = ft_strtrim(line + 3, " \n");
//         else if (!ft_strncmp(line, "WE ", 3)) path->west = ft_strtrim(line + 3, " \n");
//         else if (!ft_strncmp(line, "EA ", 3)) path->east = ft_strtrim(line + 3, " \n");

//         free(line);

//         if (path->north && path->south && path->west && path->east)
//             return;
//     }
// }

// void parsing_colors(int fd, t_color *color)
// {
//     char *line;
//     ft_bzero(color, sizeof(t_color));

//     while ((line = get_next_line(fd)))
//     {
//         if (is_map_line(line)) { free(line); return; }

//         if (!ft_strncmp(line, "F ", 2)) color->floor = ft_strtrim(line + 2, " \n");
//         else if (!ft_strncmp(line, "C ", 2)) color->ceiling = ft_strtrim(line + 2, " \n");

//         free(line);

//         if (color->floor && color->ceiling) return;
//     }
// }

// /* ************************************************************************** */
// /*                               MAP READING                                   */
// /* ************************************************************************** */

// char **append_line(char **map, char *line)
// {
//     int i = 0;
//     while (map && map[i]) i++;

//     char **new = malloc(sizeof(char *) * (i + 2));
//     if (!new) { free(line); return NULL; }

//     for (int j = 0; j < i; j++) new[j] = map[j];
//     new[i] = ft_strdup(line);
//     new[i + 1] = NULL;

//     free(map);
//     free(line);
//     return new;
// }

// char **read_map(int fd)
// {
//     char *line;
//     char **map = NULL;

//     while ((line = get_next_line(fd)))
//     {
//         if (is_map_line(line)) break;
//         free(line);
//     }
//     if (!line) return NULL;

//     map = append_line(map, line);

//     while ((line = get_next_line(fd)))
//         map = append_line(map, line);

//     return map;
// }

// /* ************************************************************************** */
// /*                               ENTRY POINT                                     */
// /* ************************************************************************** */

// int parsing(t_data *cub3d, int argc, char **argv)
// {
//     int fd;
//     if (argc != 2) return ft_putendl_fd("Usage: ./cub3D map.cub", 2), 1;

//     fd = open(argv[1], O_RDONLY);
//     if (fd < 0) return ft_putendl_fd("Cannot open file", 2), 1;

//     parsing_textures(fd, &cub3d->map.path);
//     parsing_colors(fd, &cub3d->map.color);

//     cub3d->map.grid = read_map(fd);
//     close(fd);
//     if (!cub3d->map.grid) return ft_putendl_fd("Invalid map", 2), 1;

//     char **norm = normalize_map(cub3d->map.grid);
//     free_map(cub3d->map.grid);
//     cub3d->map.grid = norm;
//     cub3d->map.height = get_height(cub3d->map.grid);
//     cub3d->map.width = get_max_width(cub3d->map.grid);

//     if (check_map_char(&cub3d->map)
//         || check_map_empty_lines(&cub3d->map)
//         || check_map_player(&cub3d->map)
//         || check_map_closed(&cub3d->map))
//         return ft_putendl_fd("Invalid map", 2), 1;

//     // ici tu peux parse le joueur et les portes comme avant
//     cub3d->map.doors = malloc(sizeof(t_door) * MAX_DOORS);
//     cub3d->map.door_count = 0;
//     parse_map_grid(cub3d);

//     // couleurs
//     cub3d->map.color.floor_rgb = convert_rgb_string(cub3d->map.color.floor);
//     cub3d->map.color.ceiling_rgb = convert_rgb_string(cub3d->map.color.ceiling);

//     if (load_all_textures(cub3d))
//         return ft_putendl_fd("Texture loading failed", 2), 1;

//     return 0;
// }
