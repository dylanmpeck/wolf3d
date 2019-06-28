/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:25:33 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/13 13:10:08 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	init_ray_step_and_side(t_ray *ray, t_player player)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x =
			(player.pos.x - ray->map.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x =
			(ray->map.x + 1.0f - player.pos.x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y =
			(player.pos.y - ray->map.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y =
			(ray->map.y + 1.0f - player.pos.y) * ray->delta_dist.y;
	}
}

t_ray	*init_ray(t_player player, int x)
{
	t_ray	*ray;
	double	camera_x;

	ray = (t_ray *)malloc(sizeof(t_ray));
	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->dir.x = player.dir.x + player.plane.x * camera_x;
	ray->dir.y = player.dir.y + player.plane.y * camera_x;
	ray->map.x = (int)player.pos.x;
	ray->map.y = (int)player.pos.y;
	ray->delta_dist.x = fabs(1 / ray->dir.x);
	ray->delta_dist.y = fabs(1 / ray->dir.y);
	ray->hit = 0;
	ray->half.x = 0;
	ray->half.y = 0;
	init_ray_step_and_side(ray, player);
	return (ray);
}

void	ray_cast(t_wolf *wolf)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		wolf->ray = init_ray(wolf->player, x);
		dda(wolf, wolf->ray, wolf->map, 0);
		get_wall_bounds(wolf->ray, wolf->player, wolf);
		get_tex_bounds(wolf, wolf->sdl, wolf->ray);
		draw_skybox(wolf->ray, wolf->sdl->textures.skybox, wolf->sdl, x);
		draw_wall(wolf->ray->line, wolf, wolf->sdl, x);
		wolf->zbuffer[x] = wolf->ray->line.wall_dist;
		floor_cast(wolf, wolf->ray, x);
		free(wolf->ray);
		wolf->ray = NULL;
		x++;
	}
}
