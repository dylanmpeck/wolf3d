/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   append_in_place.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpeck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 22:02:52 by dpeck             #+#    #+#             */
/*   Updated: 2019/03/28 19:21:22 by dpeck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*append_in_place(char *src, char *dst, int begin)
{
	int i;

	i = 0;
	while (dst[i])
	{
		src[begin] = dst[i];
		begin++;
		i++;
	}
	src[begin] = '\0';
	return (src);
}
