/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_textures1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 22:06:22 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/30 22:19:09 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Surface	**load_death(char *dir, int zombie)
{
	SDL_Surface **tex;
	char		*file_name;
	int			append_start;

	if (zombie == 1)
		tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * Z_DEA_SIZE);
	else
		tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * G_DEA_SIZE);
	file_name = ft_strnew(ft_strlen(dir) + ft_strlen("death/1.bmp"));
	ft_strncat(file_name, dir, ft_strlen(dir));
	ft_strncat(file_name, "death/", ft_strlen("death/"));
	append_start = ft_strlen(file_name);
	tex[0] = SDL_LoadBMP(append_in_place(file_name, "1.bmp", append_start));
	tex[1] = SDL_LoadBMP(append_in_place(file_name, "2.bmp", append_start));
	tex[2] = SDL_LoadBMP(append_in_place(file_name, "3.bmp", append_start));
	tex[3] = SDL_LoadBMP(append_in_place(file_name, "4.bmp", append_start));
	tex[4] = SDL_LoadBMP(append_in_place(file_name, "5.bmp", append_start));
	if (zombie == 1)
	{
		tex[5] = SDL_LoadBMP(append_in_place(file_name, "6.bmp", append_start));
		tex[6] = SDL_LoadBMP(append_in_place(file_name, "7.bmp", append_start));
	}
	ft_strdel(&file_name);
	return (tex);
}

SDL_Surface	**load_shoot(char *dir, int zombie)
{
	SDL_Surface	**tex;
	char		*file_name;
	int			append_start;

	if (zombie == 1)
		tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * Z_SHO_SIZE);
	else
		tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * G_SHO_SIZE);
	file_name = ft_strnew(ft_strlen(dir) + ft_strlen("shoot/1.bmp"));
	ft_strncat(file_name, dir, ft_strlen(dir));
	ft_strncat(file_name, "shoot/", ft_strlen("shoot/"));
	append_start = ft_strlen(file_name);
	tex[0] = SDL_LoadBMP(append_in_place(file_name, "1.bmp", append_start));
	tex[1] = SDL_LoadBMP(append_in_place(file_name, "2.bmp", append_start));
	tex[2] = SDL_LoadBMP(append_in_place(file_name, "3.bmp", append_start));
	if (zombie == 1)
		tex[3] = SDL_LoadBMP(append_in_place(file_name, "4.bmp", append_start));
	ft_strdel(&file_name);
	return (tex);
}

SDL_Surface	**load_forward(char *dir)
{
	SDL_Surface **tex;
	char		*file_name;
	int			append_start;

	tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * E_DIR_SIZE);
	file_name = ft_strnew(ft_strlen(dir) + ft_strlen("forward/1.bmp"));
	ft_strncat(file_name, dir, ft_strlen(dir));
	ft_strncat(file_name, "forward/", ft_strlen("forward/"));
	append_start = ft_strlen(file_name);
	tex[0] = SDL_LoadBMP(append_in_place(file_name, "1.bmp", append_start));
	tex[1] = SDL_LoadBMP(append_in_place(file_name, "2.bmp", append_start));
	tex[2] = SDL_LoadBMP(append_in_place(file_name, "3.bmp", append_start));
	tex[3] = SDL_LoadBMP(append_in_place(file_name, "4.bmp", append_start));
	tex[4] = SDL_LoadBMP(append_in_place(file_name, "5.bmp", append_start));
	ft_strdel(&file_name);
	return (tex);
}

SDL_Surface	**load_forwardright(char *dir)
{
	SDL_Surface **tex;
	char		*file_name;
	int			append_start;

	tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * E_DIR_SIZE);
	file_name = ft_strnew(ft_strlen(dir) + ft_strlen("forwardright/1.bmp"));
	ft_strncat(file_name, dir, ft_strlen(dir));
	ft_strncat(file_name, "forwardright/", ft_strlen("forwardright/"));
	append_start = ft_strlen(file_name);
	tex[0] = SDL_LoadBMP(append_in_place(file_name, "1.bmp", append_start));
	tex[1] = SDL_LoadBMP(append_in_place(file_name, "2.bmp", append_start));
	tex[2] = SDL_LoadBMP(append_in_place(file_name, "3.bmp", append_start));
	tex[3] = SDL_LoadBMP(append_in_place(file_name, "4.bmp", append_start));
	tex[4] = SDL_LoadBMP(append_in_place(file_name, "5.bmp", append_start));
	ft_strdel(&file_name);
	return (tex);
}

SDL_Surface	**load_forwardleft(char *dir)
{
	SDL_Surface **tex;
	char		*file_name;
	int			append_start;

	tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * E_DIR_SIZE);
	file_name = ft_strnew(ft_strlen(dir) + ft_strlen("forwardleft/1.bmp"));
	ft_strncat(file_name, dir, ft_strlen(dir));
	ft_strncat(file_name, "forwardleft/", ft_strlen("forwardleft/"));
	append_start = ft_strlen(file_name);
	tex[0] = SDL_LoadBMP(append_in_place(file_name, "1.bmp", append_start));
	tex[1] = SDL_LoadBMP(append_in_place(file_name, "2.bmp", append_start));
	tex[2] = SDL_LoadBMP(append_in_place(file_name, "3.bmp", append_start));
	tex[3] = SDL_LoadBMP(append_in_place(file_name, "4.bmp", append_start));
	tex[4] = SDL_LoadBMP(append_in_place(file_name, "5.bmp", append_start));
	ft_strdel(&file_name);
	return (tex);
}
