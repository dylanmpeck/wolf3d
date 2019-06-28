/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/24 17:36:36 by dpeck             #+#    #+#             */
/*   Updated: 2018/09/24 17:39:56 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strcjoin(const char *s1, const char *s2, char c)
{
	char	*newstr;
	int		i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	newstr = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (newstr == NULL)
		return (NULL);
	ft_strcpy(newstr, s1);
	while (newstr[i])
		i++;
	newstr[i] = c;
	ft_strcat(newstr, s2);
	return (newstr);
}
