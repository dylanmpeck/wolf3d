/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_loader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/06 19:21:07 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/13 14:46:43 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				get_enem_tex_num(char *arg, int *is_enemy)
{
	if (ft_strcmp(arg, "EnemyU") == 0)
	{
		*is_enemy = 1;
		return (EUP_TEX);
	}
	else if (ft_strcmp(arg, "EnemyL") == 0)
	{
		*is_enemy = 1;
		return (ELEFT_TEX);
	}
	else if (ft_strcmp(arg, "EnemyR") == 0)
	{
		*is_enemy = 1;
		return (ERIGHT_TEX);
	}
	else if (ft_strcmp(arg, "EnemyD") == 0)
	{
		*is_enemy = 1;
		return (EDOWN_TEX);
	}
	return (-1);
}

int				get_sprite_tex_num(char *arg)
{
	if (ft_strcmp(arg, "Light") == 0)
		return (LIG_TEX);
	else if (ft_strcmp(arg, "Barrel") == 0)
		return (BAR_TEX);
	else if (ft_strcmp(arg, "Pillar") == 0)
		return (PIL_TEX);
	else if (ft_strcmp(arg, "Key") == 0)
		return (KEY_TEX);
	else if (ft_strcmp(arg, "Table") == 0)
		return (TAB_TEX);
	else if (ft_strcmp(arg, "Well") == 0)
		return (WEL_TEX);
	else if (ft_strcmp(arg, "Vines") == 0)
		return (VIN_TEX);
	else if (ft_strcmp(arg, "Tree") == 0)
		return (TRE_TEX);
	else if (ft_strcmp(arg, "ETable") == 0)
		return (ETA_TEX);
	else if (ft_strcmp(arg, "Skel") == 0)
		return (SKE_TEX);
	else if (ft_strcmp(arg, "Kni") == 0)
		return (KNI_TEX);
	return (-1);
}

t_sprite		generate_sprite(char **split)
{
	t_sprite	sprite;
	int			tex_num;
	int			is_enemy;

	is_enemy = 0;
	tex_num = get_sprite_tex_num(split[0]);
	if (tex_num == -1)
		tex_num = get_enem_tex_num(split[0], &is_enemy);
	sprite = init_sprite(atof(split[1]), atof(split[2]), tex_num, is_enemy);
	if (tex_num == -1)
		sprite.x = -1.0;
	return (sprite);
}

t_sprite		*load_sprites(t_list *lst, int total_sprites)
{
	t_sprite	*sprites;
	t_list		*traverse;
	char		**split;
	int			i;

	sprites = (t_sprite *)malloc(sizeof(t_sprite) * total_sprites);
	i = 0;
	traverse = lst;
	while (i < total_sprites)
	{
		split = ft_strsplit((char *)traverse->content, '\t');
		sprites[i] = generate_sprite(split);
		if (sprites[i].x == -1.0f)
		{
			ft_putendl("Invalid sprite name.");
			free(sprites);
			return (cleanup(lst, NULL, NULL));
		}
		ft_splitdel(&split);
		traverse = traverse->next;
		i++;
	}
	cleanup(lst, NULL, NULL);
	return (sprites);
}
