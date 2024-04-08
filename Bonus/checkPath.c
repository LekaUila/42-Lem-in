#include "header.h"

void    ft_nextPath(t_room *room, int toAdd)
{
    int i = 0;
    if (room->isStart == 0)
    {
        if (room->pathway)
        {
            i = 0;
            if (room->checkPath > toAdd + 1 || room->checkPath == 0)
            room->checkPath = toAdd + 1;
            while (room->pathway[i] != NULL)
            {
                if (room->pathway[i]->checkPath == 0 || room->pathway[i]->isStart == 1 || room->pathway[i]->checkPath > toAdd + 1)
                {
                    ft_nextPath(room->pathway[i], toAdd + 1);
                }
                i++;
            }
        }
    }
    if (room->isStart == 1)
    {
        if (room->checkPath < toAdd + 1 || room->checkPath == 0)
        {
            room->checkPath = toAdd + 1;
        }
    }
}

void    ft_reverseNextPath(t_room *room, int toAdd)
{
    int i = 0;
    if (room->isEnd == 0)
    {
        if (room->pathway)
        {
            i = 0;
            if (room->checkPath2 > toAdd + 1 || room->checkPath2 == 0)
            room->checkPath2 = toAdd + 1;
            while (room->pathway[i] != NULL)
            {
                if (room->pathway[i]->checkPath2 == 0 || room->pathway[i]->isEnd == 1 || room->pathway[i]->checkPath2 > toAdd + 1)
                {
                    ft_reverseNextPath(room->pathway[i], toAdd + 1);
                }
                i++;
            }
        }
    }
    if (room->isEnd == 1)
    {
        if (room->checkPath2 < toAdd + 1 || room->checkPath2 == 0)
        {
            room->checkPath2 = toAdd + 1;
        }
    }
}

void    ft_finale(t_data *data)
{
    int i = 0;

    while (data->roomList[i] != NULL)
    {
        ft_printf("room is %s\n", data->roomList[i]->room);
        ft_printf("checkpathy = %d    checkpath2 = %d\n", data->roomList[i]->checkPath, data->roomList[i]->checkPath2);
        data->roomList[i]->checkPath += data->roomList[i]->checkPath2;
        i++;
    }
}

void    checkPath(t_data *data)
{
    ft_nextPath(data->end, 0);
    ft_reverseNextPath(data->start, 0);
    //ft_finale(data);
    //data->start->checkPath = 1;
    if (data->end->checkPath == 0)
        launch_fatal_error(NULL, data, -12);
    /*else
        ft_printf("\nThere is an escape, there is hope for the ant colonie !\n");*/
}