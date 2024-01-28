/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:16:16 by scambier          #+#    #+#             */
/*   Updated: 2024/01/28 17:53:03 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "vec.h"

t_ivec2	*new_ivec2(int x, int y)
{
	t_ivec2	*out;

	out = malloc(sizeof(t_ivec2));
	out->x = x;
	out->y = y;
	return (out);
}

t_ivec3	*new_ivec3(int x, int y, int z)
{
	t_ivec3	*out;

	out = malloc(sizeof(t_ivec3));
	out->x = x;
	out->y = y;
	out->z = z;
	return (out);
}

t_fvec3	*new_fvec3(float x, float y, float z)
{
	t_fvec3	*out;

	out = malloc(sizeof(t_fvec3));
	out->x = x;
	out->y = y;
	out->z = z;
	return (out);
}

void	sv(t_ivec3 *v, int x, int y, int z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

void	offset(t_ivec2 *v, int x, int y)
{
	v->x += x;
	v->y += y;
}
