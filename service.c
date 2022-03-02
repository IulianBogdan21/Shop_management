
#include "service.h"
#include <string.h>


void service_addShopItem(vector* stockItemVector_pointer,vector* undoVector, int id, char* type_pointer, 
	char* manufacturer_pointer, char* model_pointer, float price, int quantity, 
	shopItemValidationFlags_type* shopItemValidationFlags_pointer)
{
	// we assume the new item is valid (we set the flags to 1)
	setShopItemValidationFlags(shopItemValidationFlags_pointer);
	// we create the shopItem
	shopItem_type* newShopItem = createShopItem(id, type_pointer, manufacturer_pointer, model_pointer, price, quantity);
	// we validate
	validateShopItem(newShopItem, shopItemValidationFlags_pointer);
	// if the item is invalid we deallocate memory and return
	if (shopItemValidationFlags_pointer->isShopItemValid == 0)
	{
		destroyShopItem(newShopItem);
		return;
	}
	// we check if the item is already in stock
	for (size_t i = 0; i < getSize(stockItemVector_pointer); i++)
	{
		shopItem_type* curentShopItemFromStock = getElementWithIndex(stockItemVector_pointer, i);
		if (shopItem_areSame(curentShopItemFromStock, newShopItem) == TRUE)
		{
			pushBack(undoVector, createCopyOfVector(stockItemVector_pointer));
			// we increase the quantity
			curentShopItemFromStock->quantity += newShopItem->quantity;
			// we will create a copy of the updated item, so that we don t lose the data
			shopItem_type* updatedItem = createCopyOfShopItem(curentShopItemFromStock);
			// now we replace the old item from the stock with the updated quantity
			// note that the old item has been destroyed in the replace function
			shopItemVector_replaceElementWithIndexWith(stockItemVector_pointer, i, updatedItem);
			// before we return, we free the memory allocated for the object that wasn't added
			destroyShopItem(newShopItem);
			// we are done, so we return
			return;}
		// the items are not the same; we check if they have different id-s so that the id-s from the
		// stock are unique
		else if (curentShopItemFromStock->id == newShopItem->id)
		{
			// the id is not valid so we free the space allocated for the item
			destroyShopItem(newShopItem);
			return;
		}
	}
	// finally if the item is not in the stock and the id-s are unique, we add it
	pushBack(undoVector, createCopyOfVector(stockItemVector_pointer));
	pushBack(stockItemVector_pointer, newShopItem);
	return;
}

void service_updateShopItem(vector* stockItemVector_pointer,vector* undoVector,int shopItemId, float newPrice, int newQuantity)
{
	// we search the item with the given id
	for (size_t i = 0; i < getSize(stockItemVector_pointer); i++)
	{
		shopItem_type* curentItemFromStock = getElementWithIndex(stockItemVector_pointer, i);
		// we check if the id-s are equal
		if (curentItemFromStock->id == shopItemId)
		{
			pushBack(undoVector, createCopyOfVector(stockItemVector_pointer));
			// we update the curent item and the replace it in the vector
			curentItemFromStock->price = newPrice;
			curentItemFromStock->quantity = newQuantity;
			// we will create a copy of the updated item, so that we don t lose the data
			shopItem_type* updatedItem = createCopyOfShopItem(curentItemFromStock);
			// now we replace the old item with the new updated one	
			// note that the old item has been destroyed in the replace function
			shopItemVector_replaceElementWithIndexWith(stockItemVector_pointer,i,updatedItem);
			return;
		}
	}
	return;
}

void service_removeShopItemFromStock(vector* stockItemVector_pointer,vector* undoVector, int shopItemId)
{
	// we search the item with the given id
	for (size_t i = 0; i < getSize(stockItemVector_pointer); i++)
	{
		shopItem_type* curentItemFromStock = getElementWithIndex(stockItemVector_pointer, i);
		// we check if the curent item has the id we re loking for
		if (curentItemFromStock->id == shopItemId)
		{
			pushBack(undoVector, createCopyOfVector(stockItemVector_pointer));
			// we found the item, so we remove it from the vector
			shopItemVector_removeElementWithIndex(stockItemVector_pointer, i);
			return;
		}
	}
	return;
}
// Function used to compare two items by price and quantity 
// Pre: thisShopItem, otherShopItem - shopItem_type instances
// Post: returns TRUE if thisShopItem.price < otherShopItem.price or (thisShopItem.price == otherShopItem.price and
//thisShopItem.quantity < otherShopItem.quantity) or FALSE otherwise
int compareItemsByPriceAndQuantity(shopItem_type* thisShopItem, shopItem_type* otherShopItem)
{
	if (thisShopItem->price > otherShopItem->price)
		return FALSE;
	if (thisShopItem->price == otherShopItem->price)
		if (thisShopItem->quantity > otherShopItem->quantity)
			return FALSE;
	return TRUE;
}

void service_sortStockItemsByPriceAndQuantity(vector* stockItemVector_pointer, int reverseFlag)
{
	// we sort the vector by price and quantity
	shopItemVector_sort(stockItemVector_pointer, reverseFlag,compareItemsByPriceAndQuantity);
	return;
}

/// Generic function used to filter the stock by some key using a function that checks if one items
/// field respects the condition based on the given key
/// Pre: stockItemVector_pointer must be a valid pointer to a vector
///	instance (represents the items which we want to filter);
///		 filteredItemsVector_pointer must be a valid pointer to a vector
///	instance  (represents the items resulted after filtration);
///		 fieldKey_pointer - valid pointer to a key value; 
///		 checkIfItemFieldIs - function that tests if one item respects the filter condition based on
///	the value found at fieldKey_pointer
/// Post: filteredItemsVector_pointer will contain the result of filtration
/// Note: the result vector will contain copies of the items, not the actual items
void filterStockBy(vector *stockItemVector_pointer, vector*filteredItemsVector_pointer,
					void *fieldKey_pointer,
					int (*checkIfItemFieldIs)(shopItem_type*, void*) 
					)
{
	for (size_t i = 0; i < getSize(stockItemVector_pointer); i++)
	{
		// if the curent item respects the condition of the filtration, then we add it to the filteredItemsVector
		shopItem_type* curentShopItem = getElementWithIndex(stockItemVector_pointer, i);
		if (checkIfItemFieldIs(curentShopItem, fieldKey_pointer) == TRUE)
		{   
			// before we pushBack, we create a copy (we don't want to have actual references of the item in the result)
			shopItem_type* copyItem = createCopyOfShopItem(curentShopItem);
			pushBack(filteredItemsVector_pointer, copyItem);
		}
	}
	return;
}

//Function that filters the curent stock after a specified model, price and quantity
//stockItemVector_pointer - pointer to the current stock
//filteredItemsVector_pointer - pointer to the filtered stock
//modelKey_pointer - pointer to a Cstring(the model we want to filter after)
//priceKey_pointer - pointer to a float(the price we want to filter after)
//quantityKey_pointer - pointer to an integer(the quantity we want to filter after)
//checkMultipleFileds - pointer to a function that ensures a current shopItem will be introduced in the filtered stock if respects the conditions

void multipleFilter(vector* stockItemVector_pointer, vector* filteredItemsVector_pointer, char* modelKey_pointer, float* priceKey_pointer,
	int* quantityKey_pointer,
	int(*checkMultipleFields)(shopItem_type*, char*, float*, int*))
{
	for (size_t i = 0; i < getSize(stockItemVector_pointer); i++)
	{
		// if the curent item respects the condition of the filtration, then we add it to the filteredItemsVector
		shopItem_type* curentShopItem = getElementWithIndex(stockItemVector_pointer, i);
		if (checkMultipleFields(curentShopItem, modelKey_pointer, priceKey_pointer, quantityKey_pointer) == TRUE)
		{
			// before we pushBack, we create a copy (we don't want to have actual references of the item in the result)
			shopItem_type* copyItem = createCopyOfShopItem(curentShopItem);
			pushBack(filteredItemsVector_pointer, copyItem);
		}
	}
	return;
}

/// Returns TRUE if the item has the manufacturer field equal to manufacturerKey, FALSE otherwise
/// shopItem - shopItem instance
/// manufacturerKey_pointer - valid pointer to a Cstring
int checkIfManufacturerFiledIs(shopItem_type* shopItem, char* manufacturerKey_pointer)
{
	if (strcmp(shopItem->manufacturer, manufacturerKey_pointer) == 0)
		return TRUE;
	return FALSE;
}

//Returns TRUE if the current shopItem has the same model, a less price and quantity than the rest of the parameters, FALSE otherwise
//shopItem - shopItem instance
//modelKey_pointer- valid pointer to a Cstring
//priceKey_pointer - valid pointer to a float
//quantityKey_pointer - valid pointer to a integer
int checkMultipleFields(shopItem_type* shopItem, char* modelKey_pointer, float* priceKey_pointer, int* quantityKey_pointer)
{
	if (strcmp(shopItem->model, modelKey_pointer))
		return FALSE;
	if (shopItem->price > *priceKey_pointer)
		return FALSE;
	if (shopItem->quantity > *quantityKey_pointer)
		return FALSE;
	return TRUE;
}


/// Returns TRUE if the item has the price lower than the priceKey, FALSE otherwise
/// shopItem - shopItem instance
/// priceKey_pointer - valid pointer to a float
int checkIfItemPriceIsLowerThan(shopItem_type* shopItem, float* priceKey_pointer)
{
	if (shopItem->price <= *priceKey_pointer)
		return TRUE;
	return FALSE;
}

/// Returns TRUE if the items quantity is lower than the quantityKey, FALSE otherwise
/// shopItem - shopItem instance
/// quantityKey_pointer - valid pointer to an int
int checkIfQuantityIsLowerThan(shopItem_type* shopItem, int* quantityKey_pointer)
{
	if (shopItem->quantity <= *quantityKey_pointer)
		return TRUE;
	return FALSE;
}

void service_filterStockItemsByManufacturerPriceOrQuantity(vector* stockItemVector_pointer,
															vector* filteredItemsVector_pointer, 
															char curentFilterField[], 
															void* filterKey_pointer)
{
	/// we check after what field we must do the filter operation
	if (strcmp(curentFilterField, "manufacturer") == 0)
		filterStockBy(stockItemVector_pointer, filteredItemsVector_pointer, filterKey_pointer, checkIfManufacturerFiledIs);

	if(strcmp(curentFilterField, "price")==0)
		filterStockBy(stockItemVector_pointer, filteredItemsVector_pointer, filterKey_pointer, checkIfItemPriceIsLowerThan);

	if (strcmp(curentFilterField, "quantity") == 0)
		filterStockBy(stockItemVector_pointer, filteredItemsVector_pointer, filterKey_pointer, checkIfQuantityIsLowerThan);

	return;
}

void service_multipleFilter(vector* stockItemVector_pointer, vector* filteredVector, char *modelField, float *priceField, int *quantityField)
{
	multipleFilter(stockItemVector_pointer, filteredVector, modelField, priceField, quantityField, checkMultipleFields);
	return;
}

void serviceUndo(vector** stockItemVector, vector* undoVector)
{
	popUndoList(stockItemVector, undoVector);
	return;
}
