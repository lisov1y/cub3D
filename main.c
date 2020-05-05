/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mike <mike@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:30:01 by mike              #+#    #+#             */
/*   Updated: 2020/05/05 16:49:33 by mike             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx/mlx.h"

int     main(void)
{
	void    *mlx;

	mlx = mlx_init();
	mlx_new_window(mlx, 1920, 1080, "A window, nothing to see here");
	mlx_loop(mlx);
	return (0);
}