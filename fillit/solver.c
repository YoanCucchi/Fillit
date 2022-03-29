/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solver.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekantane <ekantane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 11:54:19 by ycucchi           #+#    #+#             */
/*   Updated: 2022/03/29 16:01:11 by ycucchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fillit.h"

int	solve_tet(char **grid, t_tetris *stack, int size)
{
	int	x;
	int	y;
	int	*tet;

	y = -1;
	tet = (int *)malloc(sizeof(int) * 8);
	if (!stack)
	{
		free(tet);
		return (1);
	}
	while (++y < size)
	{
		x = -1;
		while (++x < size)
		{
			dup_coord(tet, stack->tet_id);
			shift_tet(tet, x, y);
			if (solve_helper(grid, tet, stack, size))
				return (1);
		}
	}
	free(tet);
	return (0);
}

int	*x_shift(int *tet, int x)
{
	int	i;
	int	size;

	size = 4;
	i = 0;
	while (size--)
	{
		tet[i] = tet[i] + x;
		i += 2;
	}
	return (tet);
}

int	*y_shift(int *tet, int y)
{
	int	i;
	int	size;

	size = 4;
	i = 1;
	while (size--)
	{
		tet[i] = tet[i] + y;
		i += 2;
	}
	return (tet);
}

int	*shift_tet(int *tet, int x, int y)
{
	tet = x_shift(tet, x);
	tet = y_shift(tet, y);
	return (tet);
}

int	solve_helper(char **grid, int *tet, t_tetris *stack, int size)
{
	if (collision(grid, tet, size))
	{
		insert_piece(grid, tet, stack->c);
		if (solve_tet(grid, stack->next, size))
		{
			free(tet);
			return (1);
		}
		clear_piece(grid, tet);
	}
	return (0);
}
