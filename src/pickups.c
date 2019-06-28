/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pickups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:57:07 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/03 15:45:19 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	zombie_mode(t_wolf *wolf)
{
	t_sprite	*sprites;
	int			i;

	sprites = wolf->sprite;
	i = 0;
	while (i < wolf->total_sprites)
	{
		if (sprites[i].enemy)
		{
			sprites[i].alive = 1;
			sprites[i].dying = 0;
			sprites[i].zombie = 1;
			sprites[i].pink = 0;
			sprites[i].blue = 1;
			sprites[i].hp = 2;
			sprites[i].death_ind = 0;
			sprites[i].can_alert = 1;
			sprites[i].shooting = 0;
			sprites[i].moving = 0;
			sprites[i].move = 0;
			sprites[i].shoot_ind = 0;
		}
		i++;
	}
}

void	check_pickups(t_wolf *wolf)
{
	t_player	*player;
	SDL_Surface	*screen;
	t_sprite	*pickup;

	player = &wolf->player;
	screen = wolf->sdl->screen;
	if (wolf->collect[(int)player->pos.x][(int)player->pos.y])
	{
		pickup = wolf->collect[(int)player->pos.x][(int)player->pos.y];
		if (pickup->in_world)
		{
			Mix_PlayChannel(-1, wolf->audio->generics[12], 0);
			Mix_FadeInChannel(-1, wolf->audio->generics[10], 0, 200);
			player->has_key = 1;
			pickup->in_world = 0;
			zombie_mode(wolf);
			SDL_FillRect(screen, NULL,
					SDL_MapRGB(screen->format, 0xCD, 0x5C, 0x5C));
			SDL_UpdateWindowSurface(wolf->sdl->window);
		}
	}
}
