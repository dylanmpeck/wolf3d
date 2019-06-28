/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:56:11 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/03 15:50:01 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	player_is_heard(t_wolf *wolf, t_linked **enemies)
{
	t_linked	*traverse;

	traverse = (*enemies)->next;
	while (traverse)
	{
		traverse->sprite->seen_player = 1;
		traverse = traverse->next;
	}
	wolf->player_seen = 1;
}

void	fire_gun(t_wolf *wolf)
{
	if (wolf->player.firing == 0)
	{
		if (Mix_Playing(15) == 0)
			Mix_PlayChannel(15, wolf->audio->generics[2], 0);
		handle_bullet_col(wolf, wolf->map);
		wolf->player.firing = 1;
		if (wolf->player_seen == 0)
			player_is_heard(wolf, &wolf->enemies);
	}
}

void	check_action_keys(const Uint8 *state, t_wolf *wolf)
{
	if (state[SDL_SCANCODE_SPACE] && wolf->player.hp > 0)
		fire_gun(wolf);
	if (state[SDL_SCANCODE_ESCAPE])
		wolf->quit = 1;
	if (state[SDL_SCANCODE_F] && wolf->player.hp > 0)
	{
		check_door(wolf, &wolf->player, wolf->map, LD);
		check_door(wolf, &wolf->player, wolf->map, D);
	}
}

void	check_movement_keys(const Uint8 *state, t_wolf *wolf)
{
	if (state[SDL_SCANCODE_W] || state[SDL_SCANCODE_UP])
		move_forward(&wolf->player, wolf->map, wolf->audio->generics);
	if ((!(state[SDL_SCANCODE_W]) && Mix_Playing(9))
			|| (!(state[SDL_SCANCODE_UP]) && Mix_Playing(9)))
		Mix_FadeOutChannel(9, 300);
	if (state[SDL_SCANCODE_S] || state[SDL_SCANCODE_DOWN])
		move_back(&wolf->player, wolf->map);
	if (state[SDL_SCANCODE_D] || state[SDL_SCANCODE_RIGHT])
		rotate_right(&wolf->player);
	if (state[SDL_SCANCODE_A] || state[SDL_SCANCODE_LEFT])
		rotate_left(&wolf->player);
}

void	handle_events(t_wolf *wolf)
{
	SDL_Event	event;
	const Uint8	*state;

	SDL_PollEvent(&event);
	if (event.type == SDL_QUIT)
	{
		wolf->quit = 1;
		return ;
	}
	else
	{
		state = SDL_GetKeyboardState(NULL);
		check_action_keys(state, wolf);
		if (wolf->player.hp > 0)
			check_movement_keys(state, wolf);
	}
}
