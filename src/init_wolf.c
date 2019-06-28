/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wolf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:23:49 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/03 15:08:55 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_linked	*init_enemies_list(void)
{
	t_linked	*enemies;

	enemies = (t_linked *)malloc(sizeof(t_linked));
	enemies->sprite = NULL;
	enemies->next = NULL;
	return (enemies);
}

void		init_wolf(t_wolf *wolf, t_map *map, int total_sprites)
{
	wolf->sdl = init_sdl_struct(wolf->player);
	if (wolf->sdl == NULL)
		return ;
	wolf->zbuffer = (double *)malloc(sizeof(double) * WIN_WIDTH);
	if (total_sprites > 0)
	{
		wolf->sprite_order = (int *)malloc(sizeof(int) * total_sprites);
		wolf->sprite_dist = (double *)malloc(sizeof(double) * total_sprites);
	}
	wolf->quit = 0;
	wolf->weapon = init_sprite(0, 0, 20, 0);
	wolf->key = init_sprite(0, 0, 19, 0);
	wolf->key.inventory = 1;
	wolf->enemies = init_enemies_list();
	wolf->e_tail = wolf->enemies;
	wolf->map = map;
	wolf->e_map = init_e_map(wolf);
	wolf->doors = init_doors(map);
	wolf->collect = init_collect(map, wolf->sprite, wolf->total_sprites);
	wolf->floor_dist_tab = init_fdt();
	wolf->player_seen = 0;
	wolf->open_doors = NULL;
	wolf->first_enemy_dead = 0;
	wolf->ray = NULL;
}
