// This file conttains all the functions of the service layer

#ifndef SERVICE_H_
#define SERVICE_H_
#include "shopItemVector.h"
#include "domain.h"

/// Adds a new shopItem in the stock
/// Pre: stockItemVector_pointer must be a valid pointer to a vector
///	instance;
///		 id - integer;
///		 type_pointer, manufacturer_pointer, model_pointer - valid pointers to Cstrings;
///		 price - float;
///		 quantity - integer;
///		 shopItemValidationFlags_pointer - valid pointer to a shopItemValidationFlags_type instance
/// Post: if the newShopItem is already in the stock, the quantity will be
///	increased by the new quantity;
///		  otherwise, if it is valid and the id is unique, it will be added to the stock;
///		  if the object is not valid, all flags will be set to 1;
void service_addShopItem(vector* stockItemVector_pointer, 
						 vector* undoList,
						 int id,
						 char *type_pointer,
						char* manufacturer_pointer,
						char* model_pointer,
						float price,
						int quantity,
						 shopItemValidationFlags_type *shopItemValidationFlags_pointer);

///  Updates the shopItem from the stock with the given id
///  Pre: stockItemVector_pointer must be a valid pointer to a vector
///instance;
///		  newPrice - positive float;
///		  newQuantity - positive integer;
///		  shopItemId - integer;
///  Post: the shopItem will have the newPrice and newQuantity
void service_updateShopItem(vector* stockItemVector_pointer,
							vector* undoList,
							int shopItemId,
							float newPrice,
							int newQuantity);

/// Removes from the stock the shopItem with the given id
///  Pre: stockItemVector_pointer must be a valid pointer to a vector
///	instance;
///		  shopItemId - integer;
///  Post: the item, if exists, will be removed from the stock
void service_removeShopItemFromStock(vector* stockItemVector_pointer,
									 vector* undoList,
									 int shopItemId);

/// Sorts the stock by the price and quantity of the items
///  Pre: stockItemVector_pointer must be a valid pointer to a vector
///instance;
///		 reverseFlag - integer equal to TRUE or FALSE
/// Post: the stock items will be sorted in ascending order if reverseFlag = FALSE or in descending
///order if reverseFlag = TRUE;
void service_sortStockItemsByPriceAndQuantity(vector* stockItemVector_pointer,
											  int reverseFlag);

/// Filters the stock items by the curent filter field and the filter key
/// Pre: stockItemVector_pointer must be a valid pointer to a vector
///instance (represents the stock);
///		  filteredItemsVector_pointer must be a valid pointer to a vector
///instance (represents where the result of the filtration will be);
///		  curentFilterField - string equal to "manufacturer", "price" or "quantity; represents
///the field after the stock will be filtered;
///		  filterKey_pointer - valid pointer to a integer, string or float (represents the key
///after the stock will be filtered);
/// Post: the stock will be filtered by the given field and value (by manufacturer, price or quantity)
/// If the curentFilterField is "manufacturer", then the filterKey_pointer must be a string and the
///		result of filtration will contain all the items produced by the given manufacturer
/// If the curentFilterField is "price", then the filterKey_pointer must be a float pointer and the
///		result of filtration will contain all the items with the price lower or equal than the given one
/// If the curentFilterField is "quantity", then the filterKey_pointer must be a int pointer and the
///		result of filtration will contain all the items with quantity smaller or equal than the given
///		one
void service_filterStockItemsByManufacturerPriceOrQuantity(vector* stockItemVector_pointer, 
														   vector* filteredItemsVector_pointer,
														   char curentFilterField[],
														   void* filterKey_pointer);

/* filters the current list , considering a specific model, price and quantity
*  pre: stockItemVector_pointer is a valid pointer to a vector instance (the stock)
*		filteredVector is a valid pointer to a vector instance(filtered list)
* post: the stock will be filtered by model, price and quantity
*/
void service_multipleFilter(vector* stockItemVector_pointer, vector* filteredVector, char *modelField, float* priceField, int* quantityField);

/* realises undo on the current list
*  stockItemVector - pointer of pointers to a list of products
*  undoVector - pointer to a liist of lists
*/
void serviceUndo(vector** stockItemVector, vector* undoVector);

#endif