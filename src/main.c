/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:17:32 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/21 14:40:05 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main (int argc, char **argv)
{
	t_table	table;

	(void) argc;
	(void) argv;
	ft_memset(&table, 0, sizeof(table));
	table.enemy_attack = 0;
	if (argc != 2)
	{
		//write (2, "wrong input\n", 12);
		exit(EXIT_FAILURE);
	}
	// check that argc 1 is a file that can be opened and read and ends with .cub
	//parse_input();
	init_data(&table);
	table.filename = argv[1];
	if (read_file(&table))
	{
		return (1);
	}
	get_monitor_size(&table.width, &table.height);
	table.mlx_start = mlx_init(table.width, table.height, "cub3D", false);
	if (!table.mlx_start)
	{
		;//error
	}
	init_enemies(&table);
	convert_texture(&table.no_texture, &table.no_texture_colors, "pngs/texture_no.png");
	convert_texture(&table.so_texture, &table.so_texture_colors, "pngs/texture_so.png");
	convert_texture(&table.es_texture, &table.es_texture_colors, "pngs/texture_es.png");
	convert_texture(&table.ws_texture, &table.ws_texture_colors, "pngs/texture_ws.png");
	table.p_img[0] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_0.png");
	table.p_img[1] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_1.png");
	table.p_img[2] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_2.png");
	table.p_img[3] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_3.png");
	table.p_img[4] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_4.png");
	table.p_img[5] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_5.png");
	table.p_img[6] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_6.png");
	table.p_img[7] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_7.png");
	table.p_img[8] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_8.png");
	table.p_img[9] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_9.png");
	table.p_img[10] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_10.png");
	table.p_img[11] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_11.png");
	table.p_img[12] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_12.png");
	table.p_img[13] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_13.png");
	table.p_img[14] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_14.png");
	table.p_img[15] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_15.png");
	table.p_img[16] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_16.png");
	table.p_img[17] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_17.png");
	table.p_img[18] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_18.png");
	table.p_img[19] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_19.png");
	table.p_img[20] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_20.png");
	table.p_img[21] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_21.png");
	table.p_img[22] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_22.png");
	table.p_img[23] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_23.png");
	table.p_img[24] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_24.png");
	table.p_img[25] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_25.png");
	table.p_img[26] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_26.png");
	table.p_img[27] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_27.png");
	table.p_img[28] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_28.png");
	table.p_img[29] = load_image(table.mlx_start, "/home/omartela/hive-projects/cube3D/fireballs_explosion/fire_ball_blue_side_small/imgs_explode/img_29.png");
	table.right_hand = load_image(table.mlx_start, "pngs/rigth_hand.png");
	table.left_hand = load_image(table.mlx_start, "pngs/left_hand.png");
	table.e_img[0] = load_image(table.mlx_start, "pngs/enemy-run-5.png");
	table.e_img[1] = load_image(table.mlx_start, "pngs/enemy-run-1.png");
	table.e_img[2] = load_image(table.mlx_start, "pngs/enemy-run-2.png");
	table.e_img[3] = load_image(table.mlx_start, "pngs/enemy-run-3.png");
	table.e_img[4] = load_image(table.mlx_start, "pngs/enemy-run-4.png");
	table.mlx_2D = mlx_new_image(table.mlx_start, table.width, table.height); //to change
	if (!table.mlx_2D)
	{
		;//error
	}
	table.mlx_3D = mlx_new_image(table.mlx_start, table.width, table.height);
	if (!table.mlx_3D)
	{
		;//error
	}
	// ---how to scale a texture---
	/*int h = 300;
	int w = 300;
	float sh = (float)table.es_texture->height / h;
	float sw = (float)table.es_texture->width / w;
	printf("sh = %f\n", sh);
	printf("sw = %f\n", sw);
	int a = -1;
	float c = 0;
	while (++a < h)
	{
		int b = -1;
		float d = 0;
		while (++b < w)
		{
			int tex_c = (int)c;
			int tex_d = (int)d;
			mlx_put_pixel(table.mlx_3D, b, a, table.es_texture_colors[tex_c][tex_d]);
			d += sw;
			printf("%d\n", tex_d);
		}
		c += sh;
	}
	mlx_image_to_window(table.mlx_start, table.mlx_3D, 0, 0);*/

	/*y = -1;
	while (++y < table.es_texture->height)
	{
		x = -1;
		while (++x < table.es_texture->width)
			mlx_put_pixel(table.mlx_3D, x, y, table.es_texture_colors[y][x]);
	}
	mlx_image_to_window(table.mlx_start, table.mlx_3D, 0, 0);*/
	draw_minimap(&table);
	draw_raycasting(&table);
	mlx_image_to_window(table.mlx_start, table.mlx_3D, 0, 0);
	mlx_image_to_window(table.mlx_start, table.mlx_2D, 0, 0);
	insert_player_texture(&table);
	mlx_key_hook(table.mlx_start, &ft_keyboard, &table);
	mlx_loop_hook(table.mlx_start, &ft_hook, &table);
	//mlx_loop_hook(table.mlx_start, &ft_enemy, &table);
	mlx_loop(table.mlx_start);
}
