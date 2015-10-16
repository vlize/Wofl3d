/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlize <vlize@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/06/15 14:59:22 by vlize             #+#    #+#             */
/*   Updated: 2015/06/15 14:59:23 by vlize            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "wolf3d.h"

double	ft_put_operand(t_map *map, char *line, size_t *l)
{
	double	tmp;

	if ((line[*l] == 'b') && ((*l) += 1))
		return (BLOCK_SIZE);
	else if ((line[*l] == 'x') && ((*l) += 1))
		return (map->xtab * BLOCK_SIZE);
	else if ((line[*l] == 'y') && ((*l) += 1))
		return (map->ytab * BLOCK_SIZE);
	else if ((line[*l] == 'X') && ((*l) += 1))
		return ((map->xtab + 1) * BLOCK_SIZE);
	else if ((line[*l] == 'Y') && ((*l) += 1))
		return ((map->ytab + 1) * BLOCK_SIZE);
	tmp = 0;
	while (ft_isdigit(line[*l]))
	{
		tmp = (tmp * 10) + (line[*l] - 48);
		(*l)++;
	}
	return (tmp);
}

int		ft_put_data(t_map *map, char *line, size_t *l, double *data)
{
	*data = 0;
	while (ft_isdigit(line[*l]) || ft_is_op(line[*l]) || ft_is_val(line[*l]))
	{
		if (ft_isdigit(line[*l]) || ft_is_val(line[*l]))
			*data += ft_put_operand(map, line, l);
		else if ((line[*l] == '+') && ((*l) += 1))
			*data += ft_put_operand(map, line, l);
		else if ((line[*l] == '-') && ((*l) += 1))
			*data -= ft_put_operand(map, line, l);
		else if ((line[*l] == '*') && ((*l) += 1))
			*data *= ft_put_operand(map, line, l);
		else if ((line[*l] == '/') && ((*l) += 1))
			*data /= ft_put_operand(map, line, l);
	}
	if ((line[*l] == '\0') || (line[*l] == ';'))
		return (1);
	else if ((line[*l] == '\t') || (line[*l] == '|'))
		return (2);
	return (0);
}

void	ft_put_pln(t_env *env, size_t *l, t_pln *pln)
{
	int		i;

	if (!pln)
		exit(ft_perror("malloc()", env));
	pln->type = env->line[*l];
	pln->nbr = env->line[(*l += 1)] - 48;
	pln->hex = ft_put_color(pln->type, pln->nbr);
	(*l)++;
	while ((env->line[*l] != '\0') && (env->line[*l] != '\t'))
	{
		if ((env->line[*l] != '|') || (pln->pts > 3))
			exit(ft_put_error("ft_put_pln(): invalid map file.", env));
		i = -1;
		while ((i += 1) < 3)
		{
			(*l)++;
			if (!ft_put_data(env->map, env->line, l, &(pln->p[pln->pts][i])))
				exit(ft_put_error("ft_put_data(): invalid map file.", env));
		}
		pln->pts++;
	}
	if (pln->pts < 3)
		exit(ft_put_error("ft_put_pln(): invalid map file.", env));
}

void	ft_put_obj(t_env *env, size_t *l, t_obj *obj)
{
	if (!obj)
		exit(ft_perror("malloc()", env));
	obj->type = env->line[*l];
	obj->nbr = 48 + env->line[(*l += 1)];
	(*l)++;
	if (ft_isdigit(obj->nbr) == 0 || (env->line[*l] != '|'))
		exit(ft_put_error("ft_put_obj(): invalid map file.", env));
	while ((env->line[*l] != '\0') && (env->line[*l] != '\t'))
		(*l)++;
}
