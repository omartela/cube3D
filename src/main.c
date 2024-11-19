/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 09:17:32 by mpellegr          #+#    #+#             */
/*   Updated: 2024/11/19 14:04:01 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
/*
void    read_map(t_table *table, char *infile)
{
	int		i;
	int		bytes;
	int		player_pos;

	table->map_fd = open(infile, O_RDONLY);
	bytes = read(table->map_fd, table->map, sizeof(table->map));
	table->map[bytes] = '\0';
	printf("%s\n", table->map);
	i = -1;
	table->rows = 1;
	while (table->map[++i] != '\n')
		table->columns = i + 1;
	i = -1;
	while (table->map[++i] != '\0')
		if (table->map[i] == '\n')
			table->rows++;
	printf("%d x %d\n", table->columns, table->rows);
	player_pos = -1;
	while (table->map[++player_pos] != 'N')
		;
	table->player_row = (player_pos / (table->columns + 1)) + 1;
	table->player_col = player_pos - (table->player_row - 1) * (table->columns + 1) + 1;
	printf("%d x %d\n", table->player_col, table->player_row);
	table->player_x = (float)table->player_col * T_SIZE - T_SIZE / 2;
	table->player_y = (float)table->player_row * T_SIZE - T_SIZE / 2;
	printf("%f x %f\n", table->player_x, table->player_y);
}
*/

void draw_map(t_table *table)
{
	//double		cell_width;
	//double		cell_height;
	size_t		x;
	size_t		y;
	size_t		row;
	size_t		col;
	int			i;
	int			j;
	uint32_t	color;

	//cell_width = (float)500 / table->columns;
	//cell_height = (float)500 / table->rows;
	y = 0;
	while (y < T_SIZE * table->rows)
	{
		x = 0;
		while (x < T_SIZE * table->columns)
		{
			mlx_put_pixel(table->mlx_2D, x, y, 0xFF0000FF);
			++x;
		}
		++y;
	}
	
	row = 0;
	while (row < table->rows)
	{
		col = 0;
		while (col < table->columns)
		{
			x = col * T_SIZE;
			y = row * T_SIZE;

			if (table->map[row][col] == '1')
				color = 0xFFFFFFFF;
			else if (table->map[row][col] == '0')
				color = 0x000000FF;
			//else if (table->map[row * (table->columns + 1) + col] == 'N')
				//color = 0x0000FFFF;
			else
				color = 0x000000FF;
			i = -1;
			while (++i < T_SIZE - 1)
			{
				j = -1;
				while (++j < T_SIZE - 1)
					mlx_put_pixel(table->mlx_2D, x + j, y + i, color);
			}
			++col;
		}
		++row;
	}
	mlx_image_to_window(table->mlx_start, table->mlx_2D, 0, 0);
}

void draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	err = dx - dy;
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	while (1)
	{
		mlx_put_pixel(img, x0, y0, color);// Draw the pixel at (x0, y0)
		if (x0 == x1 && y0 == y1)
			break;// Stop if we’ve reached the end point
		e2 = 2 * err;
		if (e2 > -dy) {
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx) {
			err += dx;
			y0 += sy;
		}
	}
}

void draw_line_w_thk(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color, int thickness)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;
	int e2;
	
	// Calculate perpendicular direction for thickness
	float length = sqrt(dx * dx + dy * dy);   // Length of the line
	float offsetX = -(y1 - y0) / length;      // Perpendicular X offset
	float offsetY = (x1 - x0) / length;       // Perpendicular Y offset

	// Draw the line with thickness by drawing parallel lines
	for (int t = -thickness / 2; t <= thickness / 2; t++) {
		int tx0 = x0 + t * offsetX;  // Adjusted starting point
		int ty0 = y0 + t * offsetY;
		int tx1 = x1 + t * offsetX;  // Adjusted ending point
		int ty1 = y1 + t * offsetY;

		// Bresenham's line algorithm for each parallel line
		int x = tx0, y = ty0;
		int err_temp = err;
		while (1) {
			mlx_put_pixel(img, x, y, color);  // Draw the pixel at (x, y)
			if (x == tx1 && y == ty1)
				break;  // Stop if we’ve reached the end point
			e2 = 2 * err_temp;
			if (e2 > -dy) {
				err_temp -= dy;
				x += sx;
			}
			if (e2 < dx) {
				err_temp += dx;
				y += sy;
			}
		}
	}
}
void draw_circle(mlx_image_t *image, int x_center, int y_center, int radius, uint32_t color) {
    /*int	x;
	int	y;
    
	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if ((x * x + y * y) <= (radius * radius))
				mlx_put_pixel(image, x_center + x, y_center + y, color);
			x++;
		}
		y++;
	}*/

	const double step = 0.01;
    double angle;
	int x;
	int y;

	angle = 0;
	while (angle <= 2 * PI)
	{
		x = x_center + (int)(radius * cos(angle));
		y = y_center + (int)(radius * sin(angle));
		mlx_put_pixel(image, x, y, color);
		angle += step;
	}
}

float	deg_to_rad(float deg)
{
	return ((float)deg / 180 * PI);
}

void    draw_player(t_table *table)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	y = table->player_y - 5;
	while (y++ < table->player_y + 5)
	{
		x = table->player_x - 5;
		while (x++ < table->player_x + 5)
			mlx_put_pixel(table->mlx_2D, x, y, 0xFFFF00FF);
	}
	//draw_line_w_thk(table->mlx_2D, table->player_x, table->player_y, table->player_x+table->player_delta_x, table->player_y+table->player_delta_y, 0xFFFF00FF, 4);

	/*y = -1;
	while (++y < 800)
	{
		x = -1;
		while (++x < 1200)
			mlx_put_pixel(table->mlx_3D, x, y, 0x000000FF);
	}*/

	/*float px, py, x1, y1, delta_x, delta_y, vx, vy;
	px = table->player_x;
	py = table->player_y;
	//printf("\n\n%f x %f\n", px, py);
	if (table->player_angle > 3 *PI / 2 || table->player_angle < PI / 2)
		delta_x = table->player_col * T_SIZE - table->player_x;
	else
		delta_x = (table->player_col - 1) * T_SIZE - table->player_x;
	vx = fabs(delta_x / cos(table->player_angle));
	//printf("\ndelta_x = %f\n", delta_x);
	//printf("vector_x = %f\n", vx);

	if (table->player_angle > 0 && table->player_angle < PI)
		delta_y = table->player_row * T_SIZE - table->player_y;
	else
		delta_y = (table->player_row - 1) * T_SIZE - table->player_y;
	vy = fabs(delta_y/(cos(PI / 2 - (2 * PI - table->player_angle))));
	//printf("delta_y = %f\n", delta_y);
	//printf("vector_y = %f\n", vy);
	if (vx > vy)
	{
		if (table->player_angle > 3 *PI / 2 || table->player_angle < PI / 2)
			delta_x = sqrt(vy * vy - delta_y * delta_y);
		else
			delta_x = -sqrt(vy * vy - delta_y * delta_y);
	}
	else
	{
		if (table->player_angle > 0 && table->player_angle < PI)
			delta_y = sqrt(vx * vx - delta_x * delta_x);
		else
			delta_y = -sqrt(vx * vx - delta_x * delta_x);
	}
	//printf("\ndelta_x = %f\n", delta_x);
	//printf("delta_y = %f\n", delta_y);
	x1 = px + delta_x;
	y1 = py + delta_y;
	//printf("\n%f x %f\n", x1, y1);
	draw_line(table->mlx_2D, px, py, x1, y1, 0xFFFF00FF);*/

	
	
	float pa = table->player_angle - 30;
	int n_of_rays = table->width / 2;
	//printf("\nplayer angle = %f\n", table->player_angle);
	//printf("player angle - 30 = %f\n", pa);
	int r = -1;
	while (++r < n_of_rays)
	{
		if (pa > 359)
			pa -= 360;
		if (pa < 0)
			pa += 360;
		float angle = deg_to_rad(pa);
		float sx, sy, dx, dy, vv, vh, hx, hy, vx, vy, fx, fy, fv;
		// ----vertical lines----
		vv = 10000;
		if (angle > 3 *PI / 2 || angle < PI / 2)
		{
			sx = (int)(table->player_x / T_SIZE) * T_SIZE + T_SIZE;
			sy = -(table->player_x - sx) * tan(angle) + table->player_y;
			dx = T_SIZE;
			dy = T_SIZE * tan(angle);
		}
		else
		{
			sx = (int)(table->player_x / T_SIZE) * T_SIZE - 0.0001;
			sy = -(table->player_x - sx) * tan(angle) + table->player_y;
			dx = -T_SIZE;
			dy = -T_SIZE * tan(angle);
		}
		//printf("----vertical lines----\nsx = %f\n", sx);
		//printf("sy = %f\n", sy);
		//printf("dx = %f\n", dx);
		//printf("dy = %f\n", dy);
		//printf("angle = %.0f\n", table->player_angle*180/PI);
		int mx, my;
		while (sx > 0 && sy > 0 && sx < 640 && sy < 640) //check if need to add more conditins
		{
			mx = sx / T_SIZE;
			my = sy / T_SIZE;
			//printf("mx = %d\n", mx);
			//printf("my = %d\n", my);
			//printf("table->map[%d][%d] = %c\n", mx, my, table->map[mx][my]);
			//printf("%c\n----vertical lines----\n\n", table->map[mp]);
			if (table->map[my][mx] == '1')
				break;
			else
			{
				sx+=dx;
				sy+=dy;
			}
		}
		//printf("sx = %f\n", sx);
		//printf("sy = %f\n", sy);
		vv = sqrt((table->player_x - sx) * (table->player_x -  sx) + (table->player_y - sy) * (table->player_y - sy));
		vx = sx;
		vy = sy;
		//printf("\nvertical vector = %f\n", vv);
		// ----horizontals lines----
		vh = 10000;
		if (angle > 0 && angle < PI)
		{
			sy = (int)(table->player_y / T_SIZE) * T_SIZE + T_SIZE;
			sx = -(table->player_y - sy) / tan(angle) + table->player_x;
			dy = T_SIZE;
			dx = T_SIZE / tan(angle);
		}
		else
		{
			sy = (int)(table->player_y / T_SIZE) * T_SIZE - 0.0001;
			sx = -(table->player_y - sy) / tan(angle) + table->player_x;
			dy = -T_SIZE;
			dx = -(T_SIZE / tan(angle));
		}
		//printf("----horizontals lines----\nsx = %f\n", sx);
		//printf("sy = %f\n", sy);
		//printf("dx = %f\n", dx);
		//printf("dy = %f\n", dy);
		//printf("angle = %f\n", table->player_angle);
		//int mx, my, mp;
		while (sx > 0 && sy > 0 && sx < 640 && sy < 640) //check if need to add more conditins
		{
			mx = sx / T_SIZE;
			my = sy / T_SIZE;
			//printf("mx = %d\n", mx);
			//printf("my = %d\n", my);
			//printf("table->map[%d][%d] = %c\n", mx, my, table->map[mx][my]);
			//printf("----horizontals lines----\n\n");
			if (table->map[my][mx] == '1')
				break;
			else
			{
				sx+=dx;
				sy+=dy;
			}
		}
		//printf("sy = %f\n", sy);
		//printf("sx = %f\n", sx);
		vh = sqrt((table->player_x - sx) * (table->player_x -  sx) + (table->player_y - sy) * (table->player_y - sy));
		hx = sx;
		hy = sy;
		//printf("horizontal vector = %f\n", vh);
		//uint32_t color;
		if (vv > vh)
		{
			//printf("vh = %f\n", vh);
			//printf("hx = %f; hy = %f\n", hx, hy);
			fx  = hx;
			fy = hy;
			fv = vh;
			//color = 0xFFFF00FF;
			//draw_line(table->mlx_2D, table->player_x, table->player_y, hx, hy, 0xFFFF00FF);
		}
		else
		{
			//printf("vv = %f\n", vv);
			//printf("vx = %f; vy = %f\n\n", vx, vy);
			fx  = vx;
			fy = vy;
			fv = vv;
			//color = 0xCCCC00FF;
			//draw_line(table->mlx_2D, table->player_x, table->player_y, vx, vy, 0xFFFF00FF);
		}
		//printf("mx = %d\n", mx);
		//printf("my = %d\n", my);
		//printf("mp = %d\n", mp);
		//printf("%c\n", table->map[mp]);
		
		//printf("ray %d, final vector = %f\n", r, fv);

		draw_line(table->mlx_2D, table->player_x, table->player_y, fx, fy, 0xFFFF00FF);
		
		int ca=(table->player_angle - pa);
		if (ca > 359)
			ca -= 360;
		if (ca < 0)
			ca += 360;
		fv=fv*cos(deg_to_rad(ca));

		//printf("\nvector %d angle = %f\n", r, pa);
		//printf("vextor %d = %f\n", r, fv);
		int wall_h = T_SIZE * table->height / 2 / fv;
		float tx_vertical_step = (float)table->es_texture->height / wall_h;
		float tx_v_offset = 0;
		//printf("wall h %d = %d\n", r, wall_h);
		if (wall_h > table->height / 2)
		{
			tx_v_offset = (wall_h - table->height / 2) / 2;
			wall_h = table->height / 2;
		}
		int drawStart = -wall_h / 2 + table->height / 2 / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = wall_h / 2 + table->height / 2 / 2;
		if(drawEnd >= table->height / 2)
			drawEnd = table->height / 2 - 1;
		//printf("wall_h = %d\n", wall_h);
		//printf("render_x = %d\n", render_x);
		//printf("draw start = %d\n", drawStart);
		//printf("draw end = %d\n", drawEnd);
		
		int scaled_x_start = r * (table->width / 2 / n_of_rays);
		int scaled_x_end = (r + 1) * (table->width / 2 / n_of_rays) - 1;
		int i = scaled_x_start;
		//printf("scaled x end = %d\n", scaled_x_end);

		//float tx_vertical_step = (float)table->es_texture->height / wall_h;
		//float tx_horizntal_step = (float)table->es_texture->width / (scaled_x_end - scaled_x_start + 1);
		//printf("h step = %f\n", tx_horizntal_step);
		//printf("vertical step = %f\n", tx_vertical_step);
		//float ty = tx_v_offset * tx_vertical_step;
		float ty = tx_v_offset * tx_vertical_step;

		//if (tx_v_offset > 0)
		//	printf("ray n = %d	wall h = %d	offset = %f	vertical step = %f	ty = %f\n", r, (int)(T_SIZE * 800 / fv), tx_v_offset, tx_vertical_step, ty);

		float tx;
		if (vv > vh)
		{
			tx = ((int)fx % T_SIZE) * table->es_texture->width / T_SIZE;
			if (table->player_angle < 180)
			{
				if (tx == 0)
					tx = table->es_texture->width;
				tx = table->es_texture->width - tx;
			}
		}
		else
		{
			tx = ((int)fy % T_SIZE) * table->es_texture->width / T_SIZE;
			if (table->player_angle > 90 && table->player_angle < 270)
			{
				if (tx == 0)
					tx = table->es_texture->width;
				tx = table->es_texture->width - tx;
			}
		}
			
		//printf("tx x hitting point = %f\n", tx);
		
		//float tx = ((int)fv % T_SIZE) * table->es_texture->width / T_SIZE;
		
		//printf("tx = %f\n", tx);

		// Draw the wider vertical slice across the scaled width range
		while (i <= scaled_x_end)
		{
			draw_line(table->mlx_3D, i, 0, i, drawStart, 0xADD8E6FF);
			draw_line(table->mlx_3D, i, drawEnd, i, table->height / 2 - 1, 0x8B4513FF);
			//draw_line(table->mlx_3D, i, drawStart, i, drawEnd, color);
			int a = drawStart;
			ty = tx_v_offset * tx_vertical_step;
			while (a <= drawEnd)
			{
				int tex_x = (int)tx;
				int tex_y = (int)ty;
				if (tex_y >= (int)table->es_texture->height)
					tex_y = table->es_texture->height - 1;
				//printf("%08X\n", table->no_texture_colors[tex_y][tex_x]);
				//printf("ty_int = %d\n", tex_y);
				//printf("%d x %d\n", i, a);
				//printf("colour [%d][%d] = %08X\n", tex_y, tex_x, table->es_texture_colors[tex_y][tex_x]);
				//printf("%d	%d\n", tex_x, tex_y);
				mlx_put_pixel(table->mlx_3D, i, a, table->es_texture_colors[tex_y][tex_x]);
				//if (tx_v_offset > 0)
				//	mlx_put_pixel(table->mlx_3D, i, a, 0x000000FF);
				ty += tx_vertical_step;
				a++;
			}
			//tx += tx_horizntal_step;
			i++;
		}
		pa = pa + ((float)60 / n_of_rays);
	}
	draw_circle(table->mlx_2D, table->player_x, table->player_y, 20, 0x00FF00FF);
	mlx_image_to_window(table->mlx_start, table->mlx_3D, table->width / 2, 0);
	//printf("player angle + 30 = %f\n", pa);
}
int	main (int argc, char **argv)
{
	t_table	table;

	(void) argc;
	(void) argv;
	if (argc != 2)
	{
		write (2, "wrong input\n", 12);
		exit(EXIT_FAILURE);
	}
	// check that argc 1 is a file that can be opened and read and ends with .cub
	//parse_input();
	init_data(&table);
	table.filename = argv[1];
	read_map(&table);
	if (!validate_map(&table))
		return (1);
	get_monitor_size(&table.width, &table.height);
	table.mlx_start = mlx_init(table.width, table.height, "cub3D", false);
	if (!table.mlx_start)
	{
		;//error
	}
	convert_texture(&table.no_texture, &table.no_texture_colors, "pngs/texture_no.png");
	convert_texture(&table.so_texture, &table.so_texture_colors, "pngs/texture_so.png");
	convert_texture(&table.es_texture, &table.es_texture_colors, "pngs/texture_es.png");
	convert_texture(&table.ws_texture, &table.ws_texture_colors, "pngs/texture_ws.png");
	table.mlx_2D = mlx_new_image(table.mlx_start, table.columns * T_SIZE, table.rows * T_SIZE);
	if (!table.mlx_2D)
	{
		;//error
	}
	table.mlx_3D = mlx_new_image(table.mlx_start, table.width / 2, table.height / 2);
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
	draw_map(&table);
	draw_player(&table);
	mlx_key_hook(table.mlx_start, &ft_keyboard, &table);
	mlx_loop(table.mlx_start);
}
