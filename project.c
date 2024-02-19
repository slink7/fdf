/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:10:39 by scambier          #+#    #+#             */
/*   Updated: 2024/02/19 11:52:51 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>

#include "project.h"

t_camera	*new_cam(int scale, float yr, float xr, float zoom)
{
	t_camera	*cam;

	cam = malloc(sizeof(t_camera));
	cam->scale = scale;
	cam->yr = yr;
	cam->xr = xr;
	cam->zoom = zoom;
	cam->pos.x = 0;
	cam->pos.y = 0;
	cam->proj_type = 'i';
	return (cam);
}

void	rot_y(t_fvec3 *out, t_fvec3 *in, float theta)
{
	float	cos;
	float	sin;

	cos = cosf(theta);
	sin = sinf(theta);
	out->x = in->x * cos - in->z * sin;
	out->y = in->y;
	out->z = in->x * sin + in->z * cos;
}

void	rot_x(t_fvec3 *out, t_fvec3 *in, float theta)
{
	float	cos;
	float	sin;

	cos = cosf(theta);
	sin = sinf(theta);
	out->x = in->x;
	out->y = in->y * cos - in->z * sin;
	out->z = in->y * sin + in->z * cos;
}

void	project(t_camera *cam, t_ivec3 *in, t_ivec2 *out)
{
	t_fvec3	roty;
	t_fvec3	rotx;
	t_fvec3	e;

	e.x = in->x;
	e.y = in->y;
	e.z = in->z;
	rot_x(&rotx, &e, cam->xr);
	rot_y(&roty, &rotx, cam->yr);
	if (cam->proj_type == 'o')
	{
		out->x = cam->scale * (roty.x - roty.z);
		out->y = cam->scale * (-roty.y + roty.z);
	}
	else
	{
		out->x = cam->zoom * (roty.x * cam->scale + roty.z * cam->scale);
		out->y = cam->zoom * ((-roty.x * cam->scale + roty.z * cam->scale)
				- (roty.y * cam->scale));
	}
}
