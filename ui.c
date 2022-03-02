
#include "ui.h"
#include "utils.h"
#include "service.h"
#include "domain.h"
#include <stdio.h>
#include <string.h>
#include "constants.h"

/// Prints the main menu
void ui_printMainMenu(int reverseSortingFlag, char fieldFilter[FILTER_SIZE]);

/// Prints the given items
void ui_printVectorShopItems(vector* shopItemVector_pointer);

/// Reads an integer from the user. Returns TRUE if the user input is an integer and FALSE otherwise. Prints message
/// if the input is not an integer. If the reading operation was succesful, the value will be memorized at the given adress.
int ui_getIntegerFromUser(int* pointerToWhereTheIntWillBeMemorized);

/// Reads a float from the user. Returns TRUE if the user input is a float and FALSE otherwise. Prints message
/// if the input is not an float. If the reading operation was succesful, the value will be memorized at the given adress.
int ui_getFloatFromUser(float* pointerToWhereTheFloatWillBeMemorized);

/// Handles validation exception (prints error messages)
void ui_handleValidationException(shopItemValidationFlags_type shopItemValidationFlags);

/// Reads input from the user and adds the new shopItem to the stock
void ui_addShopItem(vector* stockItemVector_pointer, vector* undoVector);

/// Updates an item with the given id
void ui_updateShopItem(vector* stockItemVector_pointer,vector* undoVector);

/// Removes an item with the given id
void ui_removeShopItemFromStock(vector* stockItemVector_pointer, vector* undoVector);

//it realises the undo operation
void ui_undo(vector** stockItemVector_pointer, vector* undoVector);

/// Prints the stocks items sorted by price and quantity with the curent sorting setting
void ui_sortStockItemsByPriceAndQuantity(vector* stockItemVector_pointer, 
										int* reverseSortingFlag_pointer);

/// Prints the stocks items filtered by the active filter
void ui_filterStockItemsByFieldFilter(vector* stockItemVector_pointer,
													  char fieldFilter[FILTER_SIZE]);

void ui_filterAndSort(vector* stockItemVector_pointer, char fieldFilter[FILTER_SIZE], int* reverseSortingFlag_pointer);

//Filters after model,price and quantity
void ui_multipleFilter(vector* stockItemVector_pointer);

// Sets the order after the items will be displayed
void ui_setSortingFlag(int* reverseSortingFlag_pointer);

// Sets the filter
void ui_setFieldFilter(char fieldFilter[FILTER_SIZE]);

/// Runs the given command
void ui_runUserCommand(vector** stockItemVector_pointer,vector* undoVector, int userCommand, int* reverseSortingFlag_pointer, char fieldFilter[FILTER_SIZE])
{
	if (userCommand == ADD_SHOP_ITEM_COMMAND)
		ui_addShopItem(*stockItemVector_pointer,undoVector);
	if (userCommand == UPDATE_SHOP_ITEM_COMMAND)
		ui_updateShopItem(*stockItemVector_pointer,undoVector);
	if (userCommand == REMOVE_SHOP_ITEM_COMMAND)
		ui_removeShopItemFromStock(*stockItemVector_pointer,undoVector);
	if (userCommand == UNDO_COMMAND)
		ui_undo(stockItemVector_pointer, undoVector);
	if (userCommand == SORT_STOCK_COMMAND)
		ui_sortStockItemsByPriceAndQuantity(*stockItemVector_pointer, reverseSortingFlag_pointer);
	if (userCommand == FILTER_STOCK_COMMAND)
		ui_filterStockItemsByFieldFilter(*stockItemVector_pointer, fieldFilter);
	if (userCommand == FILTER_SORT)
		ui_filterAndSort(*stockItemVector_pointer, fieldFilter, reverseSortingFlag_pointer);
	if (userCommand == MULTIPLE_FILTER)
		ui_multipleFilter(*stockItemVector_pointer);
	if (userCommand == SET_ORDER_COMMAND)
		ui_setSortingFlag(reverseSortingFlag_pointer);
	if (userCommand == SET_FILTER_COMMMAND)
		ui_setFieldFilter(fieldFilter);
	return;
}
// Pre: stockItemVector_pointer - valid pointer to an empty vector instance
// Post: true
void ui_consoleRun()
{
	// we define the sort flag and the filter
	vector* stockItemVector = shopItemVector_create();
	vector* undoVector = shopItemVector_create();
	int reverseSortingFlag = FALSE;
	char fieldFilter[FILTER_SIZE] = "manufacturer";
	printf("---------------SHOP MANAGEMENT APLICATION---------------\n");
	ui_printMainMenu(reverseSortingFlag, fieldFilter);
	while (TRUE)
	{
		char userInputLine[BUFFER_SIZE];
		printf(">>");
		gets_s(userInputLine, BUFFER_SIZE);
		stripSpacesFromString(userInputLine);
		if (isStringInteger(userInputLine))
		{
			int userCommand = atoi(userInputLine);
			if (userCommand < 1 || userCommand > NUMBER_OF_COMMANDS)
			{
				printf("Invalid Command!\n");
				continue;
			}
			else if (userCommand == PRINT_MENIU_COMMAND)
			{
				ui_printMainMenu(reverseSortingFlag, fieldFilter);
				continue;
			}
			else if (userCommand == EXIT_COMMAND)
				break;
			else ui_runUserCommand(&stockItemVector,
									undoVector,
									userCommand,
									&reverseSortingFlag,
									fieldFilter);
		}
		else if(strlen(userInputLine)>0)
		{
			printf("Invalid Command!\n");
			continue;
		}
	}
	shopItemVector_destroy(stockItemVector);
	destroy(undoVector, shopItemVector_destroy);
	return;
}
void ui_printMainMenu(int reverseSortingFlag, char fieldFilter[FILTER_SIZE]) 
{
	printf("----------------MENIU----------------\n");
	printf("1. Add new shop item\n");
	printf("2. Update shop item\n");
	printf("3. Remove shop item from the stock\n");
	printf("4. Sort stock by price and quantity\n");
	printf("5. Filter stock by the curent set field\n");
	printf("6. Filter by model,price and quantity\n");
	printf("7. Set sorting order\n");
	printf("8. Set filter\n");
	printf("9. Undo\n");
	printf("10. Filter by the curent set field and sort\n");
	printf("11. MENIU\n");
	printf("12. EXIT\n");
	printf("-------------------------------------\n");

	if (reverseSortingFlag == FALSE)
		printf("Sorting is set to <ascending>\n");
	else
		printf("Order of sorting is set to <descending>\n");
	printf("Filter is set to <%s>\n", fieldFilter);
	printf("-------------------------------------\n");
	return;
}

void ui_printVectorShopItems(vector* shopItemVector_pointer)
{
	printf("----------------STOCK----------------\n");
	for (size_t i = 0; i < getSize(shopItemVector_pointer); i++)
	{
		shopItem_type* curentShopItem = getElementWithIndex(shopItemVector_pointer, i);
		char shopItemStringFormat[] = "Id: %d, Type: %s, Manufacturer: %s, Model: %s, Price: %f, Quantity: %d\n";
		printf(shopItemStringFormat, curentShopItem->id,curentShopItem->type,curentShopItem->manufacturer,curentShopItem->model,curentShopItem->price,curentShopItem->quantity);
	}
	printf("-------------------------------------\n");
	return;
}

int ui_getIntegerFromUser(int* pointerToWhereTheIntWillBeMemorized)
{
	char inputBuffer[BUFFER_SIZE];
	char parsingErrorMessage[] = "Invalid input format!\n";
	gets_s(inputBuffer, BUFFER_SIZE);
	stripSpacesFromString(inputBuffer);
	if (!isStringInteger(inputBuffer))
	{
		printf(parsingErrorMessage);
		return FALSE;
	}
	*pointerToWhereTheIntWillBeMemorized = atoi(inputBuffer);
	return TRUE;
}

int ui_getFloatFromUser(float* pointerToWhereTheFloatWillBeMemorized)
{
	char inputBuffer[BUFFER_SIZE];
	char parsingErrorMessage[] = "Invalid input format!\n";
	gets_s(inputBuffer, BUFFER_SIZE);
	stripSpacesFromString(inputBuffer);
	if (!isStringFloat(inputBuffer))
	{
		printf(parsingErrorMessage);
		return FALSE;
	}
	*pointerToWhereTheFloatWillBeMemorized = strtof(inputBuffer, NULL);
	return TRUE;
}

void ui_handleValidationException(shopItemValidationFlags_type shopItemValidationFlags)
{
	printf("----------VALIDATION ERROR----------\n");
	if (!shopItemValidationFlags.isIdValid)
		printf("Invalid id!\n");
	if (!shopItemValidationFlags.isTypeValid)
		printf("Invalid type!\n");
	if (!shopItemValidationFlags.isManufacturerValid)
		printf("Invalid manufacturer!\n");
	if (!shopItemValidationFlags.isModelValid)
		printf("Invalid model!\n");
	if (!shopItemValidationFlags.isPriceValid)
		printf("Invalid price!\n");
	if (!shopItemValidationFlags.isQuantityValid)
		printf("Invalid quantity!\n");
	printf("------------------------------------\n");
	return;
}

void ui_addShopItem(vector* stockItemVector_pointer, vector* undoVector)
{
	printf("------------ADD SHOP ITEM-----------\n");
	int id;
	char typeInputBuffer[BUFFER_SIZE];
	char manufacturerInputBuffer[BUFFER_SIZE];
	char modelInputBuffer[BUFFER_SIZE];
	float price;
	int quantity;
	printf("Id:");
	if (!ui_getIntegerFromUser(&id))
		return;
	printf("Type:");
	gets_s(typeInputBuffer, BUFFER_SIZE);
	stripSpacesFromString(typeInputBuffer);
	printf("Manufacturer:");
	gets_s(manufacturerInputBuffer, BUFFER_SIZE);
	stripSpacesFromString(manufacturerInputBuffer);
	printf("Model:");
	gets_s(modelInputBuffer, BUFFER_SIZE);
	stripSpacesFromString(modelInputBuffer);
	printf("Price:");
	if (!ui_getFloatFromUser(&price))
		return;
	printf("Quantity:");
	if (!ui_getIntegerFromUser(&quantity))
		return;
	shopItemValidationFlags_type shopItemValidationFlags;
	service_addShopItem(stockItemVector_pointer,undoVector, id, typeInputBuffer, manufacturerInputBuffer, modelInputBuffer, price, quantity, &shopItemValidationFlags);
	if (!shopItemValidationFlags.isShopItemValid)
		ui_handleValidationException(shopItemValidationFlags);
	return;
}

void ui_undo(vector** stockItemVector_pointer, vector* undoVector)
{
	printf("------------UNDO----------------\n");
	printf("\n");
	serviceUndo(stockItemVector_pointer, undoVector);
	return;
}

void ui_updateShopItem(vector* stockItemVector_pointer, vector* undoVector)
{
	printf("------------UPDATE ITEM-------------\n");
	int shopItemId;
	float newPrice;
	int newQuantity;
	printf("Id:");
	if (!ui_getIntegerFromUser(&shopItemId))
		return;
	printf("New price:");
	if (!ui_getFloatFromUser(&newPrice))
		return;
	printf("New quantity:");
	if(!ui_getIntegerFromUser(&newQuantity))
		return;
	service_updateShopItem(stockItemVector_pointer,undoVector, shopItemId, newPrice, newQuantity);
	return;
}

void ui_removeShopItemFromStock(vector* stockItemVector_pointer, vector* undoVector)
{
	printf("------------REMOVE ITEM-------------\n");
	int shopItemId;
	printf("Id:");
	if (!ui_getIntegerFromUser(&shopItemId))
		return;
	service_removeShopItemFromStock(stockItemVector_pointer, undoVector, shopItemId);
	return;
}

void ui_sortStockItemsByPriceAndQuantity(vector* stockItemVector_pointer, int* reverseSortingFlag_pointer)
{
	printf("------------SORT ITEMS--------------\n");
	service_sortStockItemsByPriceAndQuantity(stockItemVector_pointer, *reverseSortingFlag_pointer);
	ui_printVectorShopItems(stockItemVector_pointer);
	return;
}

void ui_filterStockItemsByFieldFilter(vector* stockItemVector_pointer, char fieldFilter[FILTER_SIZE])
{
	printf("-----------FILTER ITEMS-------------\n");
	char manufacturerKeyValue[BUFFER_SIZE];
	float priceKeyValue;
	int quantityKeyValue;
	void* filterKey_pointer = &manufacturerKeyValue;
	if (strcmp(fieldFilter, "manufacturer") == 0)
	{
		printf("Manufacturer:\n>>");
		gets_s(manufacturerKeyValue, BUFFER_SIZE);
		stripSpacesFromString(manufacturerKeyValue);
	}
	if (strcmp(fieldFilter, "price") == 0)
	{
		printf("Price:\n>>");
		if (!ui_getFloatFromUser(&priceKeyValue))
			return;
		else filterKey_pointer = &priceKeyValue;
	}
	if (strcmp(fieldFilter, "quantity") == 0)
	{
		printf("Quantity:\n>>");
		if (!ui_getIntegerFromUser(&quantityKeyValue))
			return;
		else filterKey_pointer = &quantityKeyValue;
	}
	vector* resultOfStockFiltration = shopItemVector_create();
	service_filterStockItemsByManufacturerPriceOrQuantity(stockItemVector_pointer, resultOfStockFiltration, fieldFilter, filterKey_pointer);
	ui_printVectorShopItems(resultOfStockFiltration);
	shopItemVector_destroy(resultOfStockFiltration);
	return;
}

void ui_filterAndSort(vector* stockItemVector_pointer, char fieldFilter[FILTER_SIZE], int* reverseSortingFlag_pointer)
{
	printf("-----------FILTER AND SORT ITEMS-------------\n");
	char manufacturerKeyValue[BUFFER_SIZE];
	float priceKeyValue;
	int quantityKeyValue;
	void* filterKey_pointer = &manufacturerKeyValue;
	if (strcmp(fieldFilter, "manufacturer") == 0)
	{
		printf("Manufacturer:\n>>");
		gets_s(manufacturerKeyValue, BUFFER_SIZE);
		stripSpacesFromString(manufacturerKeyValue);
	}
	if (strcmp(fieldFilter, "price") == 0)
	{
		printf("Price:\n>>");
		if (!ui_getFloatFromUser(&priceKeyValue))
			return;
		else filterKey_pointer = &priceKeyValue;
	}
	if (strcmp(fieldFilter, "quantity") == 0)
	{
		printf("Quantity:\n>>");
		if (!ui_getIntegerFromUser(&quantityKeyValue))
			return;
		else filterKey_pointer = &quantityKeyValue;
	}
	vector* resultOfStockFiltration = shopItemVector_create();
	service_filterStockItemsByManufacturerPriceOrQuantity(stockItemVector_pointer, resultOfStockFiltration, fieldFilter, filterKey_pointer);
	service_sortStockItemsByPriceAndQuantity(resultOfStockFiltration, *reverseSortingFlag_pointer);
	ui_printVectorShopItems(resultOfStockFiltration);
	shopItemVector_destroy(resultOfStockFiltration);
	return;
}

void ui_multipleFilter(vector* stockItemVector_pointer)
{
	printf("-----------FILTER ITEMS-------------\n");
	char modelKeyValue[BUFFER_SIZE];
	float priceKeyValue;
	int quantityKeyValue;
	void* filterModel = &modelKeyValue;
	printf("Model:\n>>");
	gets_s(modelKeyValue, BUFFER_SIZE);
	stripSpacesFromString(modelKeyValue);
	printf("Price:\n>>");
	if (!ui_getFloatFromUser(&priceKeyValue))
		return;
	printf("Quantity:\n>>");
	if (!ui_getIntegerFromUser(&quantityKeyValue))
		return;
	vector* resultOfStockFiltration = shopItemVector_create();
	service_multipleFilter(stockItemVector_pointer, resultOfStockFiltration, filterModel, &priceKeyValue, &quantityKeyValue);
	ui_printVectorShopItems(resultOfStockFiltration);
	shopItemVector_destroy(resultOfStockFiltration);
	return;
}

void ui_setSortingFlag(int* reverseSortingFlag_pointer)
{
	printf("-------------SET ORDER--------------\n");
	printf("Set sorting order: <ascending> <descending>:\n");
	printf(">>");
	char inputBuffer[BUFFER_SIZE];
	gets_s(inputBuffer, BUFFER_SIZE);
	stripSpacesFromString(inputBuffer);
	if (strcmp(inputBuffer, "ascending") == 0)
		*reverseSortingFlag_pointer = FALSE;
	else if (strcmp(inputBuffer, "descending") == 0)
		*reverseSortingFlag_pointer = TRUE;
	else printf("Invalid option!\n");
	return;
}

void ui_setFieldFilter(char fieldFilter[FILTER_SIZE])
{
	printf("-------------SET FILTER--------------\n");
	printf("Choose a filter: <manufacturer> <price> <quantity>:\n");
	printf(">>");
	char inputBuffer[BUFFER_SIZE];
	gets_s(inputBuffer, BUFFER_SIZE);
	stripSpacesFromString(inputBuffer);
	if (strcmp(inputBuffer, "manufacturer") == 0)
		strcpy_s(fieldFilter, FILTER_SIZE, "manufacturer");
	else if (strcmp(inputBuffer, "price") == 0)
		strcpy_s(fieldFilter, FILTER_SIZE, "price");
	else if (strcmp(inputBuffer, "quantity") == 0)
		strcpy_s(fieldFilter, FILTER_SIZE, "quantity");
	else printf("Invalid option!\n");
	return;
}


