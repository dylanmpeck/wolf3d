/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_load.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 18:39:11 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/02 18:38:31 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

SDL_Surface	*convert_bitmap(SDL_Surface *image)
{
	SDL_Surface *converted;
	int			i;
	Uint32		*pixels;
	t_convert	conv;

	converted = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0, 0, 0, 0);
	pixels = (Uint32 *)image->pixels;
	conv.pixels = (Uint32 *)converted->pixels;
	i = 0;
	while (i < converted->w * converted->h)
	{
		conv.sa = pixels[0];
		conv.sb = pixels[1];
		conv.sc = pixels[2];
		conv.pixels[i + 0] = (Uint32)conv.sa;
		conv.pixels[i + 1] = (Uint32)((conv.sa >> 24) | (conv.sb << 8));
		conv.pixels[i + 2] = (Uint32)((conv.sb >> 16) | (conv.sb << 16));
		conv.pixels[i + 3] = (Uint32)(conv.sc >> 8);
		pixels += 3;
		i += 4;
	}
	SDL_FreeSurface(image);
	return (converted);
}

void		generate_walls(SDL_Surface **texture)
{
	texture[0] = convert_bitmap(SDL_LoadBMP("textures/wall/ruinnorth.bmp"));
	texture[1] = convert_bitmap(SDL_LoadBMP("textures/wall/ruinsouth.bmp"));
	texture[2] = convert_bitmap(SDL_LoadBMP("textures/wall/ruineast.bmp"));
	texture[3] = convert_bitmap(SDL_LoadBMP("textures/wall/ruinwest.bmp"));
	texture[4] = convert_bitmap(SDL_LoadBMP("textures/wall/junglenorth.bmp"));
	texture[5] = convert_bitmap(SDL_LoadBMP("textures/wall/junglesouth.bmp"));
	texture[6] = convert_bitmap(SDL_LoadBMP("textures/wall/jungleeast.bmp"));
	texture[7] = convert_bitmap(SDL_LoadBMP("textures/wall/junglewest.bmp"));
	texture[8] = convert_bitmap(SDL_LoadBMP("textures/wall/icenorth.bmp"));
	texture[9] = convert_bitmap(SDL_LoadBMP("textures/wall/icesouth.bmp"));
	texture[10] = convert_bitmap(SDL_LoadBMP("textures/wall/iceeast.bmp"));
	texture[11] = convert_bitmap(SDL_LoadBMP("textures/wall/icewest.bmp"));
	texture[12] = convert_bitmap(SDL_LoadBMP("textures/wall/tortnorth.bmp"));
	texture[13] = convert_bitmap(SDL_LoadBMP("textures/wall/tortsouth.bmp"));
	texture[14] = convert_bitmap(SDL_LoadBMP("textures/wall/torteast.bmp"));
	texture[15] = convert_bitmap(SDL_LoadBMP("textures/wall/tortwest.bmp"));
	texture[34] = convert_bitmap(SDL_LoadBMP("textures/greystone.bmp"));
	texture[35] = convert_bitmap(SDL_LoadBMP("textures/wood.bmp"));
}

void		generate_sprites(SDL_Surface **texture)
{
	texture[16] = convert_bitmap(SDL_LoadBMP("textures/barrel.bmp"));
	texture[17] = convert_bitmap(SDL_LoadBMP("textures/pillar.bmp"));
	texture[18] = convert_bitmap(SDL_LoadBMP("textures/greenlight.bmp"));
	texture[19] = SDL_LoadBMP("textures/key.bmp");
	texture[20] = SDL_LoadBMP("textures/pistol/pistol1.bmp");
	texture[21] = SDL_LoadBMP("textures/pistol/pistol2.bmp");
	texture[22] = SDL_LoadBMP("textures/pistol/pistol3.bmp");
	texture[23] = SDL_LoadBMP("textures/pistol/pistol4.bmp");
	texture[24] = SDL_LoadBMP("textures/pistol/pistol5.bmp");
	texture[25] = SDL_LoadBMP("textures/door.bmp");
	texture[26] = SDL_LoadBMP("textures/keydoor.bmp");
	texture[27] = SDL_LoadBMP("textures/skeleton.bmp");
	texture[28] = SDL_LoadBMP("textures/well.bmp");
	texture[29] = SDL_LoadBMP("textures/table.bmp");
	texture[30] = SDL_LoadBMP("textures/vines.bmp");
	texture[31] = SDL_LoadBMP("textures/tree.bmp");
	texture[32] = SDL_LoadBMP("textures/emptytable.bmp");
	texture[33] = SDL_LoadBMP("textures/knight.bmp");
}

SDL_Surface	**generate_sky(void)
{
	SDL_Surface **skybox;

	skybox = (SDL_Surface **)malloc(sizeof(SDL_Surface *) * 4);
	skybox[0] = convert_bitmap(SDL_LoadBMP("skybox/1.bmp"));
	skybox[1] = convert_bitmap(SDL_LoadBMP("skybox/2.bmp"));
	skybox[2] = convert_bitmap(SDL_LoadBMP("skybox/3.bmp"));
	skybox[3] = convert_bitmap(SDL_LoadBMP("skybox/4.bmp"));
	return (skybox);
}
