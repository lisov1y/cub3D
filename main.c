/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mike <mike@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:30:01 by mike              #+#    #+#             */
/*   Updated: 2020/05/08 21:52:52 by mike             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	structs_init(t_player *plr, t_mlx *mlx)
{
	plr->posX = 22;
	plr->posY = 12;
	plr->dirX = -1;
	plr->dirY = 0;
	plr->planeX = 0;
	plr->planeY = 0.66;
	mlx->red = 255 << 16 ^ 0 << 8 ^ 0;
	mlx->green = 0 << 16 ^ 255 << 8 ^ 0;
	mlx->blue = 0 << 16 ^ 0 << 8 ^ 255;
	mlx->white = 255 << 16 ^ 255 << 8 ^ 255;
	mlx->yellow = 255 << 16 ^ 255 << 8 ^ 0;
}

int     main(void)
{
	t_mlx		*mlx;
	t_player	*plr;
	int			x;
	
	mlx = (t_mlx *)malloc(sizeof(t_mlx));
	plr = (t_player *)malloc(sizeof(t_player));
	structs_init(plr, mlx);
	mlx->mlx = mlx_init();
	mlx->window = mlx_new_window(mlx->mlx, W, H, "Raycast playground");
	x = -1;
	while (++x < W)
	{
		plr->cameraX = 2 * x / (double)W - 1;
		plr->rayDirX = plr->dirX + plr->planeX * plr->cameraX;
		plr->rayDirY = plr->dirY + plr->planeY * plr->cameraX;
		plr->mapX = (int)plr->posX;
		plr->mapY = (int)plr->posY;
		plr->deltaDistX = abs((int)(1 / plr->rayDirX));
		plr->deltaDistY = abs((int)(1 / plr->rayDirY));
		plr->hit = 0;
		if (plr->rayDirX < 0)
		{
			plr->stepX = -1;
			plr->sideDistX = (plr->posX - plr->mapX) * plr->deltaDistX;
		}
		else
		{
			plr->stepX = 1;
			plr->sideDistX = (plr->mapX + 1.0 - plr->posX) * plr->deltaDistX;
		}
		if (plr->rayDirY < 0)
		{
			plr->stepY = -1;
			plr->sideDistY = (plr->posY - plr->mapY) * plr->deltaDistY;
		}
		else
		{
			plr->stepY = 1;
			plr->sideDistY = (plr->mapY + 1.0 - plr->posY) * plr->deltaDistY;
		}
		while (plr->hit == 0)
		{
			if (plr->sideDistX < plr->sideDistY)
			{
				plr->sideDistX += plr->deltaDistX;
				plr->mapX += plr->stepX;
				plr->side = 0;
			}
			else
			{
				plr->sideDistY += plr->deltaDistY;
				plr->mapY += plr->stepY;
				plr->side = 1;
			}
			if (worldMap[plr->mapX][plr->mapY] > 0)
				plr->hit = 1;
		}
		if (plr->side == 0)
			plr->perpWallDist = (plr->mapX - plr->posX + (1 - plr->stepX) / 2) / plr->rayDirX;
		else
			plr->perpWallDist = (plr->mapY - plr->posY + (1 - plr->stepY) / 2) / plr->rayDirY;
		plr->lineHeight = (int)(H / plr->perpWallDist);
		plr->drawStart = -1 * (plr->lineHeight) / 2 + H / 2;
		if (plr->drawStart < 0)
			plr->drawStart = 0;
		plr->drawEnd = plr->lineHeight / 2 + H / 2;
		if (plr->drawEnd >= H)
			plr->drawEnd = H - 1;
		if (worldMap[plr->mapX][plr->mapY] == 1)
			mlx->color = mlx->red;
		else if (worldMap[plr->mapX][plr->mapY] == 2)
			mlx->color = mlx->green;
		else if (worldMap[plr->mapX][plr->mapY] == 3)
			mlx->color = mlx->blue;
		else if (worldMap[plr->mapX][plr->mapY] == 4)
			mlx->color = mlx->white;
		else
			mlx->color = mlx->yellow;
		if (plr->side == 1)
			mlx->color = mlx->color / 2;
		mlx->t = plr->drawStart;
		while (mlx->t <= plr->drawEnd)
		{
			mlx_pixel_put(mlx->mlx, mlx->window, x, mlx->t, mlx->color);
			++mlx->t;
		}
		mlx_key_hook(mlx->window, k)
	}
	mlx_loop(mlx->mlx);
	return (0);
}