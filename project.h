/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:10:02 by scambier          #+#    #+#             */
/*   Updated: 2024/01/25 16:33:30 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROJECT_H
# define PROJECT_H

# include "vec.h"

typedef struct s_camera
{
	float	yr;
	int		scale;
}	t_camera;

void	project(t_camera *cam, t_ivec3 *in, t_ivec2 *out);

#endif