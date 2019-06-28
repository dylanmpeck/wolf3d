/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 18:55:54 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/04 18:30:11 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		is_enclosed(t_map *map)
{
	int y;
	int x;
	int y_max;
	int x_max;

	y = 0;
	x = 0;
	y_max = map->height - 1;
	x_max = map->width - 1;
	while (x < map->width)
	{
		if (map->data[0][x] < 1 || map->data[y_max][x] < 1)
			return (0);
		x++;
	}
	while (y < map->height)
	{
		if (map->data[y][0] < 1 || map->data[y][x_max] < 1)
			return (0);
		y++;
	}
	return (1);
}

int		only_walls(t_map *map)
{
	int y;
	int x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->data[y][x] < 1)
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}

int		validate_map_texes(t_map *m)
{
	int y;
	int x;

	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			if (m->data[y][x] < -2 || (m->data[y][x] > MAX_TEX_NUM
				&& m->data[y][x] < D) || m->data[y][x] > LD)
			{
				ft_putendl("Invalid texture number on map.");
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int		is_number(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
