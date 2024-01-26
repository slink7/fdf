/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:16:16 by scambier          #+#    #+#             */
/*   Updated: 2024/01/26 19:38:55 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_ivec2	*new_ivec2(int x, int y)
{
	t_ivec2	*out;

	out->x = x;
	out->y = y;
	return (out);
}

t_ivec3	*new_ivec3(int x, int y, int z)
{
	t_ivec3	*out;

	out->x = x;
	out->y = y;
	out->z = z;
	return (out);
}

void	set_vec(t_ivec3 *v, int x, int y, int z)
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
