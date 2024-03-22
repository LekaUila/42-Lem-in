#include "header.h"

void    freeVictory(t_room  ***pathToVictory, int i)
{
    int  j = 0;
    while(j != i)
    {
       free(pathToVictory[j]);
       j++;
    }
    free(pathToVictory);
}

int culDeSacDeHobbit(t_room **pathToVictory, t_room *room, t_room *toWent)
{
    int i = 0;
    //ft_printf("towent = %s\nroom = %s\n", toWent->room, room->room);
    while (pathToVictory[i] != toWent)
    {
        if (pathToVictory[i] == room)
            return (-1);
        i++;
    }
    return (0);
}

int isRoomAlreadyInPath(t_room **pathToVictory, t_room *room, int tryCulDeSac, t_room *toWent)
{
    if (!room || !pathToVictory)
        return (-1);
    int j = 0;
    (void) toWent;

    while(pathToVictory[j] != toWent)
        j++;
    if (tryCulDeSac && pathToVictory[j + 1] != room && culDeSacDeHobbit(pathToVictory, room, toWent) == 0) //culDeSacDeHobbit(pathToVictory, room, toWent) == -1
        return (0);
    j = 0;
    while (pathToVictory[j] != NULL)
    {
        //ft_printf("pathToVictory[j] = %s\n room = %s\n", pathToVictory[j]->room, room->room);
        if (pathToVictory[j] == room)
        {
            //ft_printf("*************************************\n");
            return (-1);
        }
        j++;
    }
    //ft_printf("-------------------------------\n");
    return (0);
}

int pathSizeCalculator(t_room **pathToVictory)
{
    int j = 0;
    while (pathToVictory[j])
        j++;
    return (j);
}

int toMuch(t_data *data)
{
    int i = 0;

    while (data->start->pathway[i])
        i++;
    return (i - 1);
}

int specialCase(t_room    ***pathToVictory, int i)
{
    int k = 0;
    while (pathToVictory[i - 1][0]->pathway[k] != pathToVictory[i - 1][1])
        k++;
    k++;
    //ft_printf("special case : past room = %s\nactualroom : %s\n", pathToVictory[i - 1][1]->room, pathToVictory[i - 1][0]->pathway[k]->room);
    return (k);
}

int     checkSamePath(t_room **path, t_room** path2, t_room *room)
{
    int i = 0;

    if (room == path[0])
        return (-1);
    while (path[i] != room)
    {
        if (path2[i] == NULL)
            return (-1);
        if (path[i] != path2[i])
            return (-1);
        i++;
    }
    //ft_printf("end bl for room %s and test %s \n", room->room, path2[i]->room);
    if (path2[i] != room)
        return (-1);
    if (path[i + 1] == path2[i + 1])
        return (-1);
    //ft_printf("return 0\n");
    return (0);
}

int     checkOldPath(t_room ***pathToVictory, t_room *room, int i)
{
    int j = 2;
    int k = 0;
    int l = 1;
    int cpt = 1;

    //ft_printf("roomtest = %s\n", room->room);
    if (room == pathToVictory[i - 1][0])
        return (0);
    while(room->pathway && room->pathway[k])
        k++;
    if (k <= 2)
        return (1);
    //besoin de check si le chemin d'avant c'est le meme que celui la
    // j'essayre de faire une nouveau chemin a partir de room c chemin commence pareil que room -1
    while (i - j >= 0)
    {
        if (cpt >= k)
            return (-1);
        if (i - 1 < 0 || i - j < 0)
        {
            //ft_printf("j = %d\nk = %d\nl = %d\n", j, k, l);
            return (0);
        }
        if (checkSamePath(pathToVictory[i - 1], pathToVictory[i - j], room) == 0)       //si i - 1 = i - 2 c'est bon
            cpt = cpt + 1000;           //this got cancer maybe fix it if you have an error 99% chance it's here
        l++;
        j++;
    }
    //ft_printf("**************************************\n");
    //ft_printf("room = %s\n", room->room);
    //ft_printf("cpt = %d\nk = %d\nl = %d\n", cpt, k, l);
    if (cpt >= k)
        return (-1);
    return (0);
}

/*int    addPathToVictory(t_room *start, t_room **pathToCreate, t_room ***pathToVictory, int i, t_data *data)
{
    int j = 1;
    int k = 0;
    int stop = 0;
    int pathSize = 0;
    t_room *actualRoom;

    actualRoom = start;

    while(start->isEnd != 1 && stop != 1)
    {
        if (i == 0)
        {
            pathToCreate[0] = start;
            //ft_printf("actual room : %s\n", actualRoom->room);
            if (actualRoom->pathway && actualRoom->isEnd != 1)
            {
                k = 0;
                while (actualRoom->pathway[k])
                {
                    if (actualRoom->pathway[k]->isEnd == 1)
                    {
                        break ;
                    }
                    k++;
                }
                if (actualRoom->pathway[k] == NULL)
                {
                    k = 0;
                    while (actualRoom->pathway[k] && isRoomAlreadyInPath(pathToCreate, actualRoom->pathway[k], 0, NULL) != 0)
                        k++;
                }
                if (actualRoom->pathway[k] == NULL)
                {
                    stop = 1;
                    pathToCreate[j] = NULL;
                }
                else
                {
                    pathToCreate[j] = actualRoom->pathway[k];
                    actualRoom = actualRoom->pathway[k];
                }
            }
            else
            {
                stop = 1;
                pathToCreate[j] = NULL;
            }
        }
        else
        {
            pathSize = pathSizeCalculator(pathToVictory[i - 1]) - 1;            // - qqc a modulés
            while (pathSize > -1)
            {
                //ft_printf("pathsize = %d\n", pathSize);
                if (pathToVictory[i - 1][pathSize]->isStart == 1)
                {
                    data->stopTheCount++;
                    //ft_printf("data = %d\nto much = %d\n", data->stopTheCount, toMuch(data));
                    if (data->stopTheCount > toMuch(data))
                    {
                        pathToCreate[0] = 0;
                        //ft_printf("test", data->stopTheCount, toMuch(data));
                        return (-1);
                    }
                }
                if (checkOldPath(pathToVictory, pathToVictory[i - 1][pathSize], i) == 0)
                {
                    pathToCreate[0] = start;
                    k = 0;
                    // si le chemin a + de 2 option il faut que je check si ce chemin la on pas déja été crée tous car je regarde que le chemin d'avant ce qui peut etre une erreur
                    //ft_printf("actual room is : %s\n", pathToVictory[i - 1][pathSize]->room, j);
                    //ft_printf("---------------------------\n");
                    while (actualRoom->pathway[k])
                    {
                        if (actualRoom->pathway[k]->isEnd == 1)
                        {
                            break ;
                        }
                        k++;
                    }
                    if (actualRoom->pathway[k] == NULL)
                    {
                        while (pathToVictory[i - 1][pathSize]->isEnd != 1 && pathToVictory[i - 1][pathSize]->pathway && pathToVictory[i - 1][pathSize]->pathway[k] && isRoomAlreadyInPath(pathToVictory[i - 1], pathToVictory[i - 1][pathSize]->pathway[k], 1, pathToVictory[i - 1][pathSize]))
                        {
                            k++;
                        }
                    }
                    if (pathToVictory[i - 1][pathSize]->isStart == 1 )//&& pathToVictory[i - 1][pathSize]->pathway[k] == NULL)
                        k = specialCase(pathToVictory, i);
                    if (pathToVictory[i - 1][pathSize]->isEnd != 1 && pathToVictory[i - 1][pathSize]->pathway[k] != NULL)
                    {
                        j = 0;
                        //ft_printf("new path found at room : %s\n", pathToVictory[i - 1][pathSize]->room, j);
                        while (j != pathSize + 1)
                        {
                            //ft_printf("room added is %s at %d\n", pathToVictory[i - 1][j]->room, j);
                            pathToCreate[j] = pathToVictory[i - 1][j];
                            j++;
                        }
                        //ft_printf("new room added is %s at %d\n", pathToVictory[i - 1][pathSize]->pathway[k]->room, j);
                        pathToCreate[j] = pathToVictory[i - 1][pathSize]->pathway[k];
                        actualRoom = pathToCreate[j];
                        i = 0;
                        break ;
                    }
                }
                pathSize--;
            }
            // j'ai besoin de 2 truc 1 un vrai détection de fin est un meilleur code
        }
        j++;
    }
    return (0);
}*/

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

    (void)i;
    (void)pathToVictory;
    pathToCreate[0] = data->start;
    pathToCreate[1] = start;

    while (pathToCreate[j]->isEnd != 1)
    {
        if (!pathToCreate[j]->pathway)
            return ;
        k = 0;
        while (pathToCreate[j]->pathway[k])
        {
            if (nextRoom == NULL || nextRoom->checkPath < pathToCreate[j]->pathway[k]->checkPath)
                nextRoom = pathToCreate[j]->pathway[k];
            k++;
        }
        j++;
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

    while (pathToCreate[j]->isStart != 1)
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
        pathToCreate[j] = nextRoom;
        nextRoom = NULL;
    }
}

int    allPossiblePath(t_data *data, t_room ***pathToVictory)
{
    int i = 0;
    t_room *start;

    while (data->start->pathway[i] != NULL)
    {
        start = data->start->pathway[i];
        //ft_printf("i = %d\n", i);
        addPathToVictory(start, pathToVictory[i], pathToVictory, i, data);
        printPath(pathToVictory[i]);
        i++;
    }
    i--;
    /*while (i > -1)
    {
        start = data->start->pathway[i];
        //ft_printf("i = %d\n", i);
        addPathToVictory(start, pathToVictory[i], pathToVictory, i, data);
        printPath(pathToVictory[i]);
        i--;
    }*/

    i = 0;
    while (data->end->pathway[i] != NULL)
    {
        start = data->end->pathway[i];
        //ft_printf("i = %d\n", i);
        addPathToVictoryReverse(start, pathToVictory[i], pathToVictory, i, data);
        printPath(pathToVictory[i]);
        i++;
    }
   /* i--;
    while (i > -1)
    {
        start = data->end->pathway[i];
        //ft_printf("i = %d\n", i);
        addPathToVictoryReverse(start, pathToVictory[i], pathToVictory, i, data);
        printPath(pathToVictory[i]);
        i--;
    }*/
    ft_printf("number of path : %d\n", i);
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

int listPathSize(t_room ***path)
{
    int i = 0;

    while (path[i])
        i++;
    return (i);
}

t_room  **shortestPath(t_room ***pathToVictory, int i)
{
    int j = 1;
    t_room  **shortest;

    shortest = pathToVictory[0];
    while (j != i - 1)
    {
        if (culDeSac(pathToVictory[j]) != -1)
        {
            if (pathSize(shortest) > pathSize(pathToVictory[j]))
                shortest = pathToVictory[j];
        }
        j++;
    }
    return (shortest);
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

/*t_room  **findXShortest(t_room ***pathToVictory, int x)
{
    int i = 1;
    int j = 0;
    int k = 0;

    while (pathToVictory[i])
    {
        j = 0;
        k = 0;
        while (pathToVictory[j])
        {
            if (pathSize(pathToVictory[i]) <= pathSize(pathToVictory[j]))
                k++;
            j++;
        }
        j--;
        if (j - x = k)
            return (pathToVictory[i]);
        i++;
    }
}*/

int comboBetter(t_room ***listPathTest, t_room ***listPathSuccess)
{
    int len1 = 0;
    int len2 = 0;
    int i = 0;

    while (listPathTest[i])
    {
        len1+=pathSize(listPathTest[i]);
        i++;
    }
    while (listPathSuccess[i])
    {
        len2+=pathSize(listPathSuccess[i]);
        i++;
    }
    return (len1 < len2);
}

int isCompatible(t_room ***listPathTest)
{
    int i = 0;
    int j = 0;
    while (listPathTest[i])
    {
        j = i + 1;
        while (listPathTest[j])
        {
            if (j != i)
            {
                if (crossPath(listPathTest[i], listPathTest[j]))
                    return (0);
            }
            j++;
        }
        i++;
    }
    return (2);
}

void findShortestAndUnique( t_room ***pathToVictory, t_room ***listPathTest, t_room ***listPathSuccess, int optimalMax, int maxlen, int dec)
{
    int savelen = listPathSize(listPathTest);
    int i = dec;
    int j = 0;
    
    while (i < maxlen - 1)
    {
        // for (int i = 0; i < savelen; i++)
        // {
        //     write(1, " ", 1);
        // }
        // ft_printf("%i\n", i);

        if (!culDeSac(pathToVictory[i]))
        {
            listPathTest[savelen] = pathToVictory[i];
            if (savelen + 1 < optimalMax && isCompatible(listPathTest))
            {
                findShortestAndUnique( pathToVictory, listPathTest, listPathSuccess, optimalMax, maxlen, dec + 1);
            }
            else
            {
                if (listPathSuccess[0] == NULL && isCompatible(listPathTest))
                {
                    j = 0;
                    while (listPathTest[j])
                    {
                        listPathSuccess[j] = listPathTest[j];
                        j++;
                    }
                }
                else if (comboBetter(listPathTest, listPathSuccess) && isCompatible(listPathTest))
                {
                    j = 0;
                    while (listPathTest[j])
                    {
                        listPathSuccess[j] = listPathTest[j];
                        j++;
                    }
                }
            }
        }
        i++;
    }
    listPathTest[savelen] = NULL;
}

void    finishAlgo(t_data *data, t_room ***pathToUse)
{
    (void)data;
    (void)pathToUse;
}

void chooseYourPath(t_data *data, t_room ***pathToVictory, int i)
{
    int optimalMax = 0;
    int j = 1;
    int k = 2;
    // int maxPathPossible;
    t_room  ***pathToUse;
    t_room  ***pathTest;

    optimalMax = findOptimalMAx(data);
    // maxPathPossible = optimalMax;
    // ft_printf("optimalMax = %d\n", optimalMax);
    pathToUse = ft_calloc(optimalMax + 2, sizeof(t_room ***));
    pathTest = ft_calloc(optimalMax + 1, sizeof(t_room ***));
    pathToUse[0] = shortestPath(pathToVictory, i);

    ft_printf("the shortest path is :\n");
    printPath(pathToUse[0]);
    while (k <= optimalMax)
    {
        findShortestAndUnique( pathToVictory, pathTest, pathToUse + 1, k, i, 0);
        if (!pathToUse[k])
            break;
        k++;
    }

    ft_printf("optimal number of path is %d\nPath are :\n", optimalMax);
    while (pathToUse[j])
    {
        printPath(pathToUse[j]);
        j++;
    }
    finishAlgo(data, pathToUse);
    //need to find the shortest nomber of optimalMax of path that do not share the same room
    free(pathTest);
    free(pathToUse);
}

void startAlgo(t_data *data)
{
    t_room  ***pathToVictory;
    int     i = 0;
    int     j = 0;

    while (data->roomList[i] != NULL)
        i++;
    pathToVictory = ft_calloc(i * 100, sizeof(t_room ***));
    while(j != i * 100)
    {
       pathToVictory[j] = ft_calloc(i + 1, sizeof(t_room **));
       j++;
    }
    j = allPossiblePath(data, pathToVictory);
    //chooseYourPath(data, pathToVictory, j);
    freeVictory(pathToVictory, i * 100);
}
