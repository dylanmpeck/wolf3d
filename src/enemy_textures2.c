/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_textures2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 22:06:43 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/02 18:08:23 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Surface	**load_left(char *dir)
{
	SDL_Surface **tex;
	char		*file_name;
	int			append_start;

	tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * E_DIR_SIZE);
	file_name = ft_strnew(ft_strlen(dir) + ft_strlen("left/1.bmp"));
	ft_strncat(file_name, dir, ft_strlen(dir));
	ft_strncat(file_name, "left/", ft_strlen("left/"));
	append_start = ft_strlen(file_name);
	tex[0] = SDL_LoadBMP(append_in_place(file_name, "1.bmp", append_start));
	tex[1] = SDL_LoadBMP(append_in_place(file_name, "2.bmp", append_start));
	tex[2] = SDL_LoadBMP(append_in_place(file_name, "3.bmp", append_start));
	tex[3] = SDL_LoadBMP(append_in_place(file_name, "4.bmp", append_start));
	tex[4] = SDL_LoadBMP(append_in_place(file_name, "5.bmp", append_start));
	ft_strdel(&file_name);
	return (tex);
}

SDL_Surface	**load_right(char *dir)
{
	SDL_Surface **tex;
	char		*file_name;
	int			append_start;

	tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * E_DIR_SIZE);
	file_name = ft_strnew(ft_strlen(dir) + ft_strlen("right/1.bmp"));
	ft_strncat(file_name, dir, ft_strlen(dir));
	ft_strncat(file_name, "right/", ft_strlen("right/"));
	append_start = ft_strlen(file_name);
	tex[0] = SDL_LoadBMP(append_in_place(file_name, "1.bmp", append_start));
	tex[1] = SDL_LoadBMP(append_in_place(file_name, "2.bmp", append_start));
	tex[2] = SDL_LoadBMP(append_in_place(file_name, "3.bmp", append_start));
	tex[3] = SDL_LoadBMP(append_in_place(file_name, "4.bmp", append_start));
	tex[4] = SDL_LoadBMP(append_in_place(file_name, "5.bmp", append_start));
	ft_strdel(&file_name);
	return (tex);
}

SDL_Surface	**load_backleft(char *dir)
{
	SDL_Surface **tex;
	char		*file_name;
	int			append_start;

	tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * E_DIR_SIZE);
	file_name = ft_strnew(ft_strlen(dir) + ft_strlen("backleft/1.bmp"));
	ft_strncat(file_name, dir, ft_strlen(dir));
	ft_strncat(file_name, "backleft/", ft_strlen("backleft/"));
	append_start = ft_strlen(file_name);
	tex[0] = SDL_LoadBMP(append_in_place(file_name, "1.bmp", append_start));
	tex[1] = SDL_LoadBMP(append_in_place(file_name, "2.bmp", append_start));
	tex[2] = SDL_LoadBMP(append_in_place(file_name, "3.bmp", append_start));
	tex[3] = SDL_LoadBMP(append_in_place(file_name, "4.bmp", append_start));
	tex[4] = SDL_LoadBMP(append_in_place(file_name, "5.bmp", append_start));
	ft_strdel(&file_name);
	return (tex);
}

SDL_Surface	**load_backright(char *dir)
{
	SDL_Surface **tex;
	char		*file_name;
	int			append_start;

	tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * E_DIR_SIZE);
	file_name = ft_strnew(ft_strlen(dir) + ft_strlen("backright/1.bmp"));
	ft_strncat(file_name, dir, ft_strlen(dir));
	ft_strncat(file_name, "backright/", ft_strlen("backright/"));
	append_start = ft_strlen(file_name);
	tex[0] = SDL_LoadBMP(append_in_place(file_name, "1.bmp", append_start));
	tex[1] = SDL_LoadBMP(append_in_place(file_name, "2.bmp", append_start));
	tex[2] = SDL_LoadBMP(append_in_place(file_name, "3.bmp", append_start));
	tex[3] = SDL_LoadBMP(append_in_place(file_name, "4.bmp", append_start));
	tex[4] = SDL_LoadBMP(append_in_place(file_name, "5.bmp", append_start));
	ft_strdel(&file_name);
	return (tex);
}

SDL_Surface	**load_back(char *dir)
{
	SDL_Surface **tex;
	char		*file_name;
	int			append_start;

	tex = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * E_DIR_SIZE);
	file_name = ft_strnew(ft_strlen(dir) + ft_strlen("back/1.bmp"));
	ft_strncat(file_name, dir, ft_strlen(dir));
	ft_strncat(file_name, "back/", ft_strlen("back/"));
	append_start = ft_strlen(file_name);
	tex[0] = SDL_LoadBMP(append_in_place(file_name, "1.bmp", append_start));
	tex[1] = SDL_LoadBMP(append_in_place(file_name, "2.bmp", append_start));
	tex[2] = SDL_LoadBMP(append_in_place(file_name, "3.bmp", append_start));
	tex[3] = SDL_LoadBMP(append_in_place(file_name, "4.bmp", append_start));
	tex[4] = SDL_LoadBMP(append_in_place(file_name, "5.bmp", append_start));
	ft_strdel(&file_name);
	return (tex);
}
