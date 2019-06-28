/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sdl_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 19:40:08 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/02 19:03:44 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			invalid_texture(SDL_Surface **generics)
{
	int i;
	int	j;

	i = 0;
	while (i < TEX_TOTAL)
	{
		if (generics[i] == NULL)
		{
			j = 0;
			while (j < TEX_TOTAL)
			{
				if (generics[j] != NULL)
					SDL_FreeSurface(generics[j]);
				j++;
			}
			free(generics);
			ft_putendl("Invalid texture.");
			return (1);
		}
		i++;
	}
	return (0);
}

void		load_enemy_textures(t_enemy *enemy, int zombie)
{
	char	*dir;

	dir = (zombie) ? ft_strdup("textures/zombie/") :
		ft_strdup("textures/guard/");
	enemy->forward = load_forward(dir);
	enemy->forwardright = load_forwardright(dir);
	enemy->forwardleft = load_forwardleft(dir);
	enemy->left = load_left(dir);
	enemy->right = load_right(dir);
	enemy->backright = load_backright(dir);
	enemy->backleft = load_backleft(dir);
	enemy->back = load_back(dir);
	enemy->shoot = load_shoot(dir, zombie);
	enemy->death = load_death(dir, zombie);
	ft_strdel(&dir);
}

SDL_Surface	**generate_textures(void)
{
	SDL_Surface	**texture;

	texture = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * TEX_TOTAL);
	generate_walls(texture);
	generate_sprites(texture);
	return (texture);
}

t_sdl		*init_sdl_struct(t_player player)
{
	t_sdl	*sdl;

	sdl = (t_sdl *)malloc(sizeof(t_sdl));
	sdl->window = SDL_CreateWindow("wolf3d",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			WIN_WIDTH,
			WIN_HEIGHT,
			0);
	if (sdl->window == NULL)
	{
		ft_putendl("Could not create window");
		return (NULL);
	}
	else
		sdl->screen = SDL_GetWindowSurface(sdl->window);
	sdl->textures.generics = generate_textures();
	if (invalid_texture(sdl->textures.generics))
		return (NULL);
	load_enemy_textures(&sdl->textures.guard, 0);
	load_enemy_textures(&sdl->textures.zombie, 1);
	sdl->textures.skybox = generate_sky();
	setup_text(sdl, player);
	sdl->screen_pix = (Uint32 *)sdl->screen->pixels;
	return (sdl);
}
