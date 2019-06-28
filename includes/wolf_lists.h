/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf_lists.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/28 19:29:16 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/28 21:00:02 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_LISTS_H
# define WOLF_LISTS_H
# include "wolf_structs.h"

typedef struct s_sprite	t_sprite;
typedef struct s_door	t_door;

typedef struct			s_linked
{
	t_sprite			*sprite;
	struct s_linked		*next;
}						t_linked;

typedef struct			s_door_list
{
	t_door				*door;
	struct s_door_list	*next;
}						t_door_list;
#endif
