/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_angle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 18:35:59 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/28 19:19:53 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** Angle degrees are as follows:
** -22 - +22 = Forward
** 22 - 67 = FowardLeft
** 67 - 112 = Left (Player's Right)
** 112 - 157 = BackLeft
** 157 - 180 - -158 = Back
** -158 - -113 = BackRight
** -113 - -68 = Right
** -68 - -23 = ForwardRight
*/

void	*check_angle(t_sprite *sprite, t_enemy *enemy, int angle)
{
	if (angle >= -22 && angle <= 22)
		return (enemy->forward[sprite->move]->pixels);
	else if (angle > 22 && angle <= 67)
		return (enemy->forwardleft[sprite->move]->pixels);
	else if (angle > 67 && angle <= 112)
		return (enemy->left[sprite->move]->pixels);
	else if (angle > 112 && angle <= 157)
		return (enemy->backleft[sprite->move]->pixels);
	else if ((angle > 157 && angle <= 180) || (angle >= -180 && angle <= -158))
		return (enemy->back[sprite->move]->pixels);
	else if (angle > -158 && angle <= -113)
		return (enemy->backright[sprite->move]->pixels);
	else if (angle > -113 && angle <= -68)
		return (enemy->right[sprite->move]->pixels);
	else if (angle > -68 && angle <= -23)
		return (enemy->forwardright[sprite->move]->pixels);
	return (enemy->back[0]->pixels);
}

void	*get_angle(t_sprite *sprite, t_player *player, t_enemy *enemy)
{
	double	dx;
	double	dy;
	int		angle;

	dx = player->pos.x - sprite->x;
	dy = player->pos.y - sprite->y;
	angle = (int)(atan2(dy, dx) * 180 / M_PI);
	angle += (int)(atan2(sprite->dir.y, sprite->dir.x) * 180 / M_PI);
	if (angle > 180)
		angle = -180 + (angle - 180);
	if ((angle >= -22 && angle <= 22) || (angle > 22 && angle <= 67)
			|| (angle > -68 && angle <= -23))
		sprite->seen_player = 1;
	return (check_angle(sprite, enemy, angle));
}

Uint32	*get_texture(t_sprite *sprite, t_player *player, t_textures *tex)
{
	t_enemy	enemy;

	if (sprite->enemy == 1)
	{
		enemy = (sprite->zombie) ? tex->zombie : tex->guard;
		if (sprite->dying == 1)
			return ((Uint32 *)enemy.death[sprite->death_ind]->pixels);
		else
		{
			if (sprite->shooting == 1)
				return ((Uint32 *)enemy.shoot[sprite->shoot_ind]->pixels);
			else
				return ((Uint32 *)get_angle(sprite, player, &enemy));
		}
	}
	else
		return ((Uint32 *)tex->generics[sprite->texture]->pixels);
}
