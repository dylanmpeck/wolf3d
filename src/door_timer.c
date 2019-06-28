/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_timer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 21:10:52 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/29 17:45:37 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

static void	close_timer(double time, t_door_list *d, int *delete)
{
	if (time - d->door->prev_time >= 100)
	{
		d->door->prev_time = time;
		d->door->time_scale -= 100;
	}
	if (d->door->time_scale - d->door->orig_time <= 0)
	{
		d->door->close = 0;
		d->door->added = 0;
		*delete = 1;
	}
}

static void	hold_timer(t_wolf *wolf, double time, t_door_list *d)
{
	if (time - d->door->prev_time >= 100)
	{
		if (wolf->map->data[d->door->map.x][d->door->map.y] == -1)
			wolf->map->data[d->door->map.x][d->door->map.y] = d->door->value;
		d->door->prev_time = time;
		d->door->hold = 0;
		d->door->close = 1;
	}
}

static void	open_timer(t_wolf *wolf, double time, t_door_list *d)
{
	if (time - d->door->prev_time > 100)
	{
		d->door->prev_time = time;
		d->door->time_scale += 100;
	}
	if (d->door->time_scale >= d->door->orig_time + 1000)
	{
		Mix_HaltChannel(10);
		Mix_PlayChannel(-1, wolf->audio->generics[0], 0);
		wolf->map->data[d->door->map.x][d->door->map.y] = -1;
		d->door->prev_time += 3000;
		d->door->open = 0;
		d->door->hold = 1;
	}
}

void		update_door_timer(t_wolf *wolf, t_door_list **d_list)
{
	double		time;
	t_door_list	*d;
	t_door_list	*temp;
	int			delete;

	delete = 0;
	time = wolf->player.time;
	d = *d_list;
	while (d)
	{
		if (d->door->open == 1)
			open_timer(wolf, time, d);
		if (d->door->hold == 1)
			hold_timer(wolf, time, d);
		if (d->door->close == 1)
			close_timer(time, d, &delete);
		temp = (delete) ? d : NULL;
		d = d->next;
		if (delete)
		{
			free(temp);
			*d_list = (d) ? d : NULL;
			delete = 0;
		}
	}
}
