/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpellegr <mpellegr@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 09:32:58 by omartela          #+#    #+#             */
/*   Updated: 2024/12/12 10:32:04 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

mlx_texture_t	*load_texture(char *str)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(str);
	if (!texture)
	{
		ft_error("Load texture failed");
		return (NULL);
	}
	return (texture);
}

mlx_image_t	*load_image(mlx_t *mlx, char *str)
{
	mlx_image_t		*img;
	mlx_texture_t	*texture;

	texture = load_texture(str);
	if (!texture)
		return (NULL);
	img = mlx_texture_to_image(mlx, texture);
	mlx_delete_texture(texture);
	if (!img)
	{
		ft_error("Load image failed");
		return (NULL);
	}
	return (img);
}

void	convert_texture(t_texture *my_tx, uint32_t ***tx_colors, char *str)
{
	uint32_t		i;
	uint32_t		x;
	uint32_t 		y;
	mlx_texture_t	*tx;

	tx = load_texture(str);
	if (!tx)
		return ; //error
	*tx_colors = (uint32_t **)malloc(sizeof(uint32_t *) * (tx->height));
	if (!(*tx_colors)) {
		printf("Memory allocation failed for rows\n");
		return;
	}
	i = -1;
	while (++i < tx->height)
	{
		(*tx_colors)[i] = (uint32_t *)malloc(sizeof(uint32_t) * (tx->width));
		if (!(*tx_colors)[i])
		{
			printf("Memory allocation failed for rows\n");
			return ;
		}
	}
	i = 0;
	y = -1;
	while (++y < tx->height)
	{
		x = -1;
		while (++x < tx->width)
		{
			(*tx_colors)[y][x] = get_rgba(tx->pixels[i], tx->pixels[i + 1], tx->pixels[i + 2], tx->pixels[i + 3]);
			i += 4;
		}
	}
	my_tx->height = tx->height;
	my_tx->width = tx->width;
	mlx_delete_texture(tx);
}
