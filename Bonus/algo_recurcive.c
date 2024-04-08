/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_recurcive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lflandri <liam.flandrinck.58@gmail.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 14:59:39 by lflandri          #+#    #+#             */
/*   Updated: 2024/04/08 15:06:45 by lflandri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int **creatCrossPathList(t_room ***pathToVictory, int len_alloc)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int **crossPathList;

    crossPathList = ft_calloc(len_alloc + 1, sizeof(int *));
    if (!crossPathList)
        return (NULL);
    while (pathToVictory[i])
    {
        crossPathList[i] = ft_calloc(len_alloc + 1, sizeof(int));
        if (!crossPathList[i])
        {
            for (int h = 0; crossPathList[h]; h++)
            {
                free(crossPathList[h]);
            }         
            free(crossPathList);
            return (NULL);
        }
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

static int comboBetter(int lenPathTest, t_room ***listPathSuccess)
{
    static int len2 = -1;
    int i = 0;
    if (!listPathSuccess) //force set case
    {
        len2 = lenPathTest;
        return (0);
    }
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

static void findShortestAndUniqueDepth( t_room ***pathToVictory, t_room ***listPathTest, t_room ***listPathSuccess, int optimalMax,  int dec, int **crossPathList, int len_alloc, int ** intlist, int ind, int * lenlist, int lenPathtest, t_room  **untract_path)
{
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
    findShortestAndUnique( pathToVictory, listPathTest, listPathSuccess, optimalMax,  dec,crossPathList,   len_alloc,  intlist, lenlist, lenPathtest, untract_path);
}

void findShortestAndUnique( t_room ***pathToVictory, t_room ***listPathTest, t_room ***listPathSuccess, int optimalMax,  int dec, int **crossPathList, int len_alloc, int ** intlist,int * lenlist, int lenPathtest, t_room  **untract_path)
{
    static int tempcountwrite = 0;
    static  int maxToReatch = -1;
    if (maxToReatch == -1)
        maxToReatch = optimalMax;
    int i = dec;
    int j = 0;
    while (pathToVictory[i])
    {
        if (len_alloc - i + dec < maxToReatch)
        {   
            break;
        }
        else if ((!(intlist[dec][i])) && pathToVictory[i] != untract_path)
        {
            listPathTest[dec] = pathToVictory[i];
                findShortestAndUniqueDepth( pathToVictory, listPathTest, listPathSuccess, maxToReatch,  dec + 1,crossPathList,   len_alloc,  intlist, i, lenlist, lenPathtest + lenlist[i], untract_path);
            if (dec + 1 == maxToReatch)
            {
                lenPathtest += lenlist[i];
                if (listPathSuccess[0] == NULL || comboBetter(lenPathtest, listPathSuccess))
                {
                    tempcountwrite++;
                    if (DEBUG_PRINT)
                        ft_printf("write on : %d\n", tempcountwrite);
                    j = 0;
                    while (listPathTest[j])
                    {
                        listPathSuccess[j] = listPathTest[j];
                        j++;
                    }
                }
                lenPathtest -= lenlist[i];
            }
            else if (dec + 1 > maxToReatch)
            {
                if (DEBUG_PRINT)
                    ft_printf("new max to reach : %d to %d \n", maxToReatch, dec + 1);
                tempcountwrite++;
                if (DEBUG_PRINT)
                    ft_printf("write on : %d\n", tempcountwrite);
                maxToReatch = dec + 1;
                comboBetter(lenPathtest + lenlist[i], NULL);
                j = 0;
                while (listPathTest[j])
                {
                    listPathSuccess[j] = listPathTest[j];
                    j++;
                } 
            }
        }
        i++;
    }
    listPathTest[dec] = NULL;
}