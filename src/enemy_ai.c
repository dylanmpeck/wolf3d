/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_ai.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:26:28 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/03 15:51:32 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	do_enemy_action(t_wolf *wolf, t_player *p, t_linked *enemy, t_ai ai)
{
	if (enemy->sprite->moving == 1)
		move_enemy(*p, enemy, &ai, wolf);
	else if (enemy->sprite->shooting == 1)
	{
		if (check_enemy_bullet(ai.dx / ai.length, ai.dy / ai.length,
								enemy, wolf))
			shoot(p, enemy, &wolf->sdl->health, wolf->audio->generics);
		else
			enemy->sprite->shooting = 0;
	}
}

void	decide_enemy_action(t_linked *enemy, t_ai *ai)
{
	if (enemy->sprite->time > enemy->sprite->prev_time + 600)
	{
		if (enemy->sprite->moving == 0 && enemy->sprite->shooting == 0)
		{
			set_decision_ranges(ai->length, enemy);
			make_decision(enemy);
		}
	}
}

void	alert(t_wolf *wolf, t_linked *enemy, t_audio *audio)
{
	if (enemy->sprite->can_alert)
	{
		enemy->sprite->can_alert = 0;
		if (enemy->sprite->zombie)
			Mix_PlayChannel(enemy->sprite->channel,
					audio->z_alerts[enemy->sprite->init % 2], 0);
		else
			Mix_PlayChannel(enemy->sprite->channel,
					audio->g_alerts[enemy->sprite->init % 2], 0);
	}
	wolf->player_seen = 1;
}

t_ai	get_angle_and_dist_from_player(t_linked *enemy, t_player *player)
{
	t_ai	ai;
	int		front_angle;
	int		side_angle;

	ai.speed = (player->time - player->prev_time) / 1000.0f;
	ai.dx = player->pos.x - enemy->sprite->x;
	ai.dy = player->pos.y - enemy->sprite->y;
	ai.length = sqrt(ai.dx * ai.dx + ai.dy * ai.dy);
	enemy->sprite->length = ai.length;
	ai.dot_side = ai.dx * -player->dir.y + ai.dy * player->dir.x;
	ai.dot_front = ai.dx * player->dir.x + ai.dy * player->dir.y;
	ai.dot_side /= ai.length;
	ai.dot_front /= ai.length;
	ai.dot_side = acos(ai.dot_side);
	ai.dot_front = acos(ai.dot_front);
	side_angle = (int)(ai.dot_side * 180 / M_PI);
	front_angle = (int)(ai.dot_front * 180 / M_PI);
	front_angle = (180 - front_angle);
	if (side_angle > 90)
		front_angle = 180 + (180 - front_angle);
	enemy->sprite->channel = get_channel();
	Mix_SetPosition(enemy->sprite->channel, front_angle, ai.length * 20);
	enemy->sprite->angle = front_angle;
	return (ai);
}

/*
**Need to check if alert/wolf->player_seen is lining up properly
*/

void	handle_enemy_ai(t_wolf *wolf, t_player *player, t_linked *enemies)
{
	t_linked	*enemy;
	t_ai		ai;

	enemy = enemies->next;
	while (enemy)
	{
		ai = get_angle_and_dist_from_player(enemy, player);
		if (enemy->sprite->dying == 0)
		{
			if (enemy->sprite->seen_player == 1)
				alert(wolf, enemy, wolf->audio);
			if (wolf->player_seen == 1)
			{
				enemy->sprite->dir.x = ai.dx / ai.length;
				enemy->sprite->dir.y = -(ai.dy / ai.length);
				decide_enemy_action(enemy, &ai);
				do_enemy_action(wolf, player, enemy, ai);
			}
		}
		else
			death_anim(enemy, wolf);
		Mix_SetPosition(enemy->sprite->channel, 0, 0);
		enemy = enemy->next;
	}
}
