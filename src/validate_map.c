/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omartela <omartela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 11:44:07 by omartela          #+#    #+#             */
/*   Updated: 2024/11/14 14:10:36 by omartela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static int	validate_file_ext(char *file)
{
	char	*ext;

	ext = NULL;
	ext = ft_strrchr(file, '.');
	if (ext == NULL)
	{
		ft_error("Invalid file name or extension");
		return (0);
	}
	if (ft_strncmp(ext, ".cub", 5) != 0)
	{
		ft_error("Invalid file name or extension");
		return (0);
	}
	return (1);
}

static void	check_character(t_table *table, int c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
		table->player += 1;
}

static int	validate_map_char(char c)
{
	if (ft_strchr("NSWE 10", c))
		return (1);
	return (0);
}

static int	validate_map_chars(t_table *table)
{
	size_t	col;
	size_t	row;

	col = 0;
	while (col < table->columns)
	{
		row = 0;
		while (row < table->rows)
		{
			if (!validate_map_char(table->map[col][row]))
			{
				ft_error("Map has invalid characters");
				return (0);
			}
			check_character(table, table->map[col][row]);
			++row;
		}
		++col;
	}
	if (table->player != 1)
	{
		ft_error("Too few or too many players");
		return (0);
	}
	return (1);
}

int	validate_map_chars_and_ext(t_table *table)
{
	if (!validate_file_ext(table->filename))
		return (0);
	if (!validate_map_chars(table))
		return (0);
	return (1);
}

static int	validate_walls_sides(t_table *table)
{
	size_t	col;
	size_t	row;

	col = 0;
	row = 0;
	while (col < table->columns)
	{
		row = 0;
		while (table->map[col][row] == ' ')
			++row;
		if (table->map[col][row] != '1')
		{
			ft_error("Map has invalid characters at sides");
			return (0);
		}
		++col;
	}
	col = 0;
	row = table->rows;
	while (col < table->columns)
	{
		row = 0;
		while (table->map[col][row] == ' ')
			--row;
		if (table->map[col][row] != '1')
		{
			ft_error("Map has invalid characters at sides");
			return (0);
		}
		++col;
	}
	return (1);
}

static int	validate_walls_top_bot(t_table *table)
{
	size_t	row;

	row = 0;
	while (row < table->rows)
	{
		while (table->map[0][row] == ' ')
			++row;
		if (table->map[0][row] != '1')
		{
			ft_error("Map has invalid characters top or bot");
			return (0);
		}
		++row;
	}
	row = 0;
	while (row < table->rows)
	{
		while (table->map[table->columns][row] == ' ')
			--row;
		if (table->map[table->columns][row] != '1')
		{
			ft_error("Map has invalid characters top or bot");
			return (0);
		}
		++row;
	}
	return (1);
}

int	validate_map(t_table *table)
{
	if (!validate_map_chars_and_ext(table))
		return (0);
	if (!validate_walls_sides(table))
		return (0);
	if (!validate_walls_top_bot(table))
		return (0);
	return (1);
}
