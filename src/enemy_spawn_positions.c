/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_spawn_positions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:05:56 by omartela          #+#    #+#             */
/*   Updated: 2024/11/26 18:06:07 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../inc/cub3d.h"

int check_distance(t_table *table, int x, int y, int distance) 
{
    return abs(table->player_col - x) >= distance || abs(table->player_row - y) >= distance;
}

void init_enemies(t_table *table) 
{
    size_t	x;
	size_t	y;

	x = 0;
	y = 0;
	while (y < table->rows)
	{
		x = 0;
		while (x < table->columns)
		{
			if (table->map[y][x] == '0' && check_distance(table, x, y, 2))
			{
				printf("spawn position found \n");
				table->e_spawn_pos_x = x * T_SIZE + T_SIZE/2;
				table->e_spawn_pos_y = y * T_SIZE + T_SIZE/2;
				return ;
			}
			++x;
		}
		++y;
	}
	printf("No valid enemy spawn position found \n");
}
