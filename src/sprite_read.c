/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:01:22 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/13 14:49:27 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				valid_loc(t_sprite *sprites, int total_sprites, t_map *m)
{
	int i;
	int	y;
	int	x;

	i = 0;
	while (i < total_sprites)
	{
		y = (int)sprites[i].y;
		x = (int)sprites[i].x;
		if (x < 0 || x > m->width - 1 || y < 0 || y > m->height - 1)
			return (0);
		if (m->data[x][y] > 0)
			return (0);
		i++;
	}
	return (1);
}

static t_list	*get_data(int fd)
{
	int			expected;
	char		*line;
	t_list		*lst;
	t_list		*cur_line;
	int			ret;

	expected = 3;
	lst = NULL;
	while ((ret = get_next_line(fd, &line)))
	{
		if (ft_countwords(line, '\t') != expected)
			return (cleanup(lst, NULL, NULL));
		if ((cur_line = ft_lstnew(line, ft_strlen(line) + 1)) == NULL)
			return (cleanup(lst, NULL, NULL));
		ft_strdel(&line);
		ft_lstadd(&lst, cur_line);
	}
	if (ret == 1)
		return (cleanup(lst, NULL, NULL));
	ft_lstrev(&lst);
	return (lst);
}

t_sprite		*read_sprite_file(char *file, int *total_sprites, t_map *m)
{
	t_list		*lst;
	t_sprite	*sprites;
	int			fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if ((lst = get_data(fd)) == NULL)
		return (NULL);
	close(fd);
	*total_sprites = ft_lstcount(lst);
	sprites = load_sprites(lst, *total_sprites);
	if (sprites == NULL)
	{
		*total_sprites = 0;
		return (NULL);
	}
	if (!(valid_loc(sprites, *total_sprites, m)))
	{
		ft_putendl("Warning: Sprite locations invalid.");
		ft_putendl("Sprites won't be loaded.");
		*total_sprites = 0;
	}
	return (sprites);
}
