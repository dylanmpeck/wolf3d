/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_lists.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 19:48:20 by dpeck             #+#    #+#             */
/*   Updated: 2019/04/01 19:49:23 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	clean_enemy_list(t_linked **enemies)
{
	t_linked *trav;
	t_linked *delete;

	trav = (*enemies)->next;
	while (trav)
	{
		delete = trav;
		trav = trav->next;
		free(delete);
		delete = NULL;
	}
}

void	clean_door_list(t_door_list **doors)
{
	t_door_list *trav;
	t_door_list *delete;

	trav = *doors;
	while (trav)
	{
		delete = trav;
		trav = trav->next;
		free(delete);
		delete = NULL;
	}
}
