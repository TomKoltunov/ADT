// I have used the solution for the first test in the previous semester in the course "Software Systems A". Actually the whole core
// functionality was already satisfied there so the most of what I did was to add and adapt to the current task. The core functionality 
// has been given in the next link: "https://moodlearn.ariel.ac.il/course/view.php?id=101828" (there the solution to the relevant exam)
// is under the name 'moed-a-sol'.

#include "AdptArray.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct AdptArray_
{
	int ArrSize;
	PElement* pElemArr;
	DEL_FUNC delFunc;
	COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray, *PAdptArray;

PAdptArray CreateAdptArray(COPY_FUNC copyFunc_, DEL_FUNC delFunc_, PRINT_FUNC printFunc)
{
	PAdptArray pArr = (PAdptArray)malloc(sizeof(AdptArray));
	if (pArr == NULL)
		return NULL;
	pArr->ArrSize = 0;
	pArr->pElemArr = NULL;
	pArr->delFunc = delFunc_;
	pArr->copyFunc = copyFunc_;
    pArr->printFunc = printFunc;
	return pArr;
}

Result SetAdptArrayAt(PAdptArray pArr, int idx, PElement pNewElem)
{
	PElement* newpElemArr;
	if (pArr == NULL)
		return FAIL;

	if (idx >= pArr->ArrSize)
	{
		if ((newpElemArr = (PElement*)calloc((idx + 1), sizeof(PElement))) == NULL)
			return FAIL;
		memcpy(newpElemArr, pArr->pElemArr, (pArr->ArrSize) * sizeof(PElement));
        if(pArr->pElemArr != NULL) // Without this check we'll receive a Segmentation fault (core dumped)
        {
            free(pArr->pElemArr);
        }
		pArr->pElemArr = newpElemArr;
	}
    if(pArr->pElemArr[idx] != NULL) // Without this check we'll receive a Segmentation fault (core dumped)
    {
        pArr->delFunc((pArr->pElemArr)[idx]);
    }
	(pArr->pElemArr)[idx] = pArr->copyFunc(pNewElem);
	pArr->ArrSize = (idx >= pArr->ArrSize) ? (idx + 1) : pArr->ArrSize;
	return SUCCESS;
}

void DeleteAdptArray(PAdptArray pArr)
{
	int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
        if(pArr->pElemArr[i] != NULL) // Without this check we'll receive a Segmentation fault (core dumped)
        {
            pArr->delFunc((pArr->pElemArr)[i]);
        }
	}
	free(pArr->pElemArr);
	free(pArr);
}

PElement GetAdptArrayAt(PAdptArray pArr, int idx) 
{
    if (pArr->pElemArr[idx] == NULL || idx >= pArr->ArrSize)
    {
        return NULL;
    }
    return pArr->copyFunc((pArr->pElemArr)[idx]);
}

int GetAdptArraySize(PAdptArray pArr)
{
    return pArr->ArrSize;
}

void PrintDB(PAdptArray pArr)
{
    int i;
	if (pArr == NULL)
		return;
	for(i = 0; i < pArr->ArrSize; ++i)
	{
		if (pArr->pElemArr[i] != NULL)
        {
            pArr->printFunc(pArr->pElemArr[i]);
        }
	}
}