/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_everything.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 21:19:48 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/13 14:53:05 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	free_audio(t_audio **audio)
{
	int i;

	i = 0;
	while (i < SFX_TOTAL)
	{
		if (i < 2)
		{
			Mix_FreeChunk((*audio)->g_alerts[i]);
			Mix_FreeChunk((*audio)->z_alerts[i]);
		}
		if (i < 4)
		{
			Mix_FreeChunk((*audio)->g_screams[i]);
			Mix_FreeChunk((*audio)->z_screams[i]);
		}
		Mix_FreeChunk((*audio)->generics[i]);
		i++;
	}
	free((*audio)->generics);
	free((*audio)->g_alerts);
	free((*audio)->g_screams);
	free((*audio)->z_alerts);
	free((*audio)->z_screams);
	Mix_FreeMusic((*audio)->music);
}

void	free_lookup_tables(t_wolf **wolf)
{
	int i;
	int j;

	i = 0;
	while (i < (*wolf)->map->height)
	{
		j = 0;
		while (j < (*wolf)->map->width)
		{
			if ((*wolf)->doors[i][j])
				ft_memdel((void **)&(*wolf)->doors[i][j]);
			j++;
		}
		free((*wolf)->doors[i]);
		free((*wolf)->e_map[i]);
		free((*wolf)->collect[i]);
		i++;
	}
	free((*wolf)->doors);
	(*wolf)->doors = NULL;
	free((*wolf)->e_map);
	(*wolf)->e_map = NULL;
	free((*wolf)->collect);
	(*wolf)->collect = NULL;
	free((*wolf)->floor_dist_tab);
}

void	free_map(t_map **m)
{
	int i;

	i = 0;
	while (i < (*m)->height)
	{
		if ((*m)->data[i])
			ft_memdel((void **)&(*m)->data[i]);
		i++;
	}
	free((*m)->data);
}

void	free_everything(t_wolf **wolf)
{
	free_audio(&(*wolf)->audio);
	free((*wolf)->audio);
	Mix_AllocateChannels(0);
	free_sdl_struct(&(*wolf)->sdl);
	free((*wolf)->sdl);
	(*wolf)->sdl = NULL;
	free((*wolf)->zbuffer);
	(*wolf)->zbuffer = NULL;
	free_lookup_tables(wolf);
	clean_enemy_list(&(*wolf)->enemies);
	free((*wolf)->enemies);
	(*wolf)->enemies = NULL;
	clean_door_list(&(*wolf)->open_doors);
	free_map(&(*wolf)->map);
	free((*wolf)->map);
	(*wolf)->map = NULL;
	if ((*wolf)->ray)
		free((*wolf)->ray);
	if ((*wolf)->sprite)
		free((*wolf)->sprite);
	if ((*wolf)->total_sprites > 0)
	{
		free((*wolf)->sprite_order);
		free((*wolf)->sprite_dist);
	}
}
