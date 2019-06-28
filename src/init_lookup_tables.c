/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lookup_tables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:30:17 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/02 17:34:41 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_door		*init_door(int value)
{
	t_door	*door;

	door = (t_door *)malloc(sizeof(t_door));
	door->prev_time = 0;
	door->orig_time = 0;
	door->time_scale = 0;
	door->open = 0;
	door->close = 0;
	door->added = 0;
	door->map.x = 0;
	door->map.y = 0;
	door->value = value;
	return (door);
}

t_sprite	***init_e_map(t_wolf *wolf)
{
	t_sprite	***e_map;
	int			i;
	int			j;

	e_map = (t_sprite ***)malloc(sizeof(t_sprite **) * wolf->map->height);
	i = 0;
	while (i < wolf->map->height)
	{
		e_map[i] = (t_sprite **)malloc(sizeof(t_sprite*) * wolf->map->width);
		j = 0;
		while (j < wolf->map->width)
		{
			e_map[i][j] = NULL;
			j++;
		}
		i++;
	}
	return (e_map);
}

t_door		***init_doors(t_map *map)
{
	int		i;
	int		j;
	t_door	***doors;

	doors = (t_door ***)malloc(sizeof(t_door **) * map->height);
	i = 0;
	while (i < map->height)
	{
		doors[i] = (t_door **)malloc(sizeof(t_door *) * map->width);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			doors[i][j] = (map->data[i][j] >= 98) ?
				init_door(map->data[i][j]) : NULL;
			j++;
		}
		i++;
	}
	return (doors);
}

t_sprite	***init_collect(t_map *map, t_sprite *sprites, int total_sprites)
{
	int			i;
	int			j;
	t_sprite	***collect;

	collect = (t_sprite ***)malloc(sizeof(t_sprite **) * map->height);
	i = 0;
	while (i < map->height)
	{
		collect[i] = (t_sprite **)malloc(sizeof(t_sprite *) * map->width);
		j = 0;
		while (j < map->width)
		{
			collect[i][j] = NULL;
			j++;
		}
		i++;
	}
	i = 0;
	while (i < total_sprites)
	{
		if (sprites[i].texture == KEY_TEX)
			collect[(int)sprites[i].x][(int)sprites[i].y] = &sprites[i];
		i++;
	}
	return (collect);
}

double		*init_fdt(void)
{
	double	*fdt;
	int		y;

	fdt = (double *)malloc(sizeof(double) * WIN_HEIGHT);
	y = 0;
	while (y < WIN_HEIGHT)
	{
		fdt[y] = WIN_HEIGHT / (2.0 * y - WIN_HEIGHT);
		y++;
	}
	return (fdt);
}
