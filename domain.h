/// This file contains the definitions for the domain entities and their specific
/// funcions

#ifndef DOMAIN_H_
#define DOMAIN_H_
#include "constants.h"

typedef struct {
	int id;
	char* type;
	char* manufacturer;
	char* model;
	float price;
	int quantity;
}shopItem_type;

/// Each flag is either TRUE or FALSE
typedef struct {
	int isShopItemValid;
	int isIdValid;
	int isTypeValid;
	int isManufacturerValid;
	int isPriceValid;
	int isModelValid;
	int isQuantityValid;
}shopItemValidationFlags_type;

/// Creates a new shopItem_type object
///	Pre: id, quantity - integers;
///		 price - float;
///		 type, manufacturer, model - valid pointers to Cstrings;
/// Post: returns a new shopItem_type object
shopItem_type* createShopItem(int id,
							char* type,
							char* manufacturer,
							char* model,
							float price,
							int quantity);

/// Destroys the object
/// Pre: shopItem - shopItem_type instance
/// Post: the memory used by the instance will be freed
void destroyShopItem(shopItem_type* shopItem);

/// Sets to value TRUE all fields of the given shopItemValidationFlags_type instance
/// Pre: shopItemValidationFlags_pointer - must be a valid pointer to a
///shopItemValidationFlags_type instance;
/// Post: all field flags will be set to TRUE
void setShopItemValidationFlags(shopItemValidationFlags_type* shopItemValidationFlags_pointer);

/// Creates a copy of the given shopItem 
/// Pre: shopItem - shopItem_type instance
/// Post: a copy of the given item will be created
shopItem_type* createCopyOfShopItem(shopItem_type* shopItem);

/// Validates a shop item
/// Pre: shopItem - shopItem_type value;
///		shopItemValidationFlags_pointer - pointer to a shopItemValidationFlags_type; 
/// Post: if the shopItem is valid (the id, price, quantity are positive and the type,
///manufacturer, model are non-empty strings), then all of the flags will be set
///to TRUE;
///		  otherwise, isShopItemValid flag and the flags for the non-valid fileds will be
///set to FALSE ;
void validateShopItem(shopItem_type* shopItem, 
					  shopItemValidationFlags_type* shopItemValidationFlags_pointer);

///  Checks if two shopItems are the same
/// Pre: thisShopItem, otherShopItem - shopItem_type instances
/// Post: return TRUE if they are the same (same model, manufacturer, type), FALSE otherwise
int shopItem_areSame(shopItem_type* thisShopItem,
					 shopItem_type* otherShopItem);


#endif