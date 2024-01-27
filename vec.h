/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:13:09 by scambier          #+#    #+#             */
/*   Updated: 2024/01/27 21:07:14 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

typedef struct s_ivec2
{
	int	x;
	int	y;
}	t_ivec2;

typedef struct s_fvec3
{
	float	x;
	float	y;
	float	z;
}	t_fvec3;

typedef struct s_ivec3
{
	int	x;
	int	y;
	int	z;
}	t_ivec3;

t_ivec2	*new_ivec2(int x, int y);
t_ivec3	*new_ivec3(int x, int y, int z);
t_fvec3	*new_fvec3(float x, float y, float z);
void	set_vec(t_ivec3 *v, int x, int y, int z);
void	offset(t_ivec2 *v, int x, int y);

#endif