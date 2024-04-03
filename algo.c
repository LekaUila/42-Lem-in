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
    //ft_printf("---------------------------------------------------\n");
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
            if (nextRoom == NULL || nextRoom->checkPath > pathToCreate[j]->pathway[k]->checkPath)
                nextRoom = pathToCreate[j]->pathway[k];
            k++;
        }
        j++;
        pathToCreate[j] = nextRoom;
        //ft_printf("pathToCreate[j]->room = %s\n", pathToCreate[j]->room);
        //ft_printf("checpath = %d\n", pathToCreate[j]->checkPath2);
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
            if (nextRoom == NULL || nextRoom->checkPath2 > pathToCreate[j]->pathway[k]->checkPath2)
                nextRoom = pathToCreate[j]->pathway[k];
            k++;
        }
        j++;
        pathToCreate[j] = nextRoom;
        //ft_printf("pathToCreate[j]->room = %s\n", pathToCreate[j]->room);
        nextRoom = NULL;
    }
}

int    allPossiblePath(t_data *data, t_room ***pathToVictory, t_room ***pathToVictoryReverse)
{
    int i = 0;
    t_room *start;

    while (data->start->pathway[i] != NULL)
    {
        start = data->start->pathway[i];
        //ft_printf("starting direction = %s\n", start->room);
        //ft_printf("i = %d\n", i);
        addPathToVictory(start, pathToVictory[i], pathToVictory, i, data);
        //printPath(pathToVictory[i]);
        i++;
    }
    i--;

    i = 0;
    while (data->end->pathway[i] != NULL)
    {
        start = data->end->pathway[i];
        //ft_printf("starting direction = %s\n", start->room);
        //ft_printf("i = %d\n", i);
        addPathToVictoryReverse(start, pathToVictoryReverse[i], pathToVictoryReverse, i, data);
        //printPath(pathToVictoryReverse[i]);
        i++;
    }
    //ft_printf("number of path : %d\n", i);
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
    // ft_printf("try better for \n");
    while (listPathTest[i])
    {
        // printPath(listPathTest[i]);
        len1+=pathSize(listPathTest[i]);
        i++;
    }
    // ft_printf("and success for \n");
	i = 0;
    while (listPathSuccess[i])
    {
        // printPath(listPathSuccess[i]);
        len2+=pathSize(listPathSuccess[i]);
        i++;
    }
    return (len1 < len2);
}

// void printPathLign(t_room **path)
// {
// 	  int i = 0;

//     if (!path)
// 		return ;
//     if (path[0] == 0)
// 		return ;
// 	ft_printf("| ", path[i]->room);
//     while (path[i])
//     {
// 		if (!(path[i + 1]))
//         	ft_printf("%s", path[i]->room);
// 		else
// 			ft_printf("%s -> ", path[i]->room);
//         i++;
//     }
//     ft_printf(" |\n");
// }

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

void findShortestAndUnique( t_room ***pathToVictory, t_room ***listPathTest, t_room ***listPathSuccess, int optimalMax,  int dec)
{
    int savelen = listPathSize(listPathTest);
    int i = dec;
    int j = 0;
    while (pathToVictory[i])
    {

        if (!culDeSac(pathToVictory[i]))
        {
            listPathTest[savelen] = pathToVictory[i];
            if (savelen + 1 < optimalMax && isCompatible(listPathTest))
            {
                findShortestAndUnique( pathToVictory, listPathTest, listPathSuccess, optimalMax,  dec + 0);
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

void    sendAntsInPath(t_data *data, t_room **pathToUse)
{
    int i = 0;
    while (data->ants[i].number != -1 && data->ants[i].path != NULL)
        i++;
    //ft_printf("i = %d\n", i);
    if (data->ants[i].number != -1)
    {
        data->ants[i].path = pathToUse;
        data->ants[i].room = 0;
    }
}

int    mooveAnts(t_trueAnt *ant, t_data *data)
{
    if (ant->path[ant->room]->isEnd == 1)
        return (-1);
    if (ant->path[ant->room + 1]->ants != 0 && ant->path[ant->room + 1]->isEnd != 1)
        return (-1);
    AMI_addAntsMovement(data, ant->path[ant->room], ant->path[ant->room + 1]);
    ant->path[ant->room]->ants--;
    ant->room = ant->room + 1;
    ft_printf("L%d-%s", ant->number, ant->path[ant->room]->room);
    ant->path[ant->room]->ants++;
    return (0);
}

void    finishAlgo(t_data *data, t_room ***pathToUse)
{
    int i = 0;
    int space = 42;
    
    if (!pathToUse)
        return ;
    while (data->end->ants != data->total_ants)
    {
        i = 0;

        if (space != 42)
        {
            AMI_addNewStep(data);
            AMI_setNumberOfAntsForEnd(data, data->end->ants);
        }
        while(data->ants[i].number != -1 && data->ants[i].path)
        {
            space = mooveAnts(&data->ants[i], data);
            if (space == 0 && data->ants[i + 1].path != NULL)
                ft_printf(" ");
            i++;
            //if (!data->ants[i + 1].path)
        }
        if (space != 42)
        {  
            AMI_setNumberOfAntsForStart(data, data->start->ants);
        }
        space = 43;

        i = 1;
        if (pathToUse[i] == NULL)
        {
            sendAntsInPath(data, pathToUse[0]);
        }
        else
        {
            while (pathToUse[i] != NULL)
            {
                if (data->start->ants == 0)
                    break ;
                if (pathSize(pathToUse[i]) - 1 < data->start->ants + pathSize(pathToUse[0])) // is gabarge its data->start->ants + shortest path
                    sendAntsInPath(data, pathToUse[i]);
                else
                {
                    sendAntsInPath(data, pathToUse[0]);
                }
                i++;
            }
        }
        i = 0;
        ft_printf("\n");

        //ft_printf("ants in final room = %d\n", data->end->ants);
        //ft_printf("ants in starting room = %d\n", data->start->ants);
        //ft_printf("ants total = %d\n", data->total_ants);
    }
}

void chooseYourPath(t_data *data, t_room ***pathToVictory)
{
    int optimalMax = 0;
    int j = 1;
    int k = 2;
    // int maxPathPossible;
    t_room  ***pathToUse;
    t_room  ***pathTest;
    t_room  ***pathUse;


    optimalMax = findOptimalMAx(data);
    // maxPathPossible = optimalMax;
    // ft_printf("optimalMax = %d\n", optimalMax);
    pathToUse = ft_calloc(optimalMax + 2, sizeof(t_room ***));
    pathTest = ft_calloc(optimalMax + 1, sizeof(t_room ***));
    pathUse = ft_calloc(optimalMax + 1, sizeof(t_room ***));
    pathToUse[0] = shortestPath(pathToVictory);

    ft_printf("All print find\n");
    j = 0;
    while (pathToVictory[j])
    {
        printPath(pathToVictory[j]);
        j++;
    }
    ft_printf("%d\n", optimalMax);
    if (pathToVictory[1])
    {
        while (k <= optimalMax)
        {
            //ft_printf("check for %d different path\n", k);
            findShortestAndUnique( pathToVictory, pathTest, pathUse, k, 0);
            for (size_t i = 0; pathUse[i]; i++)
            {
                pathToUse[i + 1] = pathUse[i];
            }
            
            for (int i = 0; i < optimalMax; i++)
            {
                pathTest[i] = NULL;
                pathUse[i] = NULL;

            }
            if (!pathToUse[k])
                break;
            //ft_printf("path list find for %d different path\n", k);
            k++;
        }
    }
    else
    {
        ft_printf("only one path existing\n");
        pathToUse[1] = pathToUse[0];
    }

    ft_printf("optimal paths are :\n" );
    j = 0;
    while (pathToUse[j])
    {
        printPath(pathToUse[j]);
        j++;
    }
    finishAlgo(data, pathToUse);
    //need to find the shortest nomber of optimalMax of path that do not share the same room
    free(pathTest);
    free(pathUse);
    free(pathToUse);
}

int numberOfPath(t_room *room)
{
    int i = 0;

    if (!room->pathway)
        return (0);
    while (room->pathway[i])
        i++;
    return (i);
}

void    putInOrder(t_room ***pathToVictoryReverse, int stop, int toMalloc)
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
        //printPath(pathToVictoryReverse[i]);
        while(pathToVictoryReverse[i][k])
            k++;
        k--;
        while(k >= 0)
        {
            toReverse[j] = pathToVictoryReverse[i][k];
            j++;
            k--;
        }
        free(pathToVictoryReverse[i]);
        pathToVictoryReverse[i] = toReverse;
        //printPath(pathToVictoryReverse[i]);
        i++;
    }
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

int pathToBig(t_room **path, int ants)
{
    int i = 0;

    if (!path)
        return (-1);
    // ft_printf("try pathtobig for :\n");
    // printPath(path);
    // ft_printf("_____________________________________\n");
    while (path[i])
        i++;
    if (i > ants)
        return (-1);
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
        while (pathToVictory[i] && (culDeSac(pathToVictory[i]) == -1 || pathToBig(pathToVictory[i], data->total_ants) == -1))
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
    ft_printf("\n\n\n");
    while(pathToVictoryReverse[i])
    {
        while (pathToVictoryReverse[i] && (culDeSac(pathToVictoryReverse[i]) == -1 || checkDouble(pathToVictoryReverse[i], pathToVictory) == -1 || pathToBig(pathToVictoryReverse[i], data->total_ants) == -1))
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
    pathToVictoryReverse = ft_calloc(numberOfPath(data->end) + 1, sizeof(t_room ***));
    ft_printf("nb path data start : %d\n", numberOfPath(data->start));
    ft_printf("nb path data end : %d\n", numberOfPath(data->end));
    truePath = ft_calloc(numberOfPath(data->end) + numberOfPath(data->start) + 1, sizeof(t_room ***));
    while(j != numberOfPath(data->start))
    {
       pathToVictory[j] = ft_calloc(i + 1, sizeof(t_room **));
       j++;
    }
    j = 0;
    while(j != numberOfPath(data->end))
    {
       pathToVictoryReverse[j] = ft_calloc(i + 1, sizeof(t_room **));
       j++;
    }
    j = allPossiblePath(data, pathToVictory, pathToVictoryReverse);
    putInOrder(pathToVictoryReverse, numberOfPath(data->end), i + 1);
    purgeByFire(truePath, pathToVictory, pathToVictoryReverse, data);
    i = 0;
    while (truePath[i] != NULL)
    {
        printPath(truePath[i]);
        i++;
    }
    chooseYourPath(data, truePath);
    free(truePath);
    freeVictory(pathToVictory, numberOfPath(data->start) + 1);
    freeVictory(pathToVictoryReverse, numberOfPath(data->end) + 1);
}
