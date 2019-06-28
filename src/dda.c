/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:34:25 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/29 20:14:08 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

/*
** side 0 = facing north
** side 1 = facing south
** side 2 = facing west
** side 3 = facing east
*/

void	move_one_step(t_ray *ray)
{
	if (ray->side_dist.x < ray->side_dist.y)
	{
		ray->side_dist.x += ray->delta_dist.x;
		ray->map.x += ray->step.x;
		if (ray->step.x == 1)
			ray->side = 0;
		else
			ray->side = 1;
	}
	else
	{
		ray->side_dist.y += ray->delta_dist.y;
		ray->map.y += ray->step.y;
		if (ray->step.y == 1)
			ray->side = 2;
		else
			ray->side = 3;
	}
}

void	open_door(t_wolf *wolf, t_ray *ray, t_player *p, double time)
{
	double	wall_dist;
	double	hit_loc;
	double	timer;

	wall_dist = get_wall_dist(ray, p);
	hit_loc = get_precise_hit_location(wall_dist, ray, p);
	timer = (time - wolf->doors[ray->map.x][ray->map.y]->orig_time) / 1000.0f;
	if (hit_loc > timer)
		ray->hit = 1;
}

int		check_half_wall(t_ray *ray, t_player *player, t_map *map)
{
	double	wall_dist;
	double	hit_loc;
	int		x;
	int		y;

	wall_dist = get_wall_dist(ray, player);
	hit_loc = get_precise_hit_location(wall_dist, ray, player);
	if (ray->side == 2 || ray->side == 3)
	{
		x = (int)(ray->map.x + hit_loc + 0.5f * ray->dir.x);
		y = (int)ray->map.y;
		if (map->data[x][y] >= 98)
			return (1);
	}
	else
	{
		x = (int)(ray->map.x + hit_loc + 0.5f * ray->dir.y);
		y = (int)ray->map.y;
		if (map->data[x][y] >= 98)
			return (1);
	}
	return (0);
}

void	dda(t_wolf *w, t_ray *ray, t_map *map, int bullet)
{
	int x;
	int y;

	while (ray->hit == 0)
	{
		move_one_step(ray);
		x = ray->map.x;
		y = ray->map.y;
		if (map->data[x][y] > 0 && map->data[x][y] <= 13)
			ray->hit = 1;
		else if (w->doors[x][y] != NULL &&
				(w->doors[x][y]->open ||
				w->doors[x][y]->close))
		{
			if (check_half_wall(ray, &w->player, map))
				open_door(w, ray, &w->player, w->doors[x][y]->time_scale);
		}
		else if (map->data[x][y] >= 98)
		{
			if (check_half_wall(ray, &w->player, map))
				ray->hit = 1;
		}
		if (bullet)
			check_bullet_collision(ray, w->e_map, w);
	}
}
