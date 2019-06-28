/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qsort.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 19:18:06 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/29 20:15:20 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_swap_dub(double *a, double *b)
{
	double temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	ft_swap_int(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int		partition(int *order, double *distance, int first, int last)
{
	int		pindex;
	int		i;
	double	pivot;
	int		mid;

	mid = (first + last) / 2;
	pivot = distance[last];
	i = first;
	pindex = first;
	while (i < last)
	{
		if (distance[i] > pivot)
		{
			ft_swap_int(&order[i], &order[pindex]);
			ft_swap_dub(&distance[i], &distance[pindex]);
			pindex++;
		}
		i++;
	}
	ft_swap_int(&order[i], &order[pindex]);
	ft_swap_dub(&distance[i], &distance[pindex]);
	return (pindex);
}

void	sort_sprites(int *order, double *distance, int first, int last)
{
	int		pindex;

	if (first < last)
	{
		pindex = partition(order, distance, first, last);
		sort_sprites(order, distance, first, pindex - 1);
		sort_sprites(order, distance, pindex + 1, last);
	}
}
