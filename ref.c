/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ref.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mike <mike@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:30:01 by mike              #+#    #+#             */
/*   Updated: 2020/05/08 14:15:00 by mike             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//mlx_get_data_addr ( void *img_ptr, int *bits_per_pixel, int *size_line, int *endian );
//mlx_new_image ( void *mlx_ptr, int width, int height );

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct s_mlx
{
	void*		mlx;
	void*		window;
	void*		img;
	int			*data;
	int			bpp;
	int			size;
	int			endian;
}				t_mlx;


void	put_pixel_to_image(int *data, int x, int y, int color, int size)
{
	if (1 == 1)
		data[x + (y * size) * 8] = color;
}

void	draw(t_mlx *mlx, int color)
{
	int x;
	int y;

	y = -1;
	while (++y <= 720)
	{
		x = -1;
		while (++x <= 1080)
			put_pixel_to_image(mlx->data, x, y, color, mlx->size);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->img, 0, 0);
}

int	exit_hook(t_mlx *mlx)
{
	mlx->size = mlx->size;
	exit(0);
	return (1);
}

int	key_press_hook(int key, t_mlx *mlx)
{
	printf("%d\n", key);
	if (key == 65307)
	{
		mlx_destroy_window(mlx->mlx, mlx->window);
		exit(0);
	}
	return (key);
}

int		init_hooks(t_mlx *mlx)
{
	mlx_hook(mlx->window, 17, 0, exit_hook, mlx);
	mlx_hook(mlx->window, 2, 0, key_press_hook, mlx);
	return (1);
}
int     main(void)
{
	int		color;
	t_mlx	mlx;

	color = 0 << 16 ^ 0 << 8 ^ 0;
	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, W, H, "A window, nothing to see here");
	mlx.img = mlx_new_image(mlx.mlx, W, H);
	mlx.data = (int *)mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size, &mlx.endian);
	mlx.size = mlx.size / mlx.bpp;
	draw(&mlx, color);
	mlx_key_hook(mlx.window, key_press_hook, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}