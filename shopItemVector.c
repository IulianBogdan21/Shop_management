#include "shopItemVector.h"
#include "constants.h"
#include <string.h>

// Resizes the vector by RESIZE_FACTOR
// Pre: vectorPointer must be a valid pointer to a vector instance
// Post: the capacity will increase by RESIZE_FACTOR
void resizeVector(vector* vectorPointer)
{
	// we increase the capacity
	ElementType* newDataBlock = malloc(RESIZE_FACTOR* vectorPointer->capacity * sizeof(ElementType));
	// we copy the items from the old block into the new one
	memcpy(newDataBlock, vectorPointer->pointerToDataBlock, sizeof(ElementType) * vectorPointer->size);
	// we free the old block
	free(vectorPointer->pointerToDataBlock);
	vectorPointer->pointerToDataBlock = newDataBlock;
	vectorPointer->capacity = vectorPointer->capacity * RESIZE_FACTOR;
	return;
}

vector* shopItemVector_create()
{
	vector* newVector = (vector*)malloc(sizeof(vector));
	// we initialise the size and capacity
	newVector->size = 0;
	newVector->capacity = 1;
	// we allocate memory for INITIAL_CAPACITY structs
	newVector->pointerToDataBlock = malloc(INITIAL_CAPACITY * sizeof(ElementType*));
	return newVector;
}


void shopItemVector_destroy(vector* vectorPointer)
{
	destroy(vectorPointer, destroyShopItem);
	return;
}

void destroy(vector* vectorPointer,DestroyFunction destrFunction)
{
	for (size_t i = 0; i < vectorPointer->size; i++)
		// we call the destructor for each shopItem
	{
		ElementType currentShopItem = getElementWithIndex(vectorPointer, i);
		destrFunction(currentShopItem);
	}
	// we free the block
	free(vectorPointer->pointerToDataBlock);
	vectorPointer->pointerToDataBlock = NULL;
	// we free the struct
	free(vectorPointer);
	vectorPointer = NULL;
	return;
}

void popUndoList(vector** currentList, vector* undoList)
{
	if (getSize(undoList) == 0)
		return;
	shopItemVector_destroy(*currentList);
	*currentList = createCopyOfVector(getElementWithIndex(undoList, getSize(undoList) - 1));
	shopItemVector_destroy(getElementWithIndex(undoList, getSize(undoList) - 1));
	undoList->size = undoList->size - 1;
	return;
}

void pushBack(vector* shopItemVector_pointer,
							 ElementType newShopItem)
{
	if (shopItemVector_pointer->size == shopItemVector_pointer->capacity)
		resizeVector(shopItemVector_pointer);
	shopItemVector_pointer->pointerToDataBlock[shopItemVector_pointer->size++] = newShopItem;
	return;
}

void shopItemVector_removeElementWithIndex(vector* shopItemVector_pointer,
										   size_t index)
{
	// we check that the vector is not empty and index < vector s size
	if (index >= shopItemVector_pointer->size || shopItemVector_pointer->size == 0)
		return;
	// we allocate a new block of memory where we will copy the items before and after the index
	shopItem_type** newDataBlock = malloc(sizeof(shopItem_type*) *
														(shopItemVector_pointer->capacity));

	size_t curentIndexInNewBlock = 0;

	for (size_t i = 0; i < shopItemVector_pointer->size; i++)
		if (i != index)
			newDataBlock[curentIndexInNewBlock++] = shopItemVector_pointer->pointerToDataBlock[i];
	// we destroy the item with the given index
	destroyShopItem(shopItemVector_pointer->pointerToDataBlock[index]);
	// we free the old block
	free(shopItemVector_pointer->pointerToDataBlock);
	// we decrease the size
	shopItemVector_pointer->size--;
	// we save the pointer to the new block
	shopItemVector_pointer->pointerToDataBlock = newDataBlock;
	return;
}

ElementType getElementWithIndex(vector* shopItemVector_pointer,	
												 size_t index)
{
	return shopItemVector_pointer->pointerToDataBlock[index];
}



void shopItemVector_replaceElementWithIndexWith(vector* shopItemVector_pointer,
												size_t index,
												shopItem_type* newShopItem)
{
if (shopItemVector_pointer->size <= index || shopItemVector_pointer->size == 0)
return;
// we free the memory allocated for the old item
destroyShopItem(shopItemVector_pointer->pointerToDataBlock[index]);
shopItemVector_pointer->pointerToDataBlock[index] = newShopItem;
return;
}

size_t getSize(vector* shopItemVector_pointer)
{
	return shopItemVector_pointer->size;
}

vector* createCopyOfVector(vector* shopItemVector_pointer)
{
	vector* CopyVector = shopItemVector_create();
	for (size_t indice = 0; indice < getSize(shopItemVector_pointer); indice++)
	{
		shopItem_type* CurrentShopItem = getElementWithIndex(shopItemVector_pointer, indice);
		shopItem_type* copyShopItem = createCopyOfShopItem(CurrentShopItem);
		pushBack(CopyVector, copyShopItem);
	}
	return CopyVector;
}

// Function that chooses the pivot and places it at the right position in the sorted vector
// Used for quickSort implementation
int quickSort_choosePivot(vector* shopItemVector_pointer,
	int reverseFlag,
	int(*compareFunction)(shopItem_type*, shopItem_type*),
	int leftIndex,
	int rightIndex)
{
	int i = leftIndex;
	int j = rightIndex;
	int iSpeed = 0;
	int jSpeed = 1;

	while (i != j)
	{
		shopItem_type* itemOnIposition = shopItemVector_pointer->pointerToDataBlock[i];
		shopItem_type* itemOnJposition = shopItemVector_pointer->pointerToDataBlock[j];
		if (compareFunction(itemOnIposition, itemOnJposition) == reverseFlag)
		{
			shopItemVector_pointer->pointerToDataBlock[i] = itemOnJposition;
			shopItemVector_pointer->pointerToDataBlock[j] = itemOnIposition;
			int aux = iSpeed;
			iSpeed = jSpeed;
			jSpeed = aux;
		}
		i += iSpeed;
		j -= jSpeed;
	}
	return i;
}
// Quick sort algorithm implementation on a shopItem_type vector using a generic function for
// comparaing two shopItems
void quickSort(vector* shopItemVector_pointer,
	int reverseFlag,
	int(*compareFunction)(shopItem_type*, shopItem_type*),
	int leftIndex,
	int rightIndex)
{
	if (leftIndex < rightIndex)
	{
		int pivot = quickSort_choosePivot(shopItemVector_pointer,
			reverseFlag,
			compareFunction,
			leftIndex,
			rightIndex);
		quickSort(shopItemVector_pointer,
			reverseFlag,
			compareFunction,
			leftIndex,
			pivot - 1);
		quickSort(shopItemVector_pointer,
			reverseFlag,
			compareFunction,
			pivot + 1,
			rightIndex);
	}
	return;
}

void shopItemVector_sort(vector* shopItemVector_pointer,
	int reverseFlag,
	int(*compareFunction)(shopItem_type*, shopItem_type*))
{
	quickSort(shopItemVector_pointer,
		reverseFlag,
		compareFunction,
		0, shopItemVector_pointer->size-1);

}
