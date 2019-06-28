/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 18:37:06 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/13 14:43:43 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		game_loop(t_wolf *wolf)
{
	while (!wolf->quit)
	{
		update_weapon_pos(wolf);
		update_key_pos(wolf);
		ray_cast(wolf);
		sprite_cast(wolf, wolf->sprite_order, wolf->sprite_dist);
		handle_enemy_ai(wolf, &wolf->player, wolf->enemies);
		render_hp(wolf);
		check_pickups(wolf);
		update_and_refresh_frame(wolf);
		handle_events(wolf);
		refresh_enemy_list(&wolf->enemies, wolf);
		if (wolf->first_enemy_dead && Mix_PlayingMusic() == 0)
			Mix_FadeInMusic(wolf->audio->music, -1, 5000);
	}
}

int			main(int argc, char **argv)
{
	t_map		*map;
	t_wolf		*wolf;

	map = NULL;
	wolf = NULL;
	if (argc < 2)
		ft_putendl("Needs map as argument");
	else if (argc > 3)
		ft_putendl("Takes two arguments. Game map and Sprite Sheet.");
	else
	{
		if ((setup_game(&wolf, &map, argc, argv)) == -1)
			return (1);
		game_loop(wolf);
		free_everything(&wolf);
		free(wolf);
		Mix_CloseAudio();
		while (Mix_Init(0))
			Mix_Quit();
		TTF_Quit();
		SDL_QuitSubSystem(SDL_INIT_EVERYTHING);
		SDL_Quit();
	}
	return (0);
}
