/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:51:19 by lflandri          #+#    #+#             */
/*   Updated: 2024/03/15 15:55:05 by lflandri         ###   ########.fr       */
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
# define VIZU_SPEED 9
# define LEN_ANT  ((LEN_OBJECT / 2) + (LEN_OBJECT % 2))


//COLOR

# define RED 0xd80000
# define BLACK 0x020000
# define WHITE 0xebebff
# define GREEN 0x009a00
# define GREY 0xa7a7a7
# define YELLOW 0xffd500
# define PURPLE 0xff00ff

//VISU COLOR ASSIGNATION

# define PATH_COLOR_COLOR BLACK
# define START_ROOM_COLOR GREEN
# define EXIT_ROOM_COLOR RED
# define ROOM_COLOR BLACK
# define ANT_COLOR PURPLE

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
	t_ant	**AMIset;
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

// AMI

/*
Return the len of an AMIset
If the AMIset is NULL, return 0;
*/
int AMI_getStepNumber(t_ant **AMIset);

/*
Add a new step to the AMIset of data.
The new step is of len data->total_ants + 1.

return -1 if an error occured, 0 else.
*/
int AMI_addNewStep(t_data *data);

/*
Add number ants to the start in the last step of the AMIset of data.
*/
void AMI_setNumberOfAntsForStart(t_data *data, int number);

/*
Add number ants to the end in the last step of the AMIset of data.
*/
void AMI_setNumberOfAntsForEnd(t_data *data, int number);

/*
Add a ants in AMIset of data.

This end will of the t_room *actual to the t_room *toGo.
*/
void AMI_addAntsMovement(t_data *data, t_room *actual, t_room *toGo);


#endif
