/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet_collision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:36:32 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/31 20:56:37 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	play_death_scream(t_sprite *e, t_wolf *wolf)
{
	Mix_SetPosition(e->channel, e->angle, e->length * 20);
	if (e->zombie)
		Mix_PlayChannel(e->channel, wolf->audio->z_screams[e->init - 1], 0);
	else
		Mix_PlayChannel(e->channel, wolf->audio->g_screams[e->init - 1], 0);
	Mix_SetPosition(e->channel, 0, 0);
}

void	check_bullet_collision(t_ray *ray, t_sprite ***e_map, t_wolf *wolf)
{
	t_sprite	*sprite;

	if (e_map[ray->map.x][ray->map.y] != NULL)
	{
		sprite = e_map[ray->map.x][ray->map.y];
		ray->hit = 1;
		sprite->hp -= 1;
		if (sprite->hp <= 0)
		{
			play_death_scream(sprite, wolf);
			sprite->dying = 1;
			sprite->prev_time = sprite->time;
			if (wolf->first_enemy_dead == 0)
			{
				Mix_FadeOutChannel(0, 1000);
				wolf->first_enemy_dead = 1;
			}
		}
	}
}

void	handle_bullet_col(t_wolf *wolf, t_map *map)
{
	wolf->ray = init_ray(wolf->player, WIN_WIDTH / 2);
	dda(wolf, wolf->ray, map, 1);
	free(wolf->ray);
}
