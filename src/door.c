/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:54:59 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/28 22:54:30 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		setup_door_open(t_door *door, int x, int y)
{
	double	time;

	time = SDL_GetTicks();
	door->prev_time = time;
	door->orig_time = time;
	door->time_scale = time;
	door->open = 1;
	door->hold = 0;
	door->close = 0;
	door->added = 1;
	door->map.x = x;
	door->map.y = y;
}

t_door_list	*add_door(t_wolf *wolf, t_door_list **list, int x, int y)
{
	t_door_list	*head;
	t_door_list	*traverse;

	head = *list;
	if (head == NULL)
	{
		head = (t_door_list *)malloc(sizeof(t_door_list));
		head->door = wolf->doors[x][y];
		setup_door_open(head->door, x, y);
		head->next = NULL;
	}
	else
	{
		traverse = head;
		while (traverse->next)
			traverse = traverse->next;
		traverse->next = (t_door_list *)malloc(sizeof(t_door_list));
		traverse->next->door = wolf->doors[x][y];
		setup_door_open(traverse->next->door, x, y);
		traverse->next->next = NULL;
	}
	return (head);
}

void		try_door(t_wolf *wolf, int x, int y)
{
	if (wolf->doors[x][y]->added == 0)
	{
		Mix_PlayChannel(10, wolf->audio->generics[1], 0);
		wolf->open_doors = add_door(wolf, &wolf->open_doors, x, y);
	}
}

void		check_door(t_wolf *wolf, t_player *player, t_map *map, int door)
{
	int x;
	int y;

	x = (int)(player->pos.x + 1.5 * player->dir.x);
	y = (int)player->pos.y;
	if (map->data[x][y] == door)
	{
		if (door == LD && player->has_key == 0)
		{
			Mix_PlayChannel(-1, wolf->audio->generics[11], 0);
			return ;
		}
		try_door(wolf, x, y);
	}
	x = (int)player->pos.x;
	y = (int)(player->pos.y + 1.5 * player->dir.y);
	if (map->data[x][y] == door)
	{
		if (door == LD && player->has_key == 0)
		{
			Mix_PlayChannel(-1, wolf->audio->generics[11], 0);
			return ;
		}
		try_door(wolf, x, y);
	}
}
