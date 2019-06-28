/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sdl_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:45:54 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/02 19:20:57 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	free_enemy_directions(t_enemy *enemy)
{
	int i;

	i = 0;
	while (i < E_DIR_SIZE)
	{
		SDL_FreeSurface(enemy->forward[i]);
		SDL_FreeSurface(enemy->forwardleft[i]);
		SDL_FreeSurface(enemy->forwardright[i]);
		SDL_FreeSurface(enemy->left[i]);
		SDL_FreeSurface(enemy->right[i]);
		SDL_FreeSurface(enemy->backright[i]);
		SDL_FreeSurface(enemy->backleft[i]);
		SDL_FreeSurface(enemy->back[i]);
		i++;
	}
	free(enemy->forward);
	free(enemy->forwardleft);
	free(enemy->forwardright);
	free(enemy->left);
	free(enemy->right);
	free(enemy->backright);
	free(enemy->backleft);
	free(enemy->back);
}

void	free_shoot_texes(t_enemy *guard, t_enemy *zombie)
{
	int i;

	i = 0;
	while (i < G_SHO_SIZE)
	{
		SDL_FreeSurface(guard->shoot[i]);
		i++;
	}
	free(guard->shoot);
	i = 0;
	while (i < Z_SHO_SIZE)
	{
		SDL_FreeSurface(zombie->shoot[i]);
		i++;
	}
	free(zombie->shoot);
}

void	free_death_texes(t_enemy *guard, t_enemy *zombie)
{
	int	i;

	i = 0;
	while (i < G_DEA_SIZE)
	{
		SDL_FreeSurface(guard->death[i]);
		i++;
	}
	free(guard->death);
	i = 0;
	while (i < Z_DEA_SIZE)
	{
		SDL_FreeSurface(zombie->death[i]);
		i++;
	}
	free(zombie->death);
}

void	free_textures(t_textures *texture)
{
	int	i;

	i = 0;
	while (i < TEX_TOTAL)
	{
		SDL_FreeSurface(texture->generics[i]);
		i++;
	}
	free(texture->generics);
	i = 0;
	while (i < 4)
	{
		SDL_FreeSurface(texture->skybox[i]);
		i++;
	}
	free(texture->skybox);
	texture->skybox = NULL;
	free_enemy_directions(&texture->guard);
	free_enemy_directions(&texture->zombie);
	free_shoot_texes(&texture->guard, &texture->zombie);
	free_death_texes(&texture->guard, &texture->zombie);
}

void	free_sdl_struct(t_sdl **sdl)
{
	int i;

	i = 0;
	free_textures(&(*sdl)->textures);
	SDL_FreeSurface((*sdl)->health);
	SDL_FreeSurface((*sdl)->gameover);
	SDL_DestroyWindow((*sdl)->window);
}
