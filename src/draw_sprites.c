/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 16:57:12 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/03 15:51:48 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_draw_vars	*init_sprite_dvs(t_sprite *sprite, t_player *p, int hud, int offset)
{
	t_draw_vars	*dv;

	dv = (t_draw_vars *)malloc(sizeof(t_draw_vars));
	dv->pos.x = sprite->x - p->pos.x;
	dv->pos.y = sprite->y - p->pos.y;
	dv->inv_det = 1.0 / (p->plane.x * p->dir.y - p->dir.x * p->plane.y);
	dv->transform = get_transform(dv, p);
	dv->screen_x = (int)((WIN_WIDTH / 2) *
			(1 + dv->transform.x / dv->transform.y));
	dv->screen_adj = (int)(offset / dv->transform.y);
	dv->height = abs((int)(WIN_HEIGHT / dv->transform.y)) / hud;
	dv->start.y = -dv->height / 2 + WIN_HEIGHT / 2 + dv->screen_adj;
	if (dv->start.y < 0)
		dv->start.y = 0;
	dv->end.y = dv->height / 2 + WIN_HEIGHT / 2 + dv->screen_adj;
	if (dv->end.y >= WIN_HEIGHT)
		dv->end.y = WIN_HEIGHT - 1;
	dv->width = abs((int)(WIN_HEIGHT / dv->transform.y)) / hud;
	dv->start.x = -dv->width / 2 + dv->screen_x;
	if (dv->start.x < 0)
		dv->start.x = 0;
	dv->end.x = dv->width / 2 + dv->screen_x;
	if (dv->end.x >= WIN_WIDTH)
		dv->end.x = WIN_WIDTH - 1;
	return (dv);
}

/*
** i = pixel being set on screen
** j = pixel being used from sprite
** should name them better in future
*/

static void	set_pixel(t_wolf *wolf, t_sprite *sprite, int i, int j)
{
	Uint32 *screen;

	screen = wolf->sdl->screen_pix;
	if (sprite->pink == 1)
	{
		if ((sprite->pix[j] & 0x0067FF77) != 0 ||
			(sprite->pix[j] & 0x00FFFFFF) == 0 ||
			(sprite->pix[j] & 0x00FFFF77) == 0)
			screen[i] = sprite->pix[j];
	}
	else if (sprite->blue == 1)
	{
		if ((sprite->pix[j] & 0x00FFFF7F) != 0 ||
			(sprite->pix[j] & 0x00FFFFFF) == 0)
			screen[i] = sprite->pix[j];
	}
	else if ((sprite->pix[j] & 0x00FFFFFF) != 0)
		screen[i] = sprite->pix[j];
}

static void	draw_line(t_wolf *wolf, t_sprite *sprite, int stripe)
{
	int			y;
	t_draw_vars	*dv;
	int			tex_w;
	int			tex_h;

	dv = sprite->dv;
	y = dv->start.y;
	sprite->drawn = 1;
	tex_w = (sprite->zombie) ? TEX_WIDTH + 1 : TEX_WIDTH;
	tex_h = (sprite->zombie) ? TEX_HEIGHT + 1 : TEX_HEIGHT;
	while (y < dv->end.y)
	{
		dv->d = (y - dv->screen_adj) * 256 -
			WIN_HEIGHT * 128 + dv->height * 128;
		dv->tex.y = ((dv->d * tex_h) / dv->height) / 256;
		set_pixel(wolf, sprite, y * WIN_WIDTH + stripe,
				tex_w * dv->tex.y + dv->tex.x);
		y++;
	}
}

static void	draw(t_sprite *sprite, t_wolf *wolf, int inventory)
{
	t_draw_vars	*dv;
	int			tex_width;
	int			stripe;

	dv = sprite->dv;
	stripe = dv->start.x;
	tex_width = (sprite->zombie) ? TEX_WIDTH + 1 : TEX_WIDTH;
	while (stripe < dv->end.x)
	{
		dv->tex.x = (int)(256 * (stripe - (-dv->width / 2 + dv->screen_x))
				* tex_width / dv->width) / 256;
		if (inventory)
			draw_line(wolf, sprite, stripe);
		else if (dv->transform.y > 0 && stripe > 0 && stripe < WIN_WIDTH
				&& dv->transform.y < wolf->zbuffer[stripe])
			draw_line(wolf, sprite, stripe);
		else
			sprite->drawn = 0;
		stripe++;
	}
}

void		draw_sprites(t_sprite *sprite, t_wolf *wolf, int inventory)
{
	if (sprite->inventory == 1)
		sprite->dv = init_sprite_dvs(sprite, &wolf->player, 3, 150);
	else
		sprite->dv = init_sprite_dvs(sprite, &wolf->player, 1, 0);
	sprite->pix = get_texture(sprite, &wolf->player, &wolf->sdl->textures);
	draw(sprite, wolf, inventory);
	free(sprite->dv);
	sprite->dv = NULL;
}
