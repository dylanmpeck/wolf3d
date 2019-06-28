/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:14:12 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/12 15:56:09 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		is_file(const char *path)
{
	struct stat path_stat;

	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

t_point	get_transform(t_draw_vars *dv, t_player *p)
{
	t_point transform;

	transform.x = dv->inv_det * (p->dir.y * dv->pos.x - p->dir.x * dv->pos.y);
	transform.y = dv->inv_det *
		(-(p->plane.y) * dv->pos.x + p->plane.x * dv->pos.y);
	return (transform);
}

int		check_enemy_bullet(double dx, double dy, t_linked *enemy, t_wolf *wolf)
{
	double x;
	double y;

	x = enemy->sprite->x;
	y = enemy->sprite->y;
	while (wolf->map->data[(int)x][(int)y] <= 0)
	{
		if ((int)x == (int)wolf->player.pos.x &&
				(int)y == (int)wolf->player.pos.y)
			return (1);
		x += dx;
		y += dy;
	}
	return (0);
}

void	damage(t_linked *e, t_player *p, SDL_Surface **health, Mix_Chunk **sfx)
{
	Mix_PlayChannel(e->sprite->channel, sfx[7], 0);
	p->hp -= 20;
	*health = set_health_text(p->hp, *health);
}

void	*map_error(char *message)
{
	ft_putendl(message);
	return (NULL);
}
