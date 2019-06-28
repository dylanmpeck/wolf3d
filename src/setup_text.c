/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:14:51 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/02 19:21:12 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		*error(void)
{
	ft_putendl(SDL_GetError());
	return (NULL);
}

SDL_Color	make_color(int r, int g, int b)
{
	SDL_Color color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.a = 0xFF;
	return (color);
}

SDL_Surface	*set_health_text(int hp, SDL_Surface *cur_health)
{
	char		*message;
	char		*hp_str;
	SDL_Color	color;
	TTF_Font	*font;
	SDL_Surface *surface;

	if (cur_health != NULL)
		SDL_FreeSurface(cur_health);
	hp_str = ft_itoa(hp);
	color = make_color(220, 20, 60);
	message = ft_strjoin("Health: ", hp_str);
	ft_strdel(&hp_str);
	font = TTF_OpenFont("fonts/horrendo.ttf", 32);
	if (font == NULL)
		return (error());
	surface = TTF_RenderText_Blended(font, message, color);
	if (surface == NULL)
	{
		TTF_CloseFont(font);
		return (error());
	}
	TTF_CloseFont(font);
	ft_strdel(&message);
	return (surface);
}

SDL_Surface	*set_gameover_text(void)
{
	char		*message;
	SDL_Color	color;
	TTF_Font	*font;
	SDL_Surface	*surface;

	color.r = 220;
	color.g = 20;
	color.b = 60;
	color.a = 0xFF;
	message = ft_strdup("You are dead");
	font = TTF_OpenFont("fonts/horrendo.ttf", 64);
	if (font == NULL)
		return (error());
	surface = TTF_RenderText_Blended(font, message, color);
	if (surface == NULL)
	{
		TTF_CloseFont(font);
		return (error());
	}
	ft_strdel(&message);
	TTF_CloseFont(font);
	return (surface);
}

void		setup_text(t_sdl *sdl, t_player player)
{
	sdl->health = set_health_text(player.hp, NULL);
	if (sdl->health == NULL)
	{
		sdl = NULL;
		return ;
	}
	sdl->health_rect.x = 100;
	sdl->health_rect.y = WIN_HEIGHT - 100;
	sdl->health_rect.w = 100;
	sdl->health_rect.h = 100;
	sdl->gameover = set_gameover_text();
	if (sdl->gameover == NULL)
	{
		sdl = NULL;
		return ;
	}
	sdl->gameover_rect.x = (WIN_WIDTH / 2) - 200;
	sdl->gameover_rect.y = (WIN_HEIGHT / 2) - 50;
	sdl->gameover_rect.w = 100;
	sdl->gameover_rect.h = 100;
}
