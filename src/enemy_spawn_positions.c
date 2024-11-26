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

int	check_distance(t_table *table, int distance)
{
	if (abs(table->player_x - table->e_spawn_pos_x) >= distance)
		return (1);
	if (abs(table->player_y - table->e_spawn_pos_y) >= distance)
		return (1);
	return (0);
}

void	calc_enemy_spawn_pos(t_table *table, int distance)
{
	if (table->map[table->e_spawn_pos_y][table->e_spawn_pos_x + 1] == 0)
	{
		if (check_distance(table, distance))
			return ;
		else
			calc_enemy_spawn_pos(t_table *table, int distance)
	}
	if (table->map[table->e_spawn_pos_y][table->e_spawn_pos_x - 1] == 0)
	{
		if (check_distance(table, distance))
			return ;
		else
			calc_enemy_spawn_pos(t_table *table, int distance)

	}
	if (table->map[table->e_spawn_pos_y - 1][table->e_spawn_pos_x] == 0)
	{
		if (check_distance(table, distance))
			return ;
		else
			calc_enemy_spawn_pos(t_table *table, int distance)
	}
	if (table->map[table->e_spawn_pos_y + 1][table->e_spawn_pos_x] == 0)
	{
		if (check_distance(table, distance))
			return ;
		else
			calc_enemy_spawn_pos(t_table *table, int distance)
	}
}


void	init_calc_enemies(table *table)
{
	table->e_spawn_pos_x = table->player_x;
	table->e_spawn_pos_y = table->player_y;
	calc_enemy_spawn_pois(table, 5);
}
