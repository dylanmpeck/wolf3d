/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_ui.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:47:32 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/27 21:43:12 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	render_hp(t_wolf *wolf)
{
	SDL_Surface	*health;
	SDL_Surface	*gameover;
	SDL_Surface	*screen;
	SDL_Rect	health_rect;
	SDL_Rect	gameover_rect;

	screen = wolf->sdl->screen;
	health = wolf->sdl->health;
	gameover = wolf->sdl->gameover;
	health_rect = wolf->sdl->health_rect;
	gameover_rect = wolf->sdl->gameover_rect;
	if (wolf->player.hp > 0)
		SDL_BlitSurface(health, NULL, screen, &health_rect);
	else
		SDL_BlitSurface(gameover, NULL, screen, &gameover_rect);
}

void	update_weapon_pos(t_wolf *wolf)
{
	double		pos_x;
	double		pos_y;
	t_player	player;

	player = wolf->player;
	pos_x = player.pos.x + player.dir.x * 1.0f;
	pos_y = player.pos.y + player.dir.y * 1.0f;
	wolf->weapon.x = pos_x;
	wolf->weapon.y = pos_y;
}

void	update_key_pos(t_wolf *wolf)
{
	t_point		pos;
	double		old_dir_x;
	double		rot_speed;
	t_point		rot_dir;
	t_player	p;

	p = wolf->player;
	if (p.has_key == 1)
	{
		rot_speed = 0.436332;
		old_dir_x = p.dir.x;
		rot_dir.x = p.dir.x * cos(-rot_speed) - p.dir.y * sin(-rot_speed);
		rot_dir.y = old_dir_x * sin(-rot_speed) + p.dir.y * cos(-rot_speed);
		pos.x = p.pos.x + rot_dir.x * 1.0f;
		pos.y = p.pos.y + rot_dir.y * 1.0f;
		wolf->key.x = pos.x;
		wolf->key.y = pos.y;
	}
}
