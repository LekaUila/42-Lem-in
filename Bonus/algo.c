/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 03:39:22 by lflandri          #+#    #+#             */
/*   Updated: 2024/04/08 15:32:18 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int numberOfPath(t_room *room)
{
    int i = 0;

    if (!room->pathway)
        return (0);
    while (room->pathway[i])
        i++;
    return (i);
}

t_room  **shortestPath(t_room ***pathToVictory)
{
    int j = 1;
    t_room  **shortest;

    shortest = pathToVictory[0];
    while (pathToVictory[j])
    {
        if (pathSize(shortest) > pathSize(pathToVictory[j]))
            shortest = pathToVictory[j];
        j++;
    }
    return (shortest);
}

void    freeVictory(t_room  ***pathToVictory)
{
    int  j = 0;
    while(pathToVictory[j])
    {
        if (pathToVictory[j])
        {
            free(pathToVictory[j]);
            pathToVictory[j] = NULL;
        }
       j++;
    }
    free(pathToVictory);
}

int culDeSacDeHobbit(t_room **pathToVictory, t_room *room, t_room *toWent)
{
    int i = 0;
    while (pathToVictory[i] != toWent)
    {
        if (pathToVictory[i] == room)
            return (-1);
        i++;
    }
    return (0);
}

void    printPath(t_room **path)
{
    int i = 0;

    if (!path)
        return ;
    if(path[0] == 0)
        return ;
    while (path[i])
    {
        ft_printf("room is %s\n", path[i]->room);
        i++;
    }
    ft_printf("---------------------------------------------------\n");
}

int    culDeSac(t_room **pathToVictory)
{
    int i = 0;
    if (!pathToVictory)
        return (-1);
    while (pathToVictory[i] != NULL)
        i++;
    if (i == 0)
        return (-1);
    if (pathToVictory[i - 1]->isEnd != 1)
        return (-1);
    return (0);
}

void    addPathToVictory(t_room *start, t_room **pathToCreate, t_room ***pathToVictory, int i, t_data *data)
{
    int j = 1;
    int k = 0;
    t_room *nextRoom = NULL;

    (void)pathToVictory;
    (void)i;
    pathToCreate[0] = data->start;
    pathToCreate[1] = start;

    while (pathToCreate[j] && pathToCreate[j]->isEnd != 1)
    {
        if (!pathToCreate[j]->pathway)
            return ;
        k = 0;
        while (pathToCreate[j]->pathway[k])
        {
            if (nextRoom == NULL || nextRoom->checkPath > pathToCreate[j]->pathway[k]->checkPath)
                nextRoom = pathToCreate[j]->pathway[k];
            k++;
        }
        j++;
        if (nextRoom == pathToCreate[j - 2])
            break ;
        pathToCreate[j] = nextRoom;
        nextRoom = NULL;
    }
}

void    addPathToVictoryReverse(t_room *start, t_room **pathToCreate, t_room ***pathToVictory, int i, t_data *data)
{
    int j = 1;
    int k = 0;
    t_room *nextRoom = NULL;

    (void)i;
    (void)pathToVictory;
    pathToCreate[0] = data->end;
    pathToCreate[1] = start;

    while (pathToCreate[j] && pathToCreate[j]->isStart != 1)
    {
        if (!pathToCreate[j]->pathway)
            return ;
        k = 0;
        while (pathToCreate[j]->pathway[k])
        {
            if (nextRoom == NULL || nextRoom->checkPath2 > pathToCreate[j]->pathway[k]->checkPath2)
                nextRoom = pathToCreate[j]->pathway[k];
            k++;
        }
        j++;
        if (nextRoom == pathToCreate[j - 2])
            break ;
        pathToCreate[j] = nextRoom;
        nextRoom = NULL;
    }
}

t_room *checkEnd(t_room **path)
{
    int i = 0;

    while (path[i])
        i++;
    if (i == 0)
        return (path[i]);
    return (path[i - 2]);
}

int    checkIfPurged(t_room **path, t_room *** newPath)
{
    int i = 1;

    if (DEBUG_PRINT)
        ft_printf("check if %s is purged : ", checkEnd(path)->room);

    while (newPath[i])
    {
        if (checkEnd(path) == checkEnd(newPath[i]))
        {
            if (DEBUG_PRINT)
                ft_printf("yes \n");
            return (-1);
        }
        i++;
    }
    if (DEBUG_PRINT)
        ft_printf("no \n");
    return (0);
}

t_room **purge(t_room *end, t_room ***pathToVictory, t_room **little)
{
    int i = 0;
    int j = 0;
    int shorterest = 0;
    t_room **bestest;

    while (pathToVictory[i])
    {
        if (checkEnd(pathToVictory[i]) == end)
        {
            j = pathSize(pathToVictory[i]);
            if (shorterest == 0 || shorterest > j)
            {
                if (pathToVictory[i] != little)
                {
                    bestest = pathToVictory[i];
                    shorterest = j;
                }
            }
        }
        i++;
    }
    return (bestest);
}

void    freeRandom(t_room ***newPath, t_room ***oldPath)
{
    int i = 0;
    int j = 0;
    int k = 0;

    while (oldPath[i])
    {
        while (newPath[j])
        {
            if (oldPath[i] == newPath[j])
            {
                k = 1;
                break ;
            }
            j++;
        }
        if (k != 1)
        {
            if (oldPath[i])
                free (oldPath[i]);
        }
        k = 0;
        j = 0;
        oldPath[i] = NULL;
        i++;
    }
}

int    purgePath(t_data *data, t_room ***pathToVictory)
{
    t_room  ***newPathToVictory;
    int j = 0;
    int i = 1;

    newPathToVictory = ft_calloc(numberOfPath(data->start) + 1, sizeof(t_room ***));
    if (!newPathToVictory)
        return (-1);
    newPathToVictory[0] = shortestPath(pathToVictory);
    while(pathToVictory[j])
    {
        while(pathToVictory[j] && (pathToVictory[j] == newPathToVictory[0] || checkIfPurged(pathToVictory[j],  newPathToVictory) == -1))
            j++;
        if (!pathToVictory[j])
            break ;
        if (DEBUG_PRINT)
            ft_printf("purging : %s\n", checkEnd(pathToVictory[j])->room);
        newPathToVictory[i] = purge(checkEnd(pathToVictory[j]), pathToVictory, newPathToVictory[0]);
        i++;
        j++;
    }
    freeRandom(newPathToVictory, pathToVictory);
    j = 0;
    while (newPathToVictory[j])
    {
        pathToVictory[j] = newPathToVictory[j];
        j++;
    }
    pathToVictory[j] = NULL;
    free(newPathToVictory);
    return (0);
}

int    allPossiblePath(t_data *data, t_room ***pathToVictory, t_room ***pathToVictoryReverse)
{
    int i = 0;
    t_room *start;

    while (data->start->pathway[i] != NULL)
    {
        start = data->start->pathway[i];
        addPathToVictory(start, pathToVictory[i], pathToVictory, i, data);
        i++;
    }

    if (purgePath(data, pathToVictory) == -1)
        return (-1);

    i = 0;
    while (data->end->pathway[i] != NULL)
    {
        start = data->end->pathway[i];
        addPathToVictoryReverse(start, pathToVictoryReverse[i], pathToVictoryReverse, i, data);
        i++;
    }
    if (purgePath(data, pathToVictoryReverse) == -1)
        return (-1);
    return (i);
}

int findOptimalMAx(t_data *data)
{
    int pathFromStart = 0;
    int pathFromEnd = 0;

    while(data->start->pathway[pathFromStart])
        pathFromStart++;
    while(data->end->pathway[pathFromEnd])
        pathFromEnd++;
    if (pathFromStart > pathFromEnd)
        return (pathFromEnd);
    return (pathFromStart);
}

int pathSize(t_room **path)
{
    int i = 0;

    while (path[i])
        i++;
    return (i);
}

int crossPath(t_room **path1, t_room **path2)
{
    int i = 1;
    int j = 1;

    if (!path1 || !path2)
        return (-1);
    while(path1[i])
    {
        j = 1;
        if (path1[i]->isEnd == 1)
            break ;
        while (path2[j])
        {
            if (path1[i] == path2[j])
                return(-1);
            j++;
        }
        i++;
    }
    return (0);
}

int suppressingUselessPath(int nbPath, int nbTotalPath, int **crossPathList, t_room  ***newPathToVictory, t_room  **untract_path, int optimalMax)
{
    int j = 0;
    int count = 0;
    int counInfo = 0;
    int countSoloPath = 0;
    (void) optimalMax;
    for (int i = 0; newPathToVictory[i]; i++)
    {
        if (newPathToVictory[i] != untract_path)
        {
            j = 0;
            count = 0;
            while (j < nbTotalPath)
            {
                if (j == crossPathList[i][count])
                    count++;
                j++;
            }
            if (nbTotalPath - (count - 1) < nbPath)
            {
                newPathToVictory[i] = untract_path;
                counInfo +=1;
            }
            else if (count - 1 == 0)
                countSoloPath+=1;
        }
    }
    if (DEBUG_PRINT)
        ft_printf("Removing %d path to continue\n", counInfo);
    if (countSoloPath < 2)
        return (0);
    return (countSoloPath - 2);
}

void orderPathToVictory(t_room ***pathToVictory, int *lenlist, int len)
{
    t_room **tempPath;
    int tempInt;

    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (lenlist[j] > lenlist[j + 1])
            {
                tempInt = lenlist[j];
                tempPath = pathToVictory[j];
                lenlist[j] = lenlist[j + 1];
                pathToVictory[j] = pathToVictory[j + 1];
                lenlist[j + 1] = tempInt;
                pathToVictory[j + 1] = tempPath;
            }
        }
    }
}

static void MallocDestroyer(t_data *data, t_room  ***pathToUse, t_room  ***pathTest, t_room  ***pathUse, t_room  ***newPathToVictory, int **intlist, int *lenlist, int **crossPathList,  t_room ***pathToVictory)
{
    if (intlist)
    {
        for (int i = 0; intlist[i]; i++)
            free(intlist[i]);
    }
    free(intlist);
    if (crossPathList)
    {
        for (int i = 0; crossPathList[i]; i++)
            free(crossPathList[i]);   
    }
    free(newPathToVictory);
    free(crossPathList);
    free(pathTest);
    free(pathUse);
    free(pathToUse);
    free(lenlist);
    freeVictory(pathToVictory);
    launch_fatal_error(NULL, data, -666);
}

void printPathLign(t_room **path)
{
	  int i = 0;
 
    if (!path)
		return ;
    if (path[0] == 0)
		return ;
	ft_printf("| ", path[i]->room);
    while (path[i])
    {
		if (!(path[i + 1]))
        	ft_printf("%s", path[i]->room);
		else
			ft_printf("%s -> ", path[i]->room);
        i++;
    }
    ft_printf(" |\n");
}

void chooseYourPath(t_data *data, t_room ***pathToVictory)
{
    int optimalMax = 0;
    int k = 2;
    int j = 0;
    t_room  ***pathToUse;
    t_room  ***pathTest;
    t_room  ***pathUse;
    t_room  ***newPathToVictory;
    t_room  untract_room;
    t_room  *untract_path = &untract_room;

    int **intlist;
    int *lenlist;
    int **crossPathList;
    int len_alloc = 0;
    while (pathToVictory[len_alloc])
    {
        len_alloc++;
    }
    newPathToVictory = ft_calloc(len_alloc + 1, sizeof(t_room ***));
    if (!newPathToVictory)
        MallocDestroyer(data, NULL, NULL, NULL, NULL, NULL, NULL, NULL, pathToVictory);
    len_alloc = 0;
    while (pathToVictory[len_alloc])
    {
        newPathToVictory[len_alloc] = pathToVictory[len_alloc];
        len_alloc++;
    }
    optimalMax = findOptimalMAx(data);
    pathToUse = ft_calloc(optimalMax + 2, sizeof(t_room ***));
    if (!pathToUse)
        MallocDestroyer(data, NULL, NULL, NULL, newPathToVictory, NULL, NULL, NULL, pathToVictory);
    pathTest = ft_calloc(optimalMax + 1, sizeof(t_room ***));
    if (!pathTest)
        MallocDestroyer(data, pathToUse, NULL, NULL, newPathToVictory, NULL, NULL, NULL, pathToVictory);
    pathUse = ft_calloc(optimalMax + 1, sizeof(t_room ***));
    if (!pathUse)
        MallocDestroyer(data, pathToUse, pathTest, NULL, newPathToVictory, NULL, NULL, NULL, pathToVictory);
    intlist = ft_calloc(optimalMax + 1, sizeof(int *));
    if (!intlist)
        MallocDestroyer(data, pathToUse, pathTest, pathUse, newPathToVictory, NULL, NULL, NULL, pathToVictory);
    lenlist = ft_calloc(len_alloc + 1, sizeof(int));
    if (!lenlist)
        MallocDestroyer(data, pathToUse, pathTest, pathUse, newPathToVictory, intlist, NULL, NULL, pathToVictory);
    for (int i = 0; i < optimalMax + 1; i++)
    {
        intlist[i] = ft_calloc(len_alloc + 1, sizeof(int));
        if (!intlist[i])
        MallocDestroyer(data, pathToUse, pathTest, pathUse, newPathToVictory, intlist, lenlist, NULL, pathToVictory);
    }
    for (int i = 0; i < len_alloc; i++)
    {
        lenlist[i] = pathSize(pathToVictory[i]);
    }
    
    pathToUse[0] = shortestPath(pathToVictory);


    if (DEBUG_PRINT)
    {
        ft_printf("All print find\n");
        j = 0;
        while (pathToVictory[j])
        {
            printPathLign(pathToVictory[j]);
            ft_printf("___________________________________________________________________________________________________________________________________\n");
            j++;
        }        
    }

    if (DEBUG_PRINT)
    {
        ft_printf("check for %d different path minimum\n", k);
        ft_printf("number max of path possible : %d\n", optimalMax);
        ft_printf("total number path : %d\n", len_alloc);
    }

    orderPathToVictory(newPathToVictory, lenlist, len_alloc);
    crossPathList = creatCrossPathList(newPathToVictory, len_alloc);
    if (!crossPathList)
        MallocDestroyer(data, pathToUse, pathTest, pathUse, newPathToVictory, intlist, lenlist, NULL, pathToVictory);
    k += suppressingUselessPath(k, len_alloc, crossPathList, newPathToVictory, &untract_path, optimalMax);
    if (newPathToVictory[1])
    {
        if (DEBUG_PRINT)
            ft_printf("check for %d different path minimum\n", k);
            
        findShortestAndUnique( newPathToVictory, pathTest, pathUse, k, 0, crossPathList, len_alloc, intlist, lenlist, 0, &untract_path);
        for (size_t i = 0; pathUse[i]; i++)
        {
            pathToUse[i + 1] = pathUse[i];
        }

    }
    else
    {
        if (DEBUG_PRINT)
            ft_printf("only one path existing\n");
        pathToUse[1] = pathToUse[0];
    }
    // finishAlgo(data, pathToUse);
    if (AntsSwitcher(data, pathToUse) == -1)
        MallocDestroyer(data, pathToUse, pathTest, pathUse, newPathToVictory, intlist, lenlist, crossPathList, pathToVictory);
    for (int i = 0; i < optimalMax + 1; i++)
        free(intlist[i]);
    free(intlist);
    for (int i = 0; crossPathList[i]; i++)
        free(crossPathList[i]); 
    free(newPathToVictory);
    free(crossPathList);
    free(pathTest);
    free(pathUse);
    free(pathToUse);
    free(lenlist);
}

int    putInOrder(t_room ***pathToVictoryReverse, int stop, int toMalloc)
{
    int i = 0;
    int j = 0;
    int k = 0;
    t_room **toReverse = NULL;
    while (i != stop)
    {
        j = 0;
        k = 0;
        toReverse = ft_calloc(toMalloc, sizeof(t_room **));
        if (!toReverse)
            return (-1);
        while(pathToVictoryReverse[i] && pathToVictoryReverse[i][k])
            k++;
        if (!pathToVictoryReverse[i])
        {
            free(toReverse);
            break;
        }
        k--;
        while(k >= 0)
        {
            toReverse[j] = pathToVictoryReverse[i][k];
            j++;
            k--;
        }
        free(pathToVictoryReverse[i]);
        pathToVictoryReverse[i] = toReverse;
        i++;
    }
    return (0);
}

int    checkDouble(t_room **path, t_room   ***lotOfPath)
{
    int i = 0;
    int j = 0;

    while (lotOfPath[i])
    {
        j = 0;
        while(path[j] && lotOfPath[i][j])
        {
            if (path[j] != lotOfPath[i][j])
                break ;
            j++;
        }
        if (path[j] == NULL && lotOfPath[i][j]== NULL)
        {
            return (-1);
        }
        i++;
    }
    return (0);
}

void    addShortestToPath(t_room ***truePath, t_room ***pathToVictory, t_room ***pathToVictoryReverse)
{
    int i = 0;
    int j = 0;
    int k = 0;

    while(pathToVictory[i])
    {
        j = 0;
        while (pathToVictory[i][j])
            j++;
        if (k == 0 || j < k)
            k = j;
        i++;
    }

    i = 0;
    j = 0;
    while(pathToVictoryReverse[i])
    {
        j = 0;
        while (pathToVictoryReverse[i][j])
            j++;
        if (k == 0 || j < k)
            k = j;
        i++;
    }

    i = 0;
    j = 0;
    while(pathToVictory[i])
    {
        if (pathSize(pathToVictory[i]) == k && checkDouble(pathToVictory[i], truePath) != -1)
        {
            truePath[j] = pathToVictory[i];
            j++;
        }
        i++;
    }

    i = 0;
    if (j != 0)
        j++;
    while(pathToVictoryReverse[i])
    {
        if (pathSize(pathToVictoryReverse[i]) == k && checkDouble(pathToVictoryReverse[i], truePath) != -1)
        {
            truePath[j] = pathToVictoryReverse[i];
            j++;
        }
        i++;
    }
}

void    purgeByFire(t_room ***truePath, t_room ***pathToVictory, t_room ***pathToVictoryReverse, t_data *data)
{
    int i = 0;
    int j = 0;
    while(pathToVictory[i] != NULL)
    {
        while (pathToVictory[i] && (culDeSac(pathToVictory[i]) == -1   || data->start != pathToVictory[i][0]))
        {
            i++;
        }
        if (pathToVictory[i] == NULL)
            break ;
        truePath[j] = pathToVictory[i];
        j++;
        i++;
    }

    i = 0;
    while(pathToVictoryReverse[i])
    {
        while (pathToVictoryReverse[i] && (culDeSac(pathToVictoryReverse[i]) == -1 || checkDouble(pathToVictoryReverse[i], pathToVictory) == -1 || data->start != pathToVictoryReverse[i][0]))
        {
            i++;
        }
        if (pathToVictoryReverse[i] == NULL)
            break ;
        truePath[j] = pathToVictoryReverse[i];
        j++;
        i++;
    }
    if (j == 0)
    {
        addShortestToPath(truePath, pathToVictory, pathToVictoryReverse);
    }
}

void    freeThePast(t_room ***path, int i)
{
    i--;
    while (i != 0)
    {
        free(path[i]);
        i--;
    }
    free(path);
}

void startAlgo(t_data *data)
{
    t_room  ***pathToVictory;
    t_room  ***pathToVictoryReverse;
    t_room  ***truePath;
    int     i = 0;
    int     j = 0;

    while (data->roomList[i] != NULL)
        i++;
    pathToVictory = ft_calloc(numberOfPath(data->start) + 1, sizeof(t_room ***));
    if (!pathToVictory)
        launch_fatal_error(NULL, data, -666);
    pathToVictoryReverse = ft_calloc(numberOfPath(data->end) + 1, sizeof(t_room ***));
    if (!pathToVictoryReverse)
    {
        free(pathToVictory);
        launch_fatal_error(NULL, data, -666);
    }
    truePath = ft_calloc(numberOfPath(data->end) + numberOfPath(data->start) + 1, sizeof(t_room ***));
    if (!truePath)
    {
        free(pathToVictory);
        free(pathToVictoryReverse);
        launch_fatal_error(NULL, data, -666);
    }
    while(j != numberOfPath(data->start))
    {
        pathToVictory[j] = ft_calloc(i + 1, sizeof(t_room **));
        if (!pathToVictory[j])
        {
            freeThePast(pathToVictory, j);
            free(truePath);
            launch_fatal_error(NULL, data, -666);
        }
        j++;
    }
    j = 0;
    while(j != numberOfPath(data->end))
    {
       pathToVictoryReverse[j] = ft_calloc(i + 1, sizeof(t_room **));
       if (!pathToVictoryReverse[j])
        {
            free(truePath);
            freeThePast(pathToVictory, numberOfPath(data->start) + 1);
            freeThePast(pathToVictoryReverse, j);
            launch_fatal_error(NULL, data, -666);
        }
       j++;
    }
    j = allPossiblePath(data, pathToVictory, pathToVictoryReverse);
    if (j == -1)
    {
        free(truePath);
        freeThePast(pathToVictory, numberOfPath(data->start) + 1);
        freeThePast(pathToVictoryReverse, numberOfPath(data->end) + 1);
        launch_fatal_error(NULL, data, -666);
    }
    if (putInOrder(pathToVictoryReverse, numberOfPath(data->end), i + 1) == -1)
    {

        free(truePath);
        freeThePast(pathToVictory, numberOfPath(data->start) + 1);
        freeThePast(pathToVictoryReverse, numberOfPath(data->end) + 1);
        launch_fatal_error(NULL, data, -666);
    }
    purgeByFire(truePath, pathToVictory, pathToVictoryReverse, data);
    chooseYourPath(data, truePath);
    free(truePath);
    freeVictory(pathToVictory);
    freeVictory(pathToVictoryReverse);
}
