/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 18:45:37 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/01 11:26:06 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		set_enemy_start_dir(t_sprite *sprite, int tex_num)
{
	if (tex_num == EUP_TEX)
	{
		sprite->init = 1;
		sprite->dir.x = -1;
		sprite->dir.y = 0;
	}
	else if (tex_num == ELEFT_TEX)
	{
		sprite->init = 2;
		sprite->dir.x = 0;
		sprite->dir.y = 1;
	}
	else if (tex_num == ERIGHT_TEX)
	{
		sprite->init = 3;
		sprite->dir.x = 0;
		sprite->dir.y = -1;
	}
	else
	{
		sprite->init = 4;
		sprite->dir.x = 1;
		sprite->dir.y = 0;
	}
}

void		init_enemy(t_sprite *sprite, double x, double y, int tex_num)
{
	sprite->can_alert = 1;
	sprite->orig_x = x;
	sprite->orig_y = y;
	sprite->enemy = 1;
	sprite->texture = 0;
	sprite->shooting = 0;
	sprite->moving = 0;
	sprite->time = 0;
	sprite->prev_time = 0;
	sprite->shoot_ind = 0;
	set_enemy_start_dir(sprite, tex_num);
}

t_sprite	init_sprite(double x, double y, int tex_num, int is_enemy)
{
	t_sprite sprite;

	sprite.x = x;
	sprite.y = y;
	sprite.texture = (is_enemy) ? 0 : tex_num;
	sprite.drawn = 0;
	sprite.move = 0;
	sprite.alive = 1;
	sprite.death_ind = 0;
	sprite.hp = 1;
	sprite.pink = (is_enemy || tex_num >= 19) ? 1 : 0;
	sprite.blue = 0;
	sprite.inventory = 0;
	sprite.in_world = 1;
	sprite.zombie = 0;
	sprite.seen_player = 0;
	sprite.dying = 0;
	sprite.can_alert = 0;
	sprite.dv = NULL;
	if (is_enemy == 1)
		init_enemy(&sprite, x, y, tex_num);
	else
		sprite.enemy = 0;
	return (sprite);
}
