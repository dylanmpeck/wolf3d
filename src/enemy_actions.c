/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:25:06 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/31 22:20:16 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_towards_player(t_wolf *wolf, t_linked *enemy, t_ai *ai)
{
	double	dx;
	double	dy;

	dx = ai->dx / ai->length;
	dy = ai->dy / ai->length;
	ai->x_move = (int)(enemy->sprite->x + dx * ai->speed);
	ai->y_move = (int)(enemy->sprite->y + dy * ai->speed);
	if (wolf->map->data[ai->x_move][ai->y_move] <= 0 &&
			wolf->e_map[ai->x_move][ai->y_move] == NULL)
	{
		enemy->sprite->x += dx * ai->speed;
		enemy->sprite->y += dy * ai->speed;
		enemy->sprite->dir.x = dx;
		enemy->sprite->dir.y = -dy;
	}
	if (enemy->sprite->move % 2 == 0)
		Mix_PlayChannel(enemy->sprite->channel, wolf->audio->generics[5], 0);
	else
		Mix_PlayChannel(enemy->sprite->channel, wolf->audio->generics[6], 0);
	enemy->sprite->move = (enemy->sprite->move + 1) % 5;
}

void	move_enemy(t_player player, t_linked *enemy, t_ai *ai, t_wolf *wolf)
{
	int	delay;

	if (player.time != 0)
	{
		ai->speed *= (enemy->sprite->zombie) ? Z_SPEED : G_SPEED;
		delay = (enemy->sprite->zombie) ? Z_MOVE_DELAY : G_MOVE_DELAY;
		if (enemy->sprite->time > enemy->sprite->prev_time + delay)
		{
			wolf->e_map[(int)enemy->sprite->x][(int)enemy->sprite->y] = NULL;
			if (ai->length > 3.0f)
				move_towards_player(wolf, enemy, ai);
			else
			{
				enemy->sprite->moving = 0;
				enemy->sprite->move = 0;
			}
			if (enemy->sprite->move == 0)
				enemy->sprite->moving = 0;
			else
				enemy->sprite->prev_time = enemy->sprite->time;
			wolf->e_map[(int)enemy->sprite->x][(int)enemy->sprite->y] =
				enemy->sprite;
		}
	}
}

void	shoot(t_player *p, t_linked *e, SDL_Surface **health, Mix_Chunk **sfx)
{
	int	index_cap;

	index_cap = (e->sprite->zombie) ? ZOMB_SHOOT : GUARD_SHOOT;
	if (e->sprite->time > e->sprite->prev_time + 400)
	{
		e->sprite->shoot_ind = e->sprite->shoot_ind + 1;
		if (e->sprite->zombie && e->sprite->shoot_ind == 1)
			Mix_PlayChannel(e->sprite->channel, sfx[13], 0);
		if (e->sprite->zombie && e->sprite->shoot_ind == 3)
			Mix_PlayChannel(e->sprite->channel, sfx[14], 0);
		if (e->sprite->zombie && e->sprite->shoot_ind == 2)
			damage(e, p, health, sfx);
		if (e->sprite->shoot_ind == index_cap)
		{
			damage(e, p, health, sfx);
			e->sprite->shooting = 0;
			e->sprite->shoot_ind = 0;
			e->sprite->prev_time = e->sprite->time + 500;
		}
		else
			e->sprite->prev_time = e->sprite->time;
	}
}

void	death_anim(t_linked *enemy, t_wolf *wolf)
{
	int	index_cap;

	index_cap = (enemy->sprite->zombie) ? ZOMB_DEATH : GUARD_DEATH;
	if (enemy->sprite->time > enemy->sprite->prev_time + 200)
	{
		if (enemy->sprite->death_ind < index_cap - 1)
			enemy->sprite->death_ind++;
		if (enemy->sprite->death_ind == index_cap - 1)
		{
			Mix_PlayChannel(enemy->sprite->channel,
					wolf->audio->generics[8], 0);
			enemy->sprite->alive = 0;
			wolf->e_map[(int)enemy->sprite->x][(int)enemy->sprite->y] = NULL;
		}
		enemy->sprite->prev_time = enemy->sprite->time;
	}
}
