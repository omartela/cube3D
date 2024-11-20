/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giuls <giuls@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 16:45:30 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/19 20:24:23 by giuls            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_background_not_needed(t_table *table)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (++y < T_SIZE * table->rows / 4)
	{
		x = -1;
		while (++x < T_SIZE * table->columns / 4)
			mlx_put_pixel(table->mlx_2D, x, y, 0xFF0000FF);
	}
}

void	draw_tile(t_table *table, int col, int row)
{
	int			x;
	int			y;
	int			i;
	int			j;
	uint32_t	color;

	x = col * T_SIZE / 4;
	y = row * T_SIZE / 4;
	if (table->map[row][col] == '1')
		color = 0xFFFFFFFF;
	else
		color = 0x000000FF;
	i = -1;
	while (++i < T_SIZE / 4 - 1)
	{
		j = -1;
		while (++j < T_SIZE / 4 - 1)
			mlx_put_pixel(table->mlx_2D, x + j, y + i, color);
	}
}

void	draw_player(t_table *table)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	y = table->player_y / 4 - 1;
	while (y++ < table->player_y / 8 + 1)
	{
		x = table->player_x / 4 - 1;
		while (x++ < table->player_x / 4 + 1)
			mlx_put_pixel(table->mlx_2D, x, y, 0xFFFF00FF);
	}
}

void	draw_minimap(t_table *table)
{
	size_t	row;
	size_t	col;

	draw_background_not_needed(table);
	row = 0;
	while (row < table->rows)
	{
		col = 0;
		while (col < table->columns)
		{
			draw_tile(table, col, row);
			++col;
		}
		++row;
	}
	draw_player(table);
}