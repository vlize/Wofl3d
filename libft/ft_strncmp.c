/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 15:11:03 by vlize             #+#    #+#             */
/*   Updated: 2014/11/15 12:37:08 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*t1;
	unsigned char	*t2;

	i = 0;
	t1 = (unsigned char *)s1;
	t2 = (unsigned char *)s2;
	if ((!s1 && !s2) || (n == 0))
		return (0);
	if (!s1 && s2)
		return (-(t2[0]));
	if (s1 && !s2)
		return (t1[0]);
	while ((t1[i] != '\0') && (t2[i] != '\0'))
	{
		if ((t1[i] != t2[i]) || ((i + 1) == n))
			return (t1[i] - t2[i]);
		i++;
	}
	return (t1[i] - t2[i]);
}
