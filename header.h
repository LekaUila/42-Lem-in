/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:51:19 by lflandri          #+#    #+#             */
/*   Updated: 2024/04/05 16:34:56 by lflandri         ###   ########.fr       */
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
# define BORDER 1
# define LEN_OBJECT  8
# define CAMERA_SPEED_START  3
# define CAMERA_SPEED_MODIFIER 3
# define CAMERA_SPEED_MIN  3
# define CAMERA_SPEED_MAX  45
# define VIZU_SPEED 1
# define LEN_ANT  ((LEN_OBJECT / 2) + (LEN_OBJECT % 2))
# define PANNEL_LEN	190
# define BUTTON_PAUSED_X 30
# define BUTTON_PAUSED_Y 120
# define BUTTON_PAUSED_LEN	50
# define BUTTON_STEP_X 110
# define BUTTON_STEP_Y 120
# define BUTTON_STEP_LEN 50


//COLOR

# define RED 0xd80000
# define BLACK 0x020000
# define WHITE 0xebebff
# define GREEN 0x009a00
# define GREY 0xa7a7a7
# define YELLOW 0xffd500
# define PURPLE 0xff00ff
# define BLUE 0x0384fc

//VISU COLOR ASSIGNATION

# define PATH_COLOR						BLACK
# define START_ROOM_COLOR				GREEN
# define EXIT_ROOM_COLOR				RED
# define ROOM_COLOR						BLACK
# define ANT_COLOR						BLUE
# define ROOM_NAME_COLOR				PURPLE
# define PANNEL_BACKGROUND_COLOR		GREY
# define PANNEL_BORDER_COLOR			BLACK
# define PANNEL_TEXT_COLOR				BLACK
# define BUTTON_PAUSED_COLOR_OFF		RED
# define BUTTON_PAUSED_COLOR_ON			GREEN
# define BUTTON_PAUSED_BORDER_COLOR		BLACK
# define BUTTON_PAUSED_TEXT_COLOR		BLACK
# define BUTTON_STEP_COLOR_OFF			RED
# define BUTTON_STEP_COLOR_ON			GREEN
# define BUTTON_STEP_BORDER_COLOR		BLACK
# define BUTTON_STEP_TEXT_COLOR			BLACK
# define BUTTON_CAM_COLOR				PURPLE
# define BUTTON_CAM_BORDER_COLOR		BLACK
# define BUTTON_CAM_TEXT_COLOR			BLACK
# define CAM_SPEED_BAR_BACKGROUND_COLOR	BLACK
# define CAM_SPEED_BAR_CENTER_COLOR		PURPLE

// DEBUG DEFINE
# define DEBUG_PRINT 0

// OTHER DEFINE


# define SHORTEST_PATH 1
# define LIST_PATH 0


typedef struct s_room
{
    char				*room;
	int					x;
	int					y;
	int					checkPath;
	int					checkPath2;
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

typedef struct s_trueAnt
{
	int number;
	t_room	**path;
	int		room;
}	t_trueAnt;

typedef struct s_ant
{
	t_room	*actual;
	t_room	*toGo;
}	t_ant;

typedef struct s_data
{
	int 		total_ants;
	int			stopTheCount;
	t_room		*start;
	t_room		*end;
	t_room		**roomList;
	void		*id_mlx;
	void		*window;
	void		*img;
	char		isPaused;
	char		isOnlyNext;
	clock_t		last_time;
	int			cam_x;
	int			cam_y;
	int			cam_speed;
	int			stepAdvancement;
	int			stepActual;
	t_ant		**AMIset;
	t_trueAnt	*ants;
	double		calculationTime;
	int			moveNB;
}    	t_data;

//FREE AND EXIT FUNCTION
void	freeForAll(t_data *data);
void	fatal_error(char *line, t_data *data, char *str);
void	launch_fatal_error(char *line, t_data *data, int error);
void    printRoom(t_room *room);
void	exitVisu(t_data *data, int er);

//PARSING
void	parse(t_data *data);

//DRAWING
void	draw_ants_colony(t_data *data);

//KEYBORD
int		ft_mouse_hook(int keycode, int x, int y, void *param);
int		ft_key_hook(int keycode, void *param);
int		ft_hook_window_destroy(void	*param);
int		ft_other_hook(void *param);

//OTHERS
void    printRooms(t_data *data);
void	startAlgo(t_data *data);
void	checkPath(t_data *data);
void    printPath(t_room **path);

//ALGO
int		AntsSwitcher(t_data *data, t_room ***pathToUse);
int		culDeSac(t_room **pathToVictory);
int		crossPath(t_room **path1, t_room **path2);
int		pathSize(t_room **path);
int		**creatCrossPathList(t_room ***pathToVictory, int len_alloc);
void	findShortestAndUnique( t_room ***pathToVictory, t_room ***listPathTest, t_room ***listPathSuccess, int optimalMax,  int dec, int **crossPathList, int len_alloc, int ** intlist,int * lenlist, int lenPathtest, t_room  **untract_path);


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
