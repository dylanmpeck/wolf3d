/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_and_sky.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 21:46:15 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/13 14:34:32 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

Uint32	*get_skybox_quad(t_ray *ray, SDL_Surface **skybox, t_pair *sky)
{
	Uint32 *sky_pix;

	if (ray->dir.x < 0 && ray->dir.y < 0)
	{
		sky->x = (ray->dir.x + (-ray->dir.y)) * 256;
		sky_pix = (Uint32 *)skybox[0]->pixels;
	}
	else if (ray->dir.x < 0 && ray->dir.y >= 0)
	{
		sky->x = (ray->dir.x + ray->dir.y) * 256;
		sky_pix = (Uint32 *)skybox[1]->pixels;
	}
	else if (ray->dir.x >= 0 && ray->dir.y < 0)
	{
		sky->x = (ray->dir.x + ray->dir.y) * 256;
		sky_pix = (Uint32 *)skybox[2]->pixels;
	}
	else
	{
		sky->x = (ray->dir.x + (-ray->dir.y)) * 256;
		sky_pix = (Uint32 *)skybox[3]->pixels;
	}
	return (sky_pix);
}

void	draw_skybox(t_ray *ray, SDL_Surface **skybox, t_sdl *sdl, int x)
{
	t_pair	sky;
	Uint32	*sky_pix;
	int		y;
	int		loc;

	y = 0;
	sky_pix = get_skybox_quad(ray, skybox, &sky);
	while (y < ray->line.start)
	{
		sky.y = (int)((y) / (double)WIN_HEIGHT * 256.0f);
		loc = (256 * (sky.y) + (sky.x));
		sdl->screen_pix[(y * sdl->screen->w + x)] = sky_pix[loc];
		y++;
	}
}

void	draw_wall(t_line line, t_wolf *wolf, t_sdl *sdl, int x)
{
	int		d;
	int		loc;
	int		tex_height;

	if (wolf->map->data[wolf->ray->map.x][wolf->ray->map.y] >= 97)
		tex_height = TEX_HEIGHT;
	else
		tex_height = WALL_HEIGHT;
	while (line.start < line.end)
	{
		d = line.start * 1024 - WIN_HEIGHT * 512 + line.height * 512;
		line.tex.y = ((d * tex_height) / line.height) / 1024;
		loc = (tex_height * line.tex.y + line.tex.x);
		if (wolf->ray->side == 2 || wolf->ray->side == 3)
			sdl->screen_pix[(line.start * sdl->screen->w + x)] =
				(sdl->tex_pix[loc] >> 1) & 8355711;
		else
			sdl->screen_pix[(line.start * sdl->screen->w + x)] =
				sdl->tex_pix[loc];
		line.start++;
	}
}
