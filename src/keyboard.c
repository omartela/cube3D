/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 10:38:34 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/19 17:09:32 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int circle_rectangle_collision(int circle_x, int circle_y, int radius, int rect_x, int rect_y, int rect_size)
{
	// Find the closest point on the rectangle to the circle
	int closest_x = fmax(rect_x, fmin(circle_x, rect_x + rect_size));
	int closest_y = fmax(rect_y, fmin(circle_y, rect_y + rect_size));

	// Calculate distance from circle's center to closest point
	int dx = circle_x - closest_x;
	int dy = circle_y - closest_y;

	// Check if the distance is less than the circle's radius
	return (dx * dx + dy * dy) < (radius * radius);
}


int	wall_collision_w_circular_bumper(t_table *table, int new_x, int new_y)
{
	int	radius;
	//int new_x;
	//int	new_y;
	int	mpx;
	int	mpy;
	int x;
	int y;
	int check_tile_x;
	int	check_tile_y;
	int wall_x;
	int	wall_y;
	//int	offset;

	radius = 20;// + T_SIZE / 2;
	//new_x = table->player_x + table->player_delta_x * 5;
	//new_y = table->player_y + table->player_delta_y * 5;
	mpx = table->player_x / T_SIZE;
	mpy = table->player_y / T_SIZE;
	y = -1;
	while (y <= 1)
	{
		x = -1;
		while (x <= 1)
		{
			check_tile_x = mpx + x;
			check_tile_y = mpy + y;
			if (check_tile_x >= 0 && check_tile_x < (int)table->columns && check_tile_y >= 0 && check_tile_y < (int)table->rows)
			{
				if (table->map[check_tile_y][check_tile_x] == '1')
				{
					//printf("tile x = %d	tile y = %d\n", check_tile_x, check_tile_y);
					wall_x = check_tile_x * T_SIZE;// + T_SIZE / 2;
					wall_y = check_tile_y * T_SIZE;// + T_SIZE / 2;
					//offset = (new_x - wall_x) * (new_x - wall_x) + (new_y - wall_y) * (new_y - wall_y);
					//printf("offset = %d\n", offset);
					//printf("r2 = %d\n", radius * radius);
					//if (offset < radius * radius)
					//	return (1);
					if (circle_rectangle_collision(new_x, new_y, radius, wall_x, wall_y, T_SIZE))
						return 1;
				}
			}
			x++;
		}
		y++;
	}
	return (0);
}

void	ft_enemy(void *param)
{
	t_table	*table;

	table = (t_table *)param;
	(void)table;
	//animate_enemy(table);
}

void update_enemy_pos_straight(t_table *table)
{
    // Vihollisen sijainti kartalla
    float enemy_x = 3.0; // Kartan koordinaatit
    float enemy_y = 1.0;

    // Kameran sijainti kartalla
    float camera_map_x = table->player_x / T_SIZE;
    float camera_map_y = table->player_y / T_SIZE;
	
	printf("table->player_x %f and table->player_y %f \n", table->player_x, table->player_y);

    // Suhteellinen sijainti kameraan nähden
    float relative_x = enemy_x - camera_map_x;
    float relative_y = camera_map_y - enemy_y;
	printf("Camera position: camera_map_x = %f, camera_map_y = %f\n", camera_map_x, camera_map_y);
	printf("Enemy position: enemy_x = %f, enemy_y = %f\n", enemy_x, enemy_y);
	printf("Relative position: relative_x = %f, relative_y = %f\n", relative_x, relative_y);


    // Varmista, ettei vihollinen ole kameran takana
    if (relative_y <= 0.1f) {
        printf("Enemy behind camera or too close.\n");
        return;
    }

    // Ruudun koordinaatit
    int screen_x = (int)((relative_x / relative_y) * (table->width / 2)) + (table->width / 2);
    int screen_y = (table->height / 2); // Kiinteä y-taso (ei korkeuseroja)

	printf("Relative: x = %f, y = %f\n", relative_x, relative_y);
	printf("Screen: x = %d\n", screen_x);


    // Tarkista, onko vihollinen ruudulla
    if (screen_x < 0 || screen_x >= table->width) {
        printf("Enemy out of view.\n");
    }

    // Päivitä vihollisen sprite
    int i = 4;
    while (i >= 0) {
        set_image_instance_pos(&table->e_img[i]->instances[0], screen_x, screen_y);
        --i;
    }
}


 void update_enemy_pos(t_table *table)
{
    // Vihollisen sijainti kartalla
    float enemy_x = 3.0; // Kartan koordinaatit
    float enemy_y = 1.0;

    // Pelaajan sijainti kartalla
    float player_map_x = table->player_x / T_SIZE;
    float player_map_y = table->player_y / T_SIZE;

    // Suhteellinen sijainti pelaajaan nähden
    float relative_x = enemy_x - player_map_x;
    float relative_y = enemy_y - player_map_y;

    // Kulma viholliseen
    float angle_to_enemy = atan2(relative_y, relative_x);

    // Suhteellinen kulma pelaajaan nähden
    float player_angle = deg_to_rad(table->player_angle); // Muunna asteet radiaaneiksi
    float relative_angle = angle_to_enemy - player_angle;

    // Kulman normalisointi -pi ja pi välillä
    if (relative_angle > PI) relative_angle -= 2 * PI;
    if (relative_angle < -PI) relative_angle += 2 * PI;

    // Vihollisen ruutukoordinaatti (x)
    float fov = deg_to_rad(60); // Näkökenttä (60 astetta radiaaneina)
    int screen_x = (int)((relative_angle / fov) * (table->width / 2)) + (table->width / 2);

    // Tarkista, onko vihollinen näkyvissä
    if (screen_x < 0 || screen_x >= table->width) {
        printf("Enemy is out of view.\n");
    }

    // Päivitä vihollisen sprite
    int i = 4;
    while (i >= 0) {
        set_image_instance_pos(&table->e_img[i]->instances[0], screen_x, table->height / 2);
        --i;
    }
}


void ft_hook(void* param)
{
	t_table	*table;
	//int	avoid_wall_collision;
	int		new_x;
	int		new_y;

	table = (t_table *)param;

	table->frame_counter += 1;
	if (table->is_attacking)
		animate_attack(table);
	if (mlx_is_key_down(table->mlx_start, MLX_KEY_W))
	{
		new_x = table->player_x + table->player_delta_x * 5;
		new_y = table->player_y + table->player_delta_y * 5;
		if (!wall_collision_w_circular_bumper(table, new_x, table->player_y))
		//if (table->map[mpy][mpxcw] != '1')
			table->player_x = new_x;
		//if (table->map[mpycw][mpx] != '1')
		if (!wall_collision_w_circular_bumper(table, table->player_x, new_y))
			table->player_y = new_y;
	}
	if (mlx_is_key_down(table->mlx_start, MLX_KEY_S))
	{
		new_x = table->player_x - table->player_delta_x * 5;
		new_y = table->player_y - table->player_delta_y * 5;
		//if (table->map[mpy][mpxcs] != '1')
		if (!wall_collision_w_circular_bumper(table, new_x, table->player_y))
			table->player_x = new_x;
		//if (table->map[mpycs][mpx] != '1')
		if (!wall_collision_w_circular_bumper(table, table->player_x, new_y))
			table->player_y = new_y;
	}
	if (mlx_is_key_down(table->mlx_start, MLX_KEY_D))
	{
		new_x = table->player_x + table->player_delta_x_ad * 5;
		new_y = table->player_y + table->player_delta_y_ad * 5;
		/* int i = 4;
		while (i >= 0)
		{
			set_image_instance_pos(&table->e_img[i]->instances[0], table->e_img[i]->instances[0].x -= 55, table->e_img[i]->instances[0].y);
			--i;
		}	 */
		update_enemy_pos_straight(table);
		//if (table->map[mpy][mpxcd] != '1')
		if (!wall_collision_w_circular_bumper(table, new_x, table->player_y))
			table->player_x = new_x;
		//if (table->map[mpycd][mpx] != '1')
		if (!wall_collision_w_circular_bumper(table, table->player_x, new_y))
			table->player_y  = new_y;
	}
	if (mlx_is_key_down(table->mlx_start, MLX_KEY_A))
	{
		new_x = table->player_x - table->player_delta_x_ad * 5;
		new_y = table->player_y - table->player_delta_y_ad * 5;
		//if (table->map[mpy][mpxca] != '1')
		/* int i = 4;
		while (i >= 0)
		{
			set_image_instance_pos(&table->e_img[i]->instances[0], table->e_img[i]->instances[0].x += 55, table->e_img[i]->instances[0].y);
			--i;
		}	 */
		update_enemy_pos_straight(table);
		if (!wall_collision_w_circular_bumper(table, new_x, table->player_y))
			table->player_x = new_x;
		//if (table->map[mpyca][mpx] != '1')
		if (!wall_collision_w_circular_bumper(table, table->player_x, new_y))
			table->player_y = new_y;
	}
	if (mlx_is_key_down(table->mlx_start, MLX_KEY_LEFT))
	{
		table->player_angle -= 10;
		if (table->player_angle < 0)
			table->player_angle += 360;
		table->player_delta_x = cos((float)table->player_angle / 180 * PI);
		table->player_delta_y = sin((float)table->player_angle / 180 * PI);
		table->player_delta_x_ad = cos((float)(table->player_angle + 90) / 180 * PI);
		table->player_delta_y_ad = sin((float)(table->player_angle + 90) / 180 * PI);
		/* int	i;
		i = 4;
		while (i >= 0)
		{
			set_image_instance_pos(&table->e_img[i]->instances[0], table->e_img[i]->instances[0].x += 55, table->e_img[i]->instances[0].y);
			--i;
		} */
		update_enemy_pos(table);
	}
	if (mlx_is_key_down(table->mlx_start, MLX_KEY_RIGHT))
	{
		table->player_angle += 10;
		if (table->player_angle > 359)
			table->player_angle -= 360;
		table->player_delta_x = cos((float)table->player_angle / 180 * PI);
		table->player_delta_y = sin((float)table->player_angle / 180 * PI);
		table->player_delta_x_ad = cos((float)(table->player_angle + 90) / 180 * PI);
		table->player_delta_y_ad = sin((float)(table->player_angle + 90) / 180 * PI);
		/* int	i;
		i = 4;
		while (i >= 0)
		{
			set_image_instance_pos(&table->e_img[i]->instances[0], table->e_img[i]->instances[0].x -= 55, table->e_img[i]->instances[0].y);
			--i;
		} */
		update_enemy_pos(table);
	}
	animate_enemy(table);
	draw_minimap(table);
	draw_raycasting(table);
}

void	ft_keyboard(mlx_key_data_t keydata, void *param)
{
	t_table	*table;
	//int	avoid_wall_collision;

	table = (t_table *)param;
	
	// ---offset wall collision---
	/*avoid_wall_collision = 20;
	int mpy = table->player_y / T_SIZE;
	int mpx = table->player_x / T_SIZE;
	int mpycw, mpxcw;
	if (table->player_angle >= 0 && table->player_angle < 180)
		mpycw = (table->player_y + avoid_wall_collision) / T_SIZE;
	else
		mpycw = (table->player_y - avoid_wall_collision) / T_SIZE;
	if (table->player_angle >= 270 || table->player_angle < 90)
		mpxcw = (table->player_x + avoid_wall_collision) / T_SIZE;
	else
		mpxcw = (table->player_x - avoid_wall_collision) / T_SIZE;
	//printf("mpy = %d\n", mpy);
	//printf("mpx = %d\n", mpx);
	//printf("player x = %f\n", table->player_x);
	//printf("mpyc = %d\n", mpycw);
	//printf("mpxc = %d\n", mpxcw);
	//printf("table->map[%d][%d] %c\n\n", mpycw, mpx, table->map[mpycw][mpx]);
	int mpycs, mpxcs;
	if (table->player_angle > 0 && table->player_angle < 180)
		mpycs = (table->player_y - avoid_wall_collision) / T_SIZE;
	else
		mpycs = (table->player_y + avoid_wall_collision) / T_SIZE;
	if (table->player_angle > 270 || table->player_angle < 90)
		mpxcs = (table->player_x - avoid_wall_collision) / T_SIZE;
	else
		mpxcs = (table->player_x + avoid_wall_collision) / T_SIZE;
	
	int mpycd, mpxcd;
	int pa = table->player_angle + 90;
	if (pa > 359)
			pa -= 360;
	if (pa >= 0 && pa < 180)
		mpycd = (table->player_y + avoid_wall_collision) / T_SIZE;
	else
		mpycd = (table->player_y - avoid_wall_collision) / T_SIZE;
	if (pa >= 270 || pa < 90)
		mpxcd = (table->player_x + avoid_wall_collision) / T_SIZE;
	else
		mpxcd = (table->player_x - avoid_wall_collision) / T_SIZE;
	
	int mpyca, mpxca;
	pa = table->player_angle - 90;
	if (pa < 0)
			pa += 360;
	if (pa >= 0 && pa < 180)
		mpyca = (table->player_y + avoid_wall_collision) / T_SIZE;
	else
		mpyca = (table->player_y - avoid_wall_collision) / T_SIZE;
	if (pa >= 270 || pa < 90)
		mpxca = (table->player_x + avoid_wall_collision) / T_SIZE;
	else
		mpxca = (table->player_x - avoid_wall_collision) / T_SIZE;

	//int mpy_neg = (table->player_y - avoid_wall_collision) / T_SIZE;
	//int mpy_pos = (table->player_y + avoid_wall_collision) / T_SIZE;
	//int mpx_neg = (table->player_x - avoid_wall_collision) / T_SIZE;
	//int mpx_pos = (table->player_x + avoid_wall_collision) / T_SIZE;
	*/
	// ---offset wall collision---

	// ---circular wall collision---
	
	
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(table->mlx_start);
		exit (EXIT_SUCCESS);
	}
	else if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		table->is_attacking = 1;
	}
}
