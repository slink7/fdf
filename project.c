/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:10:39 by scambier          #+#    #+#             */
/*   Updated: 2024/01/25 17:38:01 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

#include "project.h"

void	project(t_camera *cam, t_ivec3 *in, t_ivec2 *out)
{
	out->x = cam->zoom * (in->x * cam->scale * cosf(cam->yr) + in->z * cam->scale * sinf(cam->yr));
	out->y = cam->zoom * (cam->xr * (-in->x * cam->scale * sinf(cam->yr) + in->z * cam->scale * cosf(cam->yr)) - (1.0f - cam->xr) * (in->y * cam->scale));
}