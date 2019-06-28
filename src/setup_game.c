/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 18:10:00 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/12 15:59:15 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static int	error(char *message)
{
	ft_putendl(message);
	return (-1);
}

void		get_player_pos(t_map *map, t_player *player)
{
	int x;
	int y;

	x = 0;
	while (x < map->height)
	{
		y = 0;
		while (y < map->width)
		{
			if (map->data[x][y] == -2)
			{
				player->pos.x = x + 0.5f;
				player->pos.y = y + 0.5f;
				if ((x + 1 < map->width && map->data[x + 1][y] == 0) ||
						(x - 1 >= 0 && map->data[x - 1][y] == 0))
					map->data[x][y] = 0;
				if ((x + 1 < map->width && map->data[x + 1][y] == -1) ||
						(x - 1 >= 0 && map->data[x - 1][y] == -1))
					map->data[x][y] = -1;
				player->pos_count++;
			}
			y++;
		}
		x++;
	}
}

t_player	init_player(t_map *map)
{
	t_player player;

	player.pos_count = 0;
	player.pos.x = -1;
	player.pos.y = -1;
	get_player_pos(map, &player);
	if (player.pos_count != 1)
	{
		ft_putendl("Invalid number of player positions on map.");
		player.pos.x = -1;
	}
	player.dir.x = -1;
	player.dir.y = 0;
	player.plane.x = 0;
	player.plane.y = 0.66;
	player.time = 0;
	player.prev_time = 0;
	player.hp = 100;
	player.firing = 0;
	player.prev_fire_time = 0;
	player.has_key = 0;
	return (player);
}

int			check_sprite_sheet(t_wolf **wolf, t_map **map, int c, char **v)
{
	if (c > 2)
	{
		if (!(is_file(v[2])))
			return (error("Sprite arg is not valid file"));
		(*wolf)->sprite = read_sprite_file(v[2],
				&(*wolf)->total_sprites, *map);
		if ((*wolf)->sprite == NULL)
		{
			free_map(map);
			free(*wolf);
			return (error("Sprite sheet is null."));
		}
	}
	else
	{
		(*wolf)->sprite = NULL;
		(*wolf)->sprite_order = NULL;
		(*wolf)->sprite_dist = NULL;
	}
	return (0);
}

int			setup_game(t_wolf **wolf, t_map **map, int argc, char **argv)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	if (TTF_Init() != 0)
	{
		SDL_Quit();
		return (error("TTF couldn't init."));
	}
	srand(time(NULL));
	if (!(is_file(argv[1])))
		return (error("Map arg is not valid file"));
	*map = read_map(argv[1]);
	if (*map == NULL)
		return (error("Map is null"));
	*wolf = (t_wolf *)malloc(sizeof(t_wolf));
	(*wolf)->total_sprites = 0;
	if (check_sprite_sheet(wolf, map, argc, argv) == -1)
		return (-1);
	(*wolf)->player = init_player(*map);
	if ((*wolf)->player.pos.x < 0 || (*wolf)->player.pos.y < 0)
		return (error("Player position is invalid"));
	init_wolf(*wolf, *map, (*wolf)->total_sprites);
	if ((*wolf)->sdl == NULL || validate_sdl((*wolf)->sdl) == -1)
		return (-1);
	init_audio(*wolf);
	return (0);
}
