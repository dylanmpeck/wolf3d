/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_sdl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 19:06:26 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/02 19:43:46 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		cleanup_sdl(t_sdl *sdl)
{
	free_sdl_struct(&sdl);
	return (-1);
}

int		check_enem_directions(t_enemy *enemy)
{
	int i;

	i = 0;
	while (i < E_DIR_SIZE)
	{
		if (enemy->forward[i] == NULL)
			return (-1);
		if (enemy->forwardleft[i] == NULL)
			return (-1);
		if (enemy->forwardright[i] == NULL)
			return (-1);
		if (enemy->left[i] == NULL)
			return (-1);
		if (enemy->right[i] == NULL)
			return (-1);
		if (enemy->backright[i] == NULL)
			return (-1);
		if (enemy->back[i] == NULL)
			return (-1);
		i++;
	}
	return (0);
}

int		check_enem_sho_and_deth(t_enemy *enemy, int zombie)
{
	int		i;
	int		sho_size;
	int		dea_size;

	i = 0;
	sho_size = (zombie) ? Z_SHO_SIZE : G_SHO_SIZE;
	dea_size = (zombie) ? Z_DEA_SIZE : G_DEA_SIZE;
	while (i < sho_size)
	{
		if (enemy->shoot[i] == NULL)
			return (-1);
		i++;
	}
	i = 0;
	while (i < dea_size)
	{
		if (enemy->death[i] == NULL)
			return (-1);
		i++;
	}
	return (0);
}

int		check_enemy_textures(t_enemy *enemy, int zombie)
{
	if (check_enem_directions(enemy) == -1)
	{
		if (zombie)
			ft_putendl("Invalid zombie dir image.");
		else
			ft_putendl("Invalid guard dir image.");
		return (-1);
	}
	if (check_enem_sho_and_deth(enemy, zombie) == -1)
	{
		if (zombie)
			ft_putendl("Invalid zombie shoot or death image.");
		else
			ft_putendl("Invalid guard shoot or death image.");
		return (-1);
	}
	return (0);
}

int		validate_sdl(t_sdl *sdl)
{
	SDL_Surface **skybox;
	int			i;

	if (check_enemy_textures(&sdl->textures.guard, 0) == -1)
		return (cleanup_sdl(sdl));
	if (check_enemy_textures(&sdl->textures.zombie, 1) == -1)
		return (cleanup_sdl(sdl));
	skybox = sdl->textures.skybox;
	i = 0;
	while (i < 4)
	{
		if (skybox[i] == NULL)
		{
			ft_putendl("Invalid skybox image.");
			return (cleanup_sdl(sdl));
		}
		i++;
	}
	return (1);
}
