#include "header.h"

void    ft_nextPath(t_room *room, int toAdd)
{
    int i = 0;
    if (room->isEnd == 0)
    {
        if (room->pathway)
        {
            i = 0;
            room->checkPath = toAdd + 1;
            while (room->pathway[i] != NULL)
            {
                if (room->pathway[i]->checkPath == 0 || room->pathway[i]->isEnd == 1 || room->pathway[i]->checkPath > toAdd + 1)
                {
                    ft_nextPath(room->pathway[i], toAdd + 1);
                }
                i++;
            }
        }
    }
    if (room->isEnd == 1)
    {
        if (room->checkPath < toAdd + 1 || room->checkPath == 0)
        {
            room->checkPath = toAdd + 1;
        }
    }
}

void    checkPath(t_data *data)
{
    ft_nextPath(data->start, 0);
    if (data->end->checkPath == 0)
        launch_fatal_error(NULL, data, -12);
    else
        ft_printf("\nThere is an escape, there is hope for the ant colonie !\n");
}