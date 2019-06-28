/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:53:20 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/13 12:33:41 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	move_forward(t_player *player, t_map *map, Mix_Chunk **sounds)
{
	double	move_speed;
	int		x;
	int		y;

	move_speed = player->move_speed;
	if (Mix_Playing(9) == 0)
		Mix_FadeInChannel(9, sounds[4], -1, 300);
	x = (int)((player->pos.x + 1 * player->dir.x) + player->dir.x * move_speed);
	y = (int)(player->pos.y + 1 * player->dir.y);
	if (x >= 0 && x < map->height - 1 && y >= 0 && y < map->width - 1 &&
			map->data[x][y] <= 0)
		player->pos.x += player->dir.x * move_speed;
	else
		Mix_PlayChannel(-1, sounds[3], 0);
	x = (int)(player->pos.x + 1 * player->dir.x);
	y = (int)((player->pos.y + 1 * player->dir.y) + player->dir.y * move_speed);
	if (x >= 0 && x < map->height - 1 && y >= 0 && y < map->width - 1 &&
			map->data[x][y] <= 0)
		player->pos.y += player->dir.y * move_speed;
	else
		Mix_PlayChannel(-1, sounds[3], 0);
}

void	move_back(t_player *player, t_map *map)
{
	double	move_speed;
	int		x;
	int		y;

	move_speed = player->move_speed;
	x = (int)((player->pos.x + 1 * -player->dir.x)
			- player->dir.x * move_speed);
	y = (int)(player->pos.y + 1 * -player->dir.y);
	if (x >= 0 && x < map->height - 1 && y >= 0 && y < map->width - 1 &&
			map->data[x][y] <= 0)
		player->pos.x -= player->dir.x * move_speed;
	x = (int)(player->pos.x + 1 * -player->dir.x);
	y = (int)((player->pos.y + 1 * -player->dir.y)
			- player->dir.y * move_speed);
	if (x >= 0 && x < map->height - 1 && y >= 0 && y < map->width - 1 &&
			map->data[x][y] <= 0)
		player->pos.y -= player->dir.y * move_speed;
}

void	rotate_right(t_player *p)
{
	double old_dir_x;
	double old_plane_x;
	double rot_speed;

	rot_speed = p->rot_speed;
	old_dir_x = p->dir.x;
	p->dir.x = p->dir.x * cos(-rot_speed) - p->dir.y * sin(-rot_speed);
	p->dir.y = old_dir_x * sin(-rot_speed) + p->dir.y * cos(-rot_speed);
	old_plane_x = p->plane.x;
	p->plane.x = p->plane.x * cos(-rot_speed) - p->plane.y * sin(-rot_speed);
	p->plane.y = old_plane_x * sin(-rot_speed) + p->plane.y * cos(-rot_speed);
}

void	rotate_left(t_player *p)
{
	double old_dir_x;
	double old_plane_x;
	double rot_speed;

	rot_speed = p->rot_speed;
	old_dir_x = p->dir.x;
	p->dir.x = p->dir.x * cos(rot_speed) - p->dir.y * sin(rot_speed);
	p->dir.y = old_dir_x * sin(rot_speed) + p->dir.y * cos(rot_speed);
	old_plane_x = p->plane.x;
	p->plane.x = p->plane.x * cos(rot_speed) - p->plane.y * sin(rot_speed);
	p->plane.y = old_plane_x * sin(rot_speed) + p->plane.y * cos(rot_speed);
}
