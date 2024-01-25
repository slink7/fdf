/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:10:39 by scambier          #+#    #+#             */
/*   Updated: 2024/01/25 16:39:08 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "project.h"

void	project(t_camera *cam, t_ivec3 *in, t_ivec2 *out)
{
	// p' = p - (n.(p - o)) x n
	out->x = in->x * cam->scale * cosf(cam->yr) + in->z * cam->scale * sinf(cam->yr);
	out->y = - in->x * cam->scale * cosf(cam->yr) + in->z * cam->scale * cosf(cam->yr) - in->y * cam->scale;
}