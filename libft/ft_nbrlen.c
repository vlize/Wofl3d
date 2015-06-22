/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/24 17:06:29 by vlize             #+#    #+#             */
/*   Updated: 2015/02/24 17:06:30 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(intmax_t n)
{
	size_t	l;

	l = 1;
	if (n < 0)
		l++;
	while ((n > 9) || (n < -9))
	{
		n /= 10;
		l++;
	}
	return (l);
}
