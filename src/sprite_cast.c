/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:52:29 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/03 15:52:51 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	add_enemy(t_sprite *sprite, t_wolf *wolf, t_linked **tail)
{
	t_linked *new_node;

	if (sprite->enemy == 1 && sprite->drawn == 1 && sprite->alive &&
			wolf->e_map[(int)sprite->x][(int)sprite->y] == NULL)
	{
		wolf->e_map[(int)sprite->x][(int)sprite->y] = sprite;
		if (sprite->prev_time == 0)
			sprite->prev_time = SDL_GetTicks();
		new_node = (t_linked *)malloc(sizeof(t_linked));
		new_node->sprite = sprite;
		new_node->next = NULL;
		(*tail)->next = new_node;
		*tail = new_node;
	}
}

void	draw_weapon(t_sprite *weapon, t_wolf *wolf)
{
	double		time;
	double		reload_time;
	t_player	*player;

	reload_time = 150.0f;
	player = &wolf->player;
	if (player->firing == 1)
	{
		time = SDL_GetTicks();
		if (time > player->prev_fire_time + 100)
		{
			player->prev_fire_time = time;
			weapon->texture = weapon->texture + 1;
		}
		if (weapon->texture == 25)
		{
			Mix_HaltChannel(15);
			weapon->texture = 20;
			player->firing = 0;
			player->prev_fire_time += reload_time;
		}
		draw_sprites(weapon, wolf, 1);
	}
	else
		draw_sprites(weapon, wolf, 1);
}

void	sort_by_dist(t_wolf *wolf, int *sprite_order, double *sprite_dist)
{
	int			i;
	t_sprite	*sprite;
	t_player	player;
	double		dx;
	double		dy;

	i = 0;
	sprite = wolf->sprite;
	player = wolf->player;
	while (i < wolf->total_sprites)
	{
		sprite_order[i] = i;
		dx = player.pos.x - sprite[i].x;
		dy = player.pos.y - sprite[i].y;
		sprite_dist[i] = (dx * dx + dy * dy);
		i++;
	}
	sort_sprites(sprite_order, sprite_dist, 0, wolf->total_sprites - 1);
}

void	sprite_cast(t_wolf *wolf, int *sprite_order, double *sprite_dist)
{
	int			i;
	t_sprite	*sprite;

	i = 0;
	sprite = wolf->sprite;
	sort_by_dist(wolf, sprite_order, sprite_dist);
	while (i < wolf->total_sprites)
	{
		if (sprite[sprite_order[i]].in_world)
			draw_sprites(&sprite[sprite_order[i]], wolf, 0);
		add_enemy(&sprite[sprite_order[i]], wolf, &wolf->e_tail);
		i++;
	}
	draw_weapon(&wolf->weapon, wolf);
	if (wolf->player.has_key)
		draw_sprites(&wolf->key, wolf, 1);
}
