/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_bounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:44:59 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/13 14:21:24 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

double	get_precise_hit_location(double wall_dist, t_ray *ray, t_player *player)
{
	double hit_loc;

	if (ray->side == 0 || ray->side == 1)
		hit_loc = player->pos.y + wall_dist * ray->dir.y;
	else
		hit_loc = player->pos.x + wall_dist * ray->dir.x;
	hit_loc -= floor((hit_loc));
	return (hit_loc);
}

double	get_half_dist(t_ray *ray, t_player *player)
{
	double	wall_dist;

	wall_dist = 0.0f;
	if (ray->side == 2 || ray->side == 3)
		wall_dist = ((ray->map.y + 0.5f * ray->dir.y) -
				player->pos.y + (1 - ray->step.y) / 2) / ray->dir.y;
	else
		wall_dist = ((ray->map.x + 0.5f * ray->dir.x) -
				player->pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
	return (wall_dist);
}

double	get_wall_dist(t_ray *ray, t_player *player)
{
	double	wall_dist;

	if (ray->side == 0 || ray->side == 1)
		wall_dist = (ray->map.x - player->pos.x +
				(1 - ray->step.x) / 2) / ray->dir.x;
	else
		wall_dist = (ray->map.y - player->pos.y +
				(1 - ray->step.y) / 2) / ray->dir.y;
	return (wall_dist);
}

void	get_tex_bounds(t_wolf *wolf, t_sdl *sdl, t_ray *ray)
{
	t_line	*line;
	int		tex_width;

	line = &ray->line;
	if (wolf->map->data[ray->map.x][ray->map.y] == 99)
		line->tex_num = 26;
	else if (wolf->map->data[ray->map.x][ray->map.y] == 98)
		line->tex_num = 25;
	else
		line->tex_num = wolf->map->data[ray->map.x][ray->map.y] - 1 + ray->side;
	if (wolf->map->data[ray->map.x][ray->map.y] >= 98)
		tex_width = TEX_WIDTH;
	else
		tex_width = WALL_WIDTH;
	line->tex.x = (int)(line->hit_loc * tex_width);
	if (ray->side == 0 || ray->side == 3)
		line->tex.x = tex_width - line->tex.x - 1;
	sdl->tex_pix = (Uint32 *)sdl->textures.generics[line->tex_num]->pixels;
}

void	get_wall_bounds(t_ray *ray, t_player player, t_wolf *wolf)
{
	t_line	line;

	if (wolf->map->data[ray->map.x][ray->map.y] >= 98)
		line.wall_dist = get_half_dist(ray, &player);
	else
		line.wall_dist = get_wall_dist(ray, &player);
	line.height = (int)(WIN_HEIGHT / line.wall_dist);
	line.start = -line.height / 2 + WIN_HEIGHT / 2;
	if (line.start < 0)
		line.start = 0;
	line.end = line.height / 2 + WIN_HEIGHT / 2;
	if (line.end >= WIN_HEIGHT)
		line.end = WIN_HEIGHT - 1;
	line.hit_loc = get_precise_hit_location(line.wall_dist, ray, &player);
	wolf->ray->line = line;
}
