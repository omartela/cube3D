/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:20:04 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/14 15:22:38 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	init_data(t_table *table)
{
	ft_memset(table, 0, sizeof(t_table));
	table->width = 2048;
	table->height = 1024;
	table->player_angle = 270; // to ghange according NSEW where the player is looking on the map
	table->player_delta_x = cos((float)table->player_angle / 180 * PI);
	table->player_delta_y = sin((float)table->player_angle / 180 * PI);
	table->player_delta_x_ad = cos((float)(table->player_angle + 90) / 180 * PI);
	table->player_delta_y_ad = sin((float)(table->player_angle + 90) / 180 * PI);
	table->e_spawn_pos_x = 0;
	table->e_spawn_pos_y = 0;

}
