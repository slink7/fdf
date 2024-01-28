/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:10:02 by scambier          #+#    #+#             */
/*   Updated: 2024/01/28 13:20:03 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_H
# define PROJECT_H

# include "vec.h"

typedef struct s_camera
{
	float	yr;
	float	xr;
	float	zoom;
	int		scale;
	t_ivec2	pos;
	char	proj_type;
}	t_camera;

t_camera	*new_cam(int scale, float yr, float xr, float zoom);
void		project(t_camera *cam, t_ivec3 *in, t_ivec2 *out);

#endif