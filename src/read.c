/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 19:25:59 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/12 13:48:41 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void			*cleanup(t_list *lst, t_map *m, char **split)
{
	t_list	*temp;
	int		i;

	i = 0;
	while (lst)
	{
		temp = lst->next;
		ft_memdel(&lst->content);
		ft_memdel((void **)&lst);
		lst = temp;
	}
	if (m)
		free_map(&m);
	if (split)
		ft_splitdel(&split);
	return (NULL);
}

t_map			*store_map_data(t_map *m, t_list *list)
{
	char	**split;
	t_list	*traverse;
	int		y;
	int		x;

	y = 0;
	traverse = list;
	while (y < m->height)
	{
		split = ft_strsplit((char *)traverse->content, '\t');
		x = 0;
		while (x < m->width)
		{
			if (!(is_number(split[x])))
				return (cleanup(NULL, m, split));
			m->data[y][x] = ft_atoi(split[x]);
			x++;
		}
		traverse = traverse->next;
		ft_splitdel(&split);
		y++;
	}
	cleanup(list, NULL, NULL);
	return (m);
}

static t_list	*get_data(int fd)
{
	static int	expected = -1;
	char		*line;
	t_list		*lst;
	t_list		*cur_line;
	int			ret;

	lst = NULL;
	while ((ret = get_next_line(fd, &line)))
	{
		if (expected == -1)
			expected = ft_countwords(line, '\t');
		if (expected == 0 || ft_countwords(line, '\t') != expected)
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

t_map			*create_map(int width, int height)
{
	t_map	*map;
	int		i;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->width = width;
	map->height = height;
	map->data = (int **)malloc(sizeof(int *) * height);
	if (map->data == NULL)
	{
		ft_memdel((void **)&map);
		return (NULL);
	}
	i = 0;
	while (i < height)
	{
		map->data[i] = (int *)malloc(sizeof(int) * width);
		i++;
	}
	return (map);
}

t_map			*read_map(char *file)
{
	t_list	*lst;
	t_map	*map;
	int		fd;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	if ((lst = get_data(fd)) == NULL)
		return (NULL);
	close(fd);
	map =
		create_map(ft_countwords((char *)lst->content, '\t'), ft_lstcount(lst));
	if (map == NULL)
		return (cleanup(lst, NULL, NULL));
	if ((store_map_data(map, lst)) == NULL)
		return (NULL);
	if (!(validate_map_texes(map)))
		return (cleanup(NULL, map, NULL));
	if (only_walls(map))
		return (map_error("Only Walls."));
	if (!(is_enclosed(map)))
		return (map_error("Map is not enclosed."));
	return (map);
}
