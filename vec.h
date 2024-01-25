/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 11:13:09 by scambier          #+#    #+#             */
/*   Updated: 2024/01/25 11:16:10 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

typedef struct s_ivec2
{
	int x;
	int y;
}	t_ivec2;

typedef struct s_ivec3
{
	int x;
	int y;
	int z;
}	t_ivec3;

t_ivec2	*new_ivec2(int x, int y);
void	free_ivec2(t_ivec2 **vec);
t_ivec3	*new_ivec3(int x, int y, int z);
void	free_ivec3(t_ivec3 **vec);

#endif