/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:50:18 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/13 14:31:36 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	delete_enemy_node(t_wolf *wolf, t_linked **delete, t_linked **prev)
{
	t_linked	*temp;

	wolf->e_map[(int)(*delete)->sprite->x][(int)(*delete)->sprite->y] = NULL;
	if ((*delete)->sprite->alive)
	{
		(*delete)->sprite->x = (*delete)->sprite->orig_x;
		(*delete)->sprite->y = (*delete)->sprite->orig_y;
	}
	(*delete)->sprite->seen_player = 0;
	(*prev)->next = (*delete)->next;
	temp = (*delete);
	*delete = (*delete)->next;
	temp->sprite = NULL;
	temp->next = NULL;
	free(temp);
	temp = NULL;
}

void	refresh_enemy_list(t_linked **enemies, t_wolf *wolf)
{
	t_linked *delete;
	t_linked *prev;

	delete = (*enemies)->next;
	prev = *enemies;
	while (delete)
	{
		delete->sprite->time = SDL_GetTicks();
		if (delete->sprite->length > 15.0f || !delete->sprite->alive)
			delete_enemy_node(wolf, &delete, &prev);
		else
		{
			prev = delete;
			delete = delete->next;
		}
	}
	if (prev->next == NULL)
		wolf->e_tail = prev;
}

void	update_and_refresh_frame(t_wolf *wolf)
{
	double			frame_time;
	SDL_Surface		*screen;
	t_player		*player;

	player = &wolf->player;
	screen = wolf->sdl->screen;
	player->prev_time = player->time;
	player->time = SDL_GetTicks();
	wolf->player_seen = 0;
	frame_time = (double)((player->time - player->prev_time) / 1000.0f);
	SDL_UpdateWindowSurface(wolf->sdl->window);
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
	player->move_speed = frame_time * 5.0f;
	player->rot_speed = frame_time * 2.5f;
	update_door_timer(wolf, &wolf->open_doors);
}
