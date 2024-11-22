/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:15:57 by omartela          #+#    #+#             */
/*   Updated: 2024/11/20 15:16:01 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int animate_attack(t_table *table)
{
	int	i;

	i = 0;
	
	if (table->frame_counter)
	{
		while (i < 30)
		{
            table->p_img[i]->instances[0].enabled = false; //Disable all animation frames first
			++i;
		}

		if (table->p_anim_index == 29)
		{
			table->p_img[0]->instances[0].enabled = true;
			table->is_attacking = 0;
			table->p_anim_index = 0;
		}
		else
		{
			table->p_img[table->p_anim_index]->instances[0].enabled = true;
			table->p_anim_index += 1;
		}
	}
	return (0);
}

void	set_image_instance_pos(mlx_instance_t *instance, int x, int y)
{
	instance->x = x;
	instance->y = y;
}

int	animate_enemy(t_table *table)
{
	int	i;

	i = 0;
	if (table->frame_counter % 5 == 0)
	{
		while (i < 5)
		{
            table->e_img[i]->instances[0].enabled = false; //Disable all animation frames first
			++i;
		}
		if (table->e_anim_index == 4)
		{
			table->p_img[0]->instances[0].enabled = true;
			table->is_attacking = 0;
			table->e_anim_index = 0;
		}
		else
		{
			table->e_img[table->e_anim_index]->instances[0].enabled = true;
			table->e_anim_index += 1;
		}
	}
	return (0);
	
}

int	insert_enemy_images(t_table *table)
{
	int	i;
	int base_x;
	int	base_y;
	/// set position towards to player from the enemy position
	i = 4;
	base_x = table->width / 2;// - 130;
	base_y = table->height / 2;// - 130;
	while (i >= 0)
	{
		mlx_resize_image(table->e_img[i], 100 + (i * 20), 100 + (i * 20));
		mlx_image_to_window(table->mlx_start, table->e_img[i], 0, 0);
		if (i != 0)
			table->e_img[i]->instances[0].enabled = false;
		set_image_instance_pos(&table->e_img[i]->instances[0], base_x, base_y - (i * 2));
		--i;
	}
	return (0);
}

int	insert_fireball(t_table *table)
{
	int	i;
	int base_x;
	int base_y;

	base_x = table->width / 2 - 150;
	base_y = table->height - 250;

	i = 0;
	while (i < 30)
	{
		mlx_resize_image(table->p_img[i], 300 - (7 * table->p_anim_index), 300 - (7 * table->p_anim_index));
		mlx_image_to_window(table->mlx_start, table->p_img[i], base_x, base_y);
		//mlx_set_instance_depth(&table->p_img[i]->instances[0], 1);
		if (i > 0)
		{
			set_image_instance_pos(&table->p_img[i]->instances[0], base_x, base_y - (i * 4));
			table->p_img[i]->instances[0].enabled = false;
		}
		++i;
	}
	return (0);
}

int	insert_player_texture(t_table *table)
{
	mlx_resize_image(table->left_hand, 150, 150);
	mlx_resize_image(table->right_hand, 150, 150);
	mlx_image_to_window(table->mlx_start, table->left_hand, table->width / 2 - 200, table->height - 150);
	mlx_image_to_window(table->mlx_start , table->right_hand, table->width / 2 + 50, table->height - 150);
	/* mlx_resize_image(table->p_img[table->p_anim_index], 300, 300);
	index = mlx_image_to_window(table->mlx_start, table->p_img[0], table->width / 2 - 150, table->height - 300);
	mlx_set_instance_depth(&table->p_img[table->p_anim_index]->instances[index], 4); */
	insert_fireball(table);
	insert_enemy_images(table);
	return (0);
}