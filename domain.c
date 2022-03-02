#include "domain.h"
#include <string.h>
#include <stdlib.h>

shopItem_type* createShopItem(int id, char* type, char* manufacturer, char* model, float price, int quantity)
{
	shopItem_type* newShopItem = malloc(sizeof(shopItem_type));
	newShopItem->id = id;
	newShopItem->price = price;
	newShopItem->quantity = quantity;

	newShopItem->type = malloc(sizeof(char) * (strlen(type) + 1));
	newShopItem->manufacturer = malloc(sizeof(char) * (strlen(manufacturer) + 1));
	newShopItem->model = malloc(sizeof(char) * (strlen(model) + 1));

	strcpy_s(newShopItem->type, strlen(type) + 1, type);
	strcpy_s(newShopItem->manufacturer, strlen(manufacturer) + 1, manufacturer);
	strcpy_s(newShopItem->model, strlen(model) + 1, model);

	return newShopItem;
}

void destroyShopItem(shopItem_type* shopItem)
{
	free(shopItem->type);
	free(shopItem->manufacturer);
	free(shopItem->model);
	free(shopItem);
	return;
}


void setShopItemValidationFlags(shopItemValidationFlags_type* shopItemValidationFlags_pointer)
{
	shopItemValidationFlags_pointer->isIdValid = TRUE;
	shopItemValidationFlags_pointer->isManufacturerValid = TRUE;
	shopItemValidationFlags_pointer->isModelValid = TRUE;
	shopItemValidationFlags_pointer->isQuantityValid = TRUE;
	shopItemValidationFlags_pointer->isShopItemValid = TRUE;
	shopItemValidationFlags_pointer->isTypeValid = TRUE;
	shopItemValidationFlags_pointer->isPriceValid = TRUE;
	return;
}

shopItem_type* createCopyOfShopItem(shopItem_type* shopItem)
{
	shopItem_type* copyOfShopItem = createShopItem(shopItem->id,
												shopItem->type,
												shopItem->manufacturer,
												shopItem->model,
												shopItem->price,
												shopItem->quantity);
	return copyOfShopItem;
}

void validateShopItem(shopItem_type* shopItem,
					  shopItemValidationFlags_type* shopItemValidationFlags_pointer)
{
	if (shopItem->id <= 0)
		shopItemValidationFlags_pointer->isIdValid = FALSE;
	if (strcmp(shopItem->manufacturer, "") == 0)
		shopItemValidationFlags_pointer->isManufacturerValid = FALSE;
	if (strcmp(shopItem->model, "") == 0)
		shopItemValidationFlags_pointer->isModelValid = FALSE;
	if (shopItem->price <= 0.0f)
		shopItemValidationFlags_pointer->isPriceValid = FALSE;
	if (shopItem->quantity < 0)
		shopItemValidationFlags_pointer->isQuantityValid = FALSE;
	if (strcmp(shopItem->type, "") == 0)
		shopItemValidationFlags_pointer->isTypeValid = FALSE;

	shopItemValidationFlags_pointer->isShopItemValid =
		shopItemValidationFlags_pointer->isIdValid &
		shopItemValidationFlags_pointer->isManufacturerValid &
		shopItemValidationFlags_pointer->isModelValid &
		shopItemValidationFlags_pointer->isPriceValid &
		shopItemValidationFlags_pointer->isQuantityValid &
		shopItemValidationFlags_pointer->isTypeValid;
	return;
}

int shopItem_areSame(shopItem_type* thisShopItem, shopItem_type* otherShopItem)
{
	
	if (strcmp(thisShopItem->manufacturer, otherShopItem->manufacturer))
		return FALSE;
	if(strcmp(thisShopItem->model, otherShopItem->model))
		return FALSE;
	if (strcmp(thisShopItem->type, otherShopItem->type))
		return FALSE;
	return TRUE;
}
