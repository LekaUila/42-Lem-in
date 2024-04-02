/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_recurcive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:59:39 by lflandri          #+#    #+#             */
/*   Updated: 2024/04/02 18:18:28 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

static int listPathSize(t_room ***path)
{
    int i = 0;

    while (path[i])
        i++;
    return (i);
}

int **creatCrossPathList(t_room ***pathToVictory, int len_alloc)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int **crossPathList;

    crossPathList = ft_calloc(len_alloc, sizeof(int *));
    while (pathToVictory[i])
    {
        crossPathList[i] = ft_calloc(len_alloc + 1, sizeof(int));
        j = 0;
        k = 0;
        while (pathToVictory[j])
        {
            if (j == i)
            {
                crossPathList[i][k] = j;
                k++;
            }
            else if (crossPath(pathToVictory[i], pathToVictory[j]) == -1)
            {
                crossPathList[i][k] = j;
                k++;
            }
            j++;
        }
        crossPathList[i][k] = -1;
        i++;
    }
    return (crossPathList);
}
//TODO : try to precalcul thing to be faster
static int comboBetter(t_room ***listPathTest, t_room ***listPathSuccess)
{
    static int len2 = -1;
    int len1 = 0;
    int i = 0;
    if (len2 == -1)
    {
        i = 0;
        len2 = 0;
        while (listPathSuccess[i])
        {
            len2+=pathSize(listPathSuccess[i]);
            i++;
        }  
    }
    i = 0;
    while (listPathTest[i])
    {
        len1+=pathSize(listPathTest[i]);
        i++;
    }
    if (len1 < len2)
    {
        len2 = len1;
        return (1);
    }
    return (0);
    // (void) listPathTest;
    // (void) listPathSuccess;
    // return (1);

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

static void findShortestAndUniqueDepth( t_room ***pathToVictory, t_room ***listPathTest, t_room ***listPathSuccess, int optimalMax,  int dec, int **crossPathList, int len_alloc, int ** intlist, int ind)
{
    //TODO : corectly implement that
    // int *newIntlist = ft_calloc(len_alloc, sizeof(t_room ***));
    int i = 0;
    int j = 0;
    while (i < len_alloc)
    {
        if (i == crossPathList[ind][j])
        {
            intlist[dec][i] = 1;
            j++;
        }
        else
        {
            intlist[dec][i] = intlist[dec - 1][i];
        }
        i++;
    }
    findShortestAndUnique( pathToVictory, listPathTest, listPathSuccess, optimalMax,  dec,crossPathList,   len_alloc,  intlist);
    // free(newIntlist);
}

void findShortestAndUnique( t_room ***pathToVictory, t_room ***listPathTest, t_room ***listPathSuccess, int optimalMax,  int dec, int **crossPathList, int len_alloc, int ** intlist)
{
    static int lenPathToVictory = 0;
    if (!lenPathToVictory)
        lenPathToVictory = listPathSize(pathToVictory);
    // int lenPathToVictory = listPathSize(pathToVictory);
    // int savelen = listPathSize(listPathTest);
    int i = dec;
    int j = 0;
    while (pathToVictory[i])
    {
        if (!dec && lenPathToVictory - i < optimalMax)
        {   
            ft_printf("abort rec at : %d path\n", i);
            break;
        }
        if (!(intlist[dec][i]))
        {
            listPathTest[dec] = pathToVictory[i];
            if (dec + 1 < optimalMax)
            {
                findShortestAndUniqueDepth( pathToVictory, listPathTest, listPathSuccess, optimalMax,  dec + 1,crossPathList,   len_alloc,  intlist, i);
            }
            else
            {
                if (listPathSuccess[0] == NULL)
                {
                    j = 0;
                    while (listPathTest[j])
                    {
                        listPathSuccess[j] = listPathTest[j];
                        j++;
                    }
                }
                else if (comboBetter(listPathTest, listPathSuccess))
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
    listPathTest[dec] = NULL;
}