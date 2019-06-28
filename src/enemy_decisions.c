/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_decisions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 20:23:42 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/31 21:05:23 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	set_range(t_decisions *decisions, int move, int shoot)
{
	decisions->move.low = 0;
	decisions->move.high = move;
	decisions->shoot.low = move + 1;
	decisions->shoot.high = shoot;
	decisions->idle.low = shoot + 1;
	decisions->idle.high = 99;
}

void	set_decision_ranges(double length, t_linked *enemy)
{
	if (length <= 4.0f)
		set_range(&enemy->sprite->decisions, 19, 79);
	else if (length > 4.0f && length <= 9.0f)
	{
		if (enemy->sprite->zombie)
			set_range(&enemy->sprite->decisions, 69, 69);
		else
			set_range(&enemy->sprite->decisions, 49, 59);
	}
	else
	{
		if (enemy->sprite->zombie)
			set_range(&enemy->sprite->decisions, 79, 79);
		else
			set_range(&enemy->sprite->decisions, 59, 69);
	}
}

void	make_decision(t_linked *enemy)
{
	int		choice;
	t_range	move;
	t_range	shoot;
	t_range	idle;

	choice = rand() & 100;
	move = enemy->sprite->decisions.move;
	shoot = enemy->sprite->decisions.shoot;
	idle = enemy->sprite->decisions.idle;
	if (choice >= move.low && choice <= move.high)
	{
		enemy->sprite->moving = 1;
		enemy->sprite->shooting = 0;
	}
	else if (choice >= shoot.low && choice <= shoot.high)
	{
		enemy->sprite->moving = 0;
		enemy->sprite->shooting = 1;
	}
	else
	{
		enemy->sprite->moving = 0;
		enemy->sprite->shooting = 0;
		enemy->sprite->prev_time = enemy->sprite->time + 800;
	}
}
