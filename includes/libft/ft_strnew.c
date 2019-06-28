/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 18:02:29 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/15 22:27:15 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*newstr;

	newstr = (char *)malloc((size + 1) * (sizeof(char)));
	if (newstr == NULL)
		return (NULL);
	ft_memset(newstr, '\0', size + 1);
	return (newstr);
}
