/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:51:19 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/12 20:04:30 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include <time.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# define WIDTH_W 900
# define HEIGHT_W 600
# define BORDER 3
# define LEN_OBJECT  10

//COLOR
# define RED 0xd80000
# define BLACK 0x020000
# define WHITE 0xebebff
# define GREEN 0x009a00
# define GREY 0xa7a7a7
# define YELLOW 0xffd500


typedef struct s_room
{
    char				*room;
	int					x;
	int					y;
    long long int		ants;
    char				isStart;
    char				isEnd;
    struct s_room		 **pathway;
}    	t_room;

typedef struct s_mlx_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_mlx_img;

typedef struct s_data
{
	int total_ants;
	t_room	*start;
	t_room	*end;
	t_room	**roomList;
	void	*id_mlx;
	void	*window;
	void	*img;
	clock_t	last_time;
	int		cam_x;
	int		cam_y;
}    	t_data;

void	freeForAll(t_data *data);
void	parse(t_data *data);
void	fatal_error(char *line, t_data *data, char *str);
void	launch_fatal_error(char *line, t_data *data, int error);
void    printRooms(t_data *data);
void	exitVisu(t_data *data, int er);

//DRAWING
void	draw_background(t_data *data);
int		draw_room(t_data *data, int x, int y);
void	draw_line(t_data *data, int start_x, int start_y, int end_x, int end_y);

//KEYBORD
int		ft_key_hook(int keycode, void *param);
int		ft_hook_window_destroy(void	*param);
int		ft_other_hook(void *param);
#endif
