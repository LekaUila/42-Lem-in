/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:51:19 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/14 16:38:18 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "./libft/libft.h"
# include <time.h>
# include "./minilibx-linux/mlx.h"
# include "./minilibx-linux/mlx_int.h"

//VIZU UTILS DEFINE

# define WIDTH_W 1200
# define HEIGHT_W 900
# define BORDER 0
# define LEN_OBJECT  10
# define CAMERA_SPEED  3
# define VIZU_SPEED 3
# define LEN_ANT  ((LEN_OBJECT / 2) + (LEN_OBJECT % 2))


//COLOR

# define RED 0xd80000
# define BLACK 0x020000
# define WHITE 0xebebff
# define GREEN 0x009a00
# define GREY 0xa7a7a7
# define YELLOW 0xffd500

//VISU COLOR ASSIGNATION

# define PATH_COLOR_COLOR BLACK
# define START_ROOM_COLOR GREEN
# define EXIT_ROOM_COLOR RED
# define ROOM_COLOR BLACK
# define ANT_COLOR YELLOW

typedef struct s_room
{
    char				*room;
	int					x;
	int					y;
	int					checkPath;
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

typedef struct s_ant
{
	t_room	*actual;
	t_room	*toGo;
}	t_ant;

typedef struct s_data
{
	int total_ants;
	t_room	*start;
	t_room	*end;
	t_room	**roomList;
	void	*id_mlx;
	void	*window;
	void	*img;
	char	isPaused;
	char	isOnlyNext;
	clock_t	last_time;
	int		cam_x;
	int		cam_y;
	int		stepAdvancement;
	int		stepActual;
	t_ant	**ants_list;
}    	t_data;

//FREE AND EXIT FUNCTION
void	freeForAll(t_data *data);
void	fatal_error(char *line, t_data *data, char *str);
void	launch_fatal_error(char *line, t_data *data, int error);
void	exitVisu(t_data *data, int er);

//PARSING
void	parse(t_data *data);

//DRAWING
void	draw_ants_colony(t_data *data);

//KEYBORD
int		ft_key_hook(int keycode, void *param);
int		ft_hook_window_destroy(void	*param);
int		ft_other_hook(void *param);

//OTHERS
void    printRooms(t_data *data);
void	startAlgo(t_data *data);
void	checkPath(t_data *data);

#endif
