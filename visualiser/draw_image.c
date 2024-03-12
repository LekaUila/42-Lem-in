/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:26:25 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/12 20:38:47 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static void	img_pix_put(void *img_mlx, int x, int y, int color)
{
	char	*pixel;
	int		i;
	t_mlx_img	img;

	img.addr = mlx_get_data_addr(img_mlx, &img.bpp, &img.line_len, &img.endian);
	i = img.bpp -8;
	// ft_printf("i : %d\n", i);
	pixel = img.addr + (y * img.line_len + x * (img.bpp / 8));
	while (i >= 0)
	{
		// ft_printf("pixel put in : %d, %d with color %d\n", x, y, color);
		if (img.endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		else
			*pixel++ = (color >> (img.bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

static void	draw_line_bis(int *line, int *start_x, int *start_y)
{
	line[5] = line[4];
	if (line[5] > -line[0])
	{
		line[4] -= line[1];
		*start_x += line[2];
	}
	if (line[5] < line[1])
	{
		line[4] += line[0];
		*start_y += line[3];
	}
}

//line[6] from 0 to 6 is : difference_x difference_y sign_x sign_y
// check_next_pixel_pos check_next_pixel_pos 2
void	draw_line(t_data *data, int start_x, int start_y, int end_x, int end_y)
{
	int	save_y;
	int	save_x;
	int	line[6];

	save_y = start_y;
	save_x = start_x;
	line[0] = abs(end_x - save_x);
	if (save_x < end_x)
		line[2] = 1;
	else
		line[2] = -1;
	line[1] = abs(end_y - save_y);
	if (save_y < end_y)
		line[3] = 1;
	else
		line[3] = -1;
	if (line[0] > line[1])
		line[4] = line[0] / 2;
	else
		line[4] = -line[1] / 2;
	while (save_y != end_y || save_x != end_x)
	{
		if (save_x < WIDTH_W && save_y < HEIGHT_W)
			img_pix_put(data->img, save_x, save_y, RED);
		draw_line_bis(line, &save_x, &save_y);
	}
}

// static int	img_pix_get(void *img_mlx, int x, int y)
// {
// 	char		*pixel;
// 	t_mlx_img	img;
// 	int			result;

// 	img.addr = mlx_get_data_addr(img_mlx, &img.bpp, &img.line_len, &img.endian);
// 	pixel = img.addr + (y * img.line_len + x * (img.bpp / 8));
// 	result = *(int *)pixel;
// 	return (result);
// }

// static int	create_trgb(int r, int g, int b)
// {
// 	return (0xFF << 24 | r << 16 | g << 8 | b);
// }

void	draw_background(t_data *data)
{
	int			x;
	int			y;

	y = 0;
	while (y < HEIGHT_W)
	{
		x = 0;
		while (x < WIDTH_W)
		{
			img_pix_put(data->img, x, y, WHITE);
			x++;
		}
		y++;
	}
}

int	draw_room(t_data *data, int x, int y)
{
	int			pos_x = x * (LEN_OBJECT + (BORDER * 2)) + BORDER;
	int			pos_y = y * (LEN_OBJECT + (BORDER * 2)) + BORDER;
	// ft_printf("room in %d, %d draw in %d, %d\n", x, y, pos_x, pos_y);

	while (pos_x < x * (LEN_OBJECT + BORDER * 2) + LEN_OBJECT + BORDER)
	{
		pos_y = y * (LEN_OBJECT + BORDER * 2) + BORDER;

		while (pos_y < y * (LEN_OBJECT + BORDER * 2) + LEN_OBJECT + BORDER)
		{
			if (pos_x < WIDTH_W && pos_y < HEIGHT_W)
				img_pix_put(data->img, pos_x, pos_y + 1, BLACK);
			pos_y++;
		}
		pos_x++;
	}
	return (0);
}