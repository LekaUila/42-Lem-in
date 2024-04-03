/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_recurcive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:59:39 by lflandri          #+#    #+#             */
/*   Updated: 2024/04/03 15:43:42 by lflandri         ###   ########.fr       */
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
        // ft_printf("for path %d : \n", i);
        while (pathToVictory[j])
        {
            if (j == i)
            {
                crossPathList[i][k] = j;
                k++;
                // ft_printf("   path %d is same \n", j);
            }
            else if (crossPath(pathToVictory[i], pathToVictory[j]) == -1)
            {
                crossPathList[i][k] = j;
                k++;
                // ft_printf("   path %d is incompatible \n", j);

            }
            // else
            //     ft_printf("   path %d is compatible \n", j);
            j++;
        }
        crossPathList[i][k] = -1;
        i++;
    }
    return (crossPathList);
}

static int comboBetter(int lenPathTest, t_room ***listPathSuccess)
{
    static int len2 = -1;
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
    if (lenPathTest < len2)
    {
        len2 = lenPathTest;
        return (1);
    }
    return (0);
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

static void findShortestAndUniqueDepth( t_room ***pathToVictory, t_room ***listPathTest, t_room ***listPathSuccess, int optimalMax,  int dec, int **crossPathList, int len_alloc, int ** intlist, int ind, int * lenlist, int lenPathtest, t_room  **untract_path)
{
    int i = 0;
    int j = 0;
    // ft_printf("enter second at %d\n", dec);
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
    findShortestAndUnique( pathToVictory, listPathTest, listPathSuccess, optimalMax,  dec,crossPathList,   len_alloc,  intlist, lenlist, lenPathtest, untract_path);
    // ft_printf("exit second at %d\n", dec);
}

void findShortestAndUnique( t_room ***pathToVictory, t_room ***listPathTest, t_room ***listPathSuccess, int optimalMax,  int dec, int **crossPathList, int len_alloc, int ** intlist,int * lenlist, int lenPathtest, t_room  **untract_path)
{
    static int lenPathToVictory = 0;
    if (!lenPathToVictory)
        lenPathToVictory = listPathSize(pathToVictory);
    int i = dec;
    int j = 0;
    // ft_printf("enter first at %d\n", dec);
    while (pathToVictory[i])
    {
        if (/*!dec &&*/ lenPathToVictory - i + dec < optimalMax)
        {   
            // ft_printf("abort rec at : %d path, %d depth\n", i, dec);
            break;
        }
        else if ((!(intlist[dec][i])) && pathToVictory[i] != untract_path)
        {
            listPathTest[dec] = pathToVictory[i];
            if (dec + 1 < optimalMax)
            {
                findShortestAndUniqueDepth( pathToVictory, listPathTest, listPathSuccess, optimalMax,  dec + 1,crossPathList,   len_alloc,  intlist, i, lenlist, lenPathtest + lenlist[i], untract_path);
            }
            else
            {
                lenPathtest += lenlist[i];
                if (listPathSuccess[0] == NULL || comboBetter(lenPathtest, listPathSuccess))
                {
                    j = 0;
                    while (listPathTest[j])
                    {
                        listPathSuccess[j] = listPathTest[j];
                        j++;
                    }
                }
                lenPathtest -= lenlist[i];
            }
        }
        i++;
    }
    listPathTest[dec] = NULL;
    // ft_printf("exit first at %d\n", dec);
}