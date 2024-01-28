/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scambier <scambier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 16:22:16 by scambier          #+#    #+#             */
/*   Updated: 2024/01/28 16:53:19 by scambier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOOKS_H
# define HOOKS_H

# include "t_structs.h"

int	key_hook(int keycode, t_all *all);
int	close_hook(t_all *all);
int	expose_hook(t_all *all);

#endif