#ifndef SHOPITEMVECTOR_H_
#define SHOPITEMVECTOR_H_
 /*This file contains the definitions and methods of the vector
 container, usable only with instances of shopItem_type*/

#include "domain.h"
#include <stdlib.h>
typedef void* ElementType;

typedef void (*DestroyFunction)(ElementType);

typedef struct {
	size_t size;
	size_t capacity;
	ElementType* pointerToDataBlock;
}vector;

 /*Creates a new vector and returns the adress
 Pre: true
 Post: returns a pointer to a vector instance or NULL if the heap is full*/
vector*  shopItemVector_create();

 /*Deallocates the memory of the vector
 Pre: vectorPointer must be a valid pointer to a vector instance
 Post: the memory will be freed*/
void shopItemVector_destroy(vector* vectorPointer);

/* destroys a list of generic items(can be shopItems or lists)
*  vectorPointer- pointer to a valid vector of instances
* destrFunction- general function that destroys a shopItem or a list
*/
void destroy(vector* vectorPointer, DestroyFunction destrFunction);

 /*Adds a new shopItem at the end of the vector
 Pre: shopItemVector_pointer must be a valid pointer to a vector
		instance;
		newShopItem - shopItem_type instance;
 Post: newShopItem will be added at the end of the vector;
		the size of the vector will be increased by 1 ;*/
void pushBack(vector* shopItemVector_pointer,
							 ElementType newShopItem);

 //Removes the shopItem instance with the given index from the vector
 // Pre: shopItemVector_pointer must be a valid pointer to a vector
	//	instance;
	//	index - size_t value, index < size of vector;
 //Post: the shopItem instance with the given index will be removed from the vector;
	//	the size of the vector will be decreased by 1;
void shopItemVector_removeElementWithIndex(vector* shopItemVector_pointer,
										   size_t index);

 /*Returns the shopItem instance with the given index from the vector
  Pre: shopItemVector_pointer must be a valid pointer to a vector
		instance;
		index - size_t value, index < size of vector;
 Post: returns a shopItem instance;
 Undefined behaviour if index >= size or the vector is empty */
ElementType getElementWithIndex(vector* shopItemVector_pointer,
												 size_t index);

 /*Replaces the shopItem with the given index from the vector with newShopItemValue
  Pre: shopItemVector_pointer must be a valid pointer to a vector
	instance;
		index - size_t value, index < size of vector;
		newShopItemValue - shopItem_type instance;
 Post: the shopItem with the given index will be replaced with the newShopItem 
 Note: the old item will be destroyed*/
void shopItemVector_replaceElementWithIndexWith(vector* shopItemVector_pointer,
												size_t index,
												shopItem_type* newShopItem);
 /*Returns the size of the vector
  Pre: shopItemVector_pointer must be a valid pointer to a vector
		instance
 Post: returns a size_t value*/
size_t getSize(vector* shopItemVector_pointer);

/*
 Sorts the vector in ascending or descending order
 Pre: shopItemVector_pointer must be a valid pointer to a vector
	instance;
		reverseFlag - int value equal to TRUE or FALSE
		compareFunction - function that returns an integer equal to TRUE or FALSE (compares two
	items after one or more fields)  
 Post: the vector will be sorted in ascending or descending order based on
	the compareFunction;
		  the compareFunction must return TRUE if the key value of the first formal parameter is 
 smaller (or equal) than the key value of the second one or FALSE otherwise;
		  if reverseFlag == FALSE, the vector will be sorted in ascending order;
		  if reverseFlag == TRUE, the vector will be sorted in descending order*/
void shopItemVector_sort(vector* shopItemVector_pointer,
						 int reverseFlag,
						 int (*compareFunction)(shopItem_type*, shopItem_type*));
/* creates a copy of the current list(which is a parameter)
* Pre:shopItemVector_pointer - valid pointer to a vector instance
* Post: creates and returns a copy of the list shopItemVector_pointer 
*/
vector* createCopyOfVector(vector* shopItemVector_pointer);

/* eliberates memory ocupated by the last list from undoList, currentList becomes the last list from undoList
*  pre: currentList- valid pointer to the current list of instances
*       undoList- the undo list which contains lists
* post: eliberates memory ocupated by the last list from undoList
*/
void popUndoList(vector** currentList, vector* undoList);

#define GET_POINTER_SHOPITEM(shopItemVector,index)((shopItem_type*)getElementWithIndex(shopItemVector,index))

#endif