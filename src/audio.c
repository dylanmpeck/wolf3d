/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:38:34 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/03 15:30:05 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int			get_channel(void)
{
	int channel;

	channel = 0;
	while (Mix_Playing(channel))
	{
		channel++;
		if (channel == 8)
			return (0);
	}
	return (channel);
}

Mix_Chunk	**load_generics(void)
{
	Mix_Chunk **generics;

	generics = (Mix_Chunk **)malloc(sizeof(Mix_Chunk *) * 15);
	generics[0] = Mix_LoadWAV("sfx/click.wav");
	generics[1] = Mix_LoadWAV("sfx/dooropen.wav");
	generics[2] = Mix_LoadWAV("sfx/gunshot.wav");
	generics[3] = Mix_LoadWAV("sfx/collision.wav");
	generics[4] = Mix_LoadWAV("sfx/wolfsteps.wav");
	generics[5] = Mix_LoadWAV("sfx/e_step1.wav");
	generics[6] = Mix_LoadWAV("sfx/e_step2.wav");
	generics[7] = Mix_LoadWAV("sfx/e_gunshot.wav");
	generics[8] = Mix_LoadWAV("sfx/bodyfall.wav");
	generics[9] = Mix_LoadWAV("sfx/ambience.wav");
	generics[10] = Mix_LoadWAV("sfx/thunder.wav");
	generics[11] = Mix_LoadWAV("sfx/locked.wav");
	generics[12] = Mix_LoadWAV("sfx/pickup.wav");
	generics[13] = Mix_LoadWAV("sfx/shing1.wav");
	generics[14] = Mix_LoadWAV("sfx/shing2.wav");
	return (generics);
}

t_audio		*load_sounds(void)
{
	t_audio	*sounds;

	sounds = (t_audio *)malloc(sizeof(t_audio));
	sounds->g_screams = (Mix_Chunk **)malloc(sizeof(Mix_Chunk *) * 4);
	sounds->g_screams[0] = Mix_LoadWAV("sfx/g_scream1.wav");
	sounds->g_screams[1] = Mix_LoadWAV("sfx/g_scream2.wav");
	sounds->g_screams[2] = Mix_LoadWAV("sfx/g_scream3.wav");
	sounds->g_screams[3] = Mix_LoadWAV("sfx/g_scream4.wav");
	sounds->z_screams = (Mix_Chunk **)malloc(sizeof(Mix_Chunk *) * 4);
	sounds->z_screams[0] = Mix_LoadWAV("sfx/z_scream1.wav");
	sounds->z_screams[1] = Mix_LoadWAV("sfx/z_scream2.wav");
	sounds->z_screams[2] = Mix_LoadWAV("sfx/z_scream3.wav");
	sounds->z_screams[3] = Mix_LoadWAV("sfx/z_scream4.wav");
	sounds->g_alerts = (Mix_Chunk **)malloc(sizeof(Mix_Chunk *) * 2);
	sounds->g_alerts[0] = Mix_LoadWAV("sfx/g_alert1.wav");
	sounds->g_alerts[1] = Mix_LoadWAV("sfx/g_alert1.wav");
	sounds->z_alerts = (Mix_Chunk **)malloc(sizeof(Mix_Chunk *) * 2);
	sounds->z_alerts[0] = Mix_LoadWAV("sfx/z_alert1.wav");
	sounds->z_alerts[1] = Mix_LoadWAV("sfx/z_alert2.wav");
	sounds->generics = load_generics();
	return (sounds);
}

void		init_audio(t_wolf *wolf)
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 512) == -1)
		ft_putendl("Mixer failed");
	Mix_AllocateChannels(16);
	Mix_ReserveChannels(8);
	wolf->audio = load_sounds();
	wolf->audio->music = Mix_LoadMUS("sfx/WolfBGM.wav");
	Mix_Volume(8, 64);
	Mix_FadeInChannel(8, wolf->audio->generics[9], -1, 1000);
}
