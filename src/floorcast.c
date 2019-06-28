/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:08:50 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/13 14:31:19 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		get_floor_start(t_ray *ray, t_floor *floor)
{
	if (ray->side == 0)
	{
		floor->wall.x = ray->map.x;
		floor->wall.y = ray->map.y + ray->line.hit_loc;
	}
	else if (ray->side == 1)
	{
		floor->wall.x = ray->map.x + 1.0f;
		floor->wall.y = ray->map.y + ray->line.hit_loc;
	}
	else if (ray->side == 2)
	{
		floor->wall.x = ray->map.x + ray->line.hit_loc;
		floor->wall.y = ray->map.y;
	}
	else
	{
		floor->wall.x = ray->map.x + ray->line.hit_loc;
		floor->wall.y = ray->map.y + 1.0f;
	}
	floor->wall_dist = ray->line.wall_dist;
}

void		calc_floor_pos(t_floor *f, t_player player, int y, t_wolf *wolf)
{
	double cur_dist;

	cur_dist = wolf->floor_dist_tab[y];
	f->weight = cur_dist / f->wall_dist;
	f->current.x = f->weight * f->wall.x + (1.0 - f->weight) * player.pos.x;
	f->current.y = f->weight * f->wall.y + (1.0 - f->weight) * player.pos.y;
	f->tex.x = (int)(f->current.x * TEX_WIDTH) % TEX_WIDTH;
	f->tex.y = (int)(f->current.y * TEX_HEIGHT) % TEX_HEIGHT;
	f->map.x = (int)f->current.x;
	f->map.y = (int)f->current.y;
}

static void	draw(t_wolf *wolf, int x, int y)
{
	Uint32	*screen_pix;
	Uint32	*tex_pix;
	t_sdl	*sdl;
	t_floor	floor;
	int		tex_idx;

	screen_pix = wolf->sdl->screen_pix;
	tex_pix = wolf->sdl->tex_pix;
	sdl = wolf->sdl;
	floor = wolf->ray->floor;
	tex_pix = (Uint32 *)sdl->textures.generics[34]->pixels;
	tex_idx = TEX_WIDTH * floor.tex.y + floor.tex.x;
	screen_pix[y * sdl->screen->w + x] = (tex_pix[tex_idx] >> 1) & 8355711;
	if (wolf->map->data[floor.map.x][floor.map.y] < 0
			|| wolf->map->data[floor.map.x][floor.map.y] > 22)
	{
		tex_pix = (Uint32 *)sdl->textures.generics[35]->pixels;
		screen_pix[(WIN_HEIGHT - y) * sdl->screen->w + x] =
			(tex_pix[tex_idx] >> 1) & 8355711;
	}
}

void		draw_floor_and_ceiling(t_wolf *wolf, int x)
{
	int		y;

	if (wolf->ray->line.end < 0)
		wolf->ray->line.end = WIN_HEIGHT;
	y = wolf->ray->line.end + 1;
	while (y < WIN_HEIGHT)
	{
		calc_floor_pos(&wolf->ray->floor, wolf->player, y, wolf);
		draw(wolf, x, y);
		y++;
	}
}

/*
** check for >= 97 is for doors/half walls
*/

void		floor_cast(t_wolf *wolf, t_ray *ray, int x)
{
	get_floor_start(ray, &ray->floor);
	if (wolf->map->data[ray->map.x][ray->map.y] >= 97)
	{
		if (ray->side == 0 || ray->side == 1)
			ray->floor.wall.x += 0.5 * ray->dir.x;
		if (ray->side == 2 || ray->side == 3)
			ray->floor.wall.y += 0.5 * ray->dir.y;
	}
	draw_floor_and_ceiling(wolf, x);
}
