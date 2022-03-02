#include "test.h"
#include "domain.h"
#include "service.h"
#include "utils.h"
#include "shopItemVector.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>




/// -----------------------DOMAIN TESTS---------------------------

void createShopItemTest()
{
	shopItem_type* shopItem1 = createShopItem(1,"phone","Apple","S10",7000,	10);
	assert(shopItem1->id == 1);
	assert(strcmp(shopItem1->type, "phone") == 0);
	assert(strcmp(shopItem1->manufacturer, "Apple") == 0);
	assert(strcmp(shopItem1->model, "S10") == 0);
	assert(shopItem1->price == 7000);
	assert(shopItem1->quantity == 10);
	destroyShopItem(shopItem1);
}

void validateShopItemTest()
{
	shopItemValidationFlags_type validationFlags;
	setShopItemValidationFlags(&validationFlags);
	assert(validationFlags.isIdValid == 1);
	assert(validationFlags.isManufacturerValid == 1);
	assert(validationFlags.isModelValid == 1);
	assert(validationFlags.isPriceValid == 1);
	assert(validationFlags.isQuantityValid == 1);
	assert(validationFlags.isShopItemValid == 1);
	assert(validationFlags.isTypeValid == 1);
	shopItem_type* validShopItem = createShopItem(1,"SmartPhone","Apple","S10",5000.0f,5);
	shopItem_type* invalidShopItem1 = createShopItem(-100,"SmartTv","","",500.0f,30);
	shopItem_type* invalidShopItem2 = createShopItem(1,"","Apple","S10",-100.0f,-30);
	validateShopItem(validShopItem, &validationFlags);
	assert(validationFlags.isIdValid == 1);
	assert(validationFlags.isManufacturerValid == 1);
	assert(validationFlags.isModelValid == 1);
	assert(validationFlags.isPriceValid == 1);
	assert(validationFlags.isQuantityValid == 1);
	assert(validationFlags.isShopItemValid == 1);
	assert(validationFlags.isTypeValid == 1);
	setShopItemValidationFlags(&validationFlags);
	validateShopItem(invalidShopItem1, &validationFlags);
	assert(validationFlags.isIdValid == 0);
	assert(validationFlags.isManufacturerValid == 0);
	assert(validationFlags.isModelValid == 0);
	assert(validationFlags.isPriceValid == 1);
	assert(validationFlags.isQuantityValid == 1);
	assert(validationFlags.isShopItemValid == 0);
	assert(validationFlags.isTypeValid == 1);
	setShopItemValidationFlags(&validationFlags);
	validateShopItem(invalidShopItem2, &validationFlags);
	assert(validationFlags.isIdValid == 1);
	assert(validationFlags.isManufacturerValid == 1);
	assert(validationFlags.isModelValid == 1);
	assert(validationFlags.isPriceValid == 0);
	assert(validationFlags.isQuantityValid == 0);
	assert(validationFlags.isShopItemValid == 0);
	assert(validationFlags.isTypeValid == 0);
	destroyShopItem(validShopItem);
	destroyShopItem(invalidShopItem1);
	destroyShopItem(invalidShopItem2);
	return;
}

void shopItem_areSameTest()
{
	shopItem_type* shopItem1 = createShopItem(1,"smartphone","Apple","S10",0,0);
	shopItem_type* shopItem2 = createShopItem(1,"smartphone","Apple","S10",0,0);
	shopItem_type* shopItem3 = createShopItem(1,"smart","Samsung","S",0,0);
	shopItem_type* shopItem4 = createShopItem(1,"mart","Samsung","S",0,0);
	shopItem_type* shopItem5 = createShopItem(1,"smartphone","Apple","S11", 0, 0);
	assert(shopItem_areSame(shopItem1, shopItem2) == 1);
	assert(shopItem_areSame(shopItem1, shopItem3) == 0);
	assert(shopItem_areSame(shopItem2, shopItem3) == 0);
	assert(shopItem_areSame(shopItem3, shopItem4) == 0);
	assert(shopItem_areSame(shopItem1, shopItem5) == 0);
	destroyShopItem(shopItem1);
	destroyShopItem(shopItem2);
	destroyShopItem(shopItem3);
	destroyShopItem(shopItem4);
	destroyShopItem(shopItem5);
	return;
}

void createCopyOfShopItemTest()
{
	shopItem_type* shopItem = createShopItem(1,"smartphone","Apple","S10",500.0f,10);
	// we create the copy
	shopItem_type* copy = createCopyOfShopItem(shopItem);
	// we test that the field values are equal
	assert(copy->id == shopItem->id);
	assert(strcmp(copy->type, shopItem->type) == 0);
	assert(strcmp(copy->manufacturer, shopItem->manufacturer) == 0);
	assert(strcmp(copy->model, shopItem->model) == 0);
	assert(copy->price == shopItem->price);
	assert(copy->quantity == shopItem->quantity);
	// we make sure that the pointers have different values
	assert(copy->manufacturer != shopItem->manufacturer);
	assert(copy->type != shopItem->type);
	assert(copy->model != shopItem->model);
	destroyShopItem(shopItem);
	destroyShopItem(copy);
}

void runDomainTests()
{
	createShopItemTest();
	validateShopItemTest();
	shopItem_areSameTest();
	createCopyOfShopItemTest();
	return;
}

// ----------------------VECTOR CONTAINER TESTS-------------------------


void shopItemVector_createTest() 
{
	vector* vector = shopItemVector_create();
	assert(vector->size == 0);
	assert(vector->capacity == 1);
	shopItemVector_destroy(vector);
	return;
}

// Sets up a vector representing a stock of items
vector* setUpStock() 
{
	vector* testVector = shopItemVector_create();
	shopItem_type* shopItem1 = createShopItem(1,"smartphone","Apple","S10",500.0f,10);
	shopItem_type* shopItem2 = createShopItem(2,"smartphone","Apple","S11",600.0f,5);
	shopItem_type* shopItem3 = createShopItem(3,"smartphone","Samsung","10",600.0f,20);
	shopItem_type* shopItem4 = createShopItem(4,"smartphone","Huawei","2k19",500.0f,12);
	pushBack(testVector,shopItem1);
	pushBack(testVector,shopItem2);
	pushBack(testVector,shopItem3);
	pushBack(testVector,shopItem4);
	return testVector;
}

void copyVectorTest()
{
	vector* testVector = setUpStock();
	vector* copyVector = createCopyOfVector(testVector);
	assert(getSize(copyVector) == 4);
	assert(GET_POINTER_SHOPITEM(copyVector, 0)->id == 1);
	assert(GET_POINTER_SHOPITEM(copyVector, 1)->id == 2);
	assert(GET_POINTER_SHOPITEM(copyVector, 2)->id == 3);
	assert(GET_POINTER_SHOPITEM(copyVector, 3)->id == 4);
	for (size_t i = 0; i < 4; i++)
		assert(GET_POINTER_SHOPITEM(copyVector, i) != GET_POINTER_SHOPITEM(testVector, i));
	shopItemVector_destroy(testVector);
	shopItemVector_destroy(copyVector);
	return;
}

void listOfListsTest(){
	vector* testVector = setUpStock();
	vector* undoList = shopItemVector_create();
	pushBack(undoList, createCopyOfVector(testVector));
	assert(getSize(undoList) == 1);
	shopItemVector_destroy(testVector);
	destroy(undoList, shopItemVector_destroy);
	return;
}

void popUndoListTest()
{
	vector* testVectorT = shopItemVector_create();
	vector* undoList = shopItemVector_create();
	pushBack(undoList, createCopyOfVector(testVectorT));
	assert(getSize(undoList) == 1);
	shopItemVector_destroy(testVectorT);
	vector* testVector = setUpStock();
	pushBack(undoList, createCopyOfVector(testVector));
	assert(getSize(undoList) == 2);
	pushBack(testVector, createShopItem(5, "smartphone", "Alcatel", "T4", 600.0f, 15));
	assert(getSize(testVector) == 5);
	popUndoList(&testVector, undoList);
	assert(getSize(undoList) == 1);
	vector* result2 = getElementWithIndex(undoList, 0);
	assert(getSize(result2) == 0);
	assert(getSize(testVector) == 4);
	popUndoList(&testVector, undoList);	
	assert(getSize(undoList) == 0);
	assert(getSize(testVector) == 0);
	popUndoList(&testVector, undoList);
	shopItemVector_destroy(testVector);
	destroy(undoList, shopItemVector_destroy);
	return;
}

void pushBackTest() {
	vector* vectorPointer = shopItemVector_create();
	shopItem_type* shopItem1 = createShopItem(1,"smartphone","Apple","S10",500.0f,10);
	shopItem_type* shopItem2 = createShopItem(2,"smartphone","Apple","S11",600.0f,5);
	shopItem_type* shopItem3 = createShopItem(3,"smartphone","Samsung","10",600.0f,20);
	pushBack(vectorPointer, shopItem1);
	pushBack(vectorPointer, shopItem2);
	pushBack(vectorPointer, shopItem3);
	assert(vectorPointer->size == 3);
	assert(vectorPointer->capacity == 4);
	assert(shopItem_areSame(vectorPointer->pointerToDataBlock[0], shopItem1) == TRUE);
	assert(shopItem_areSame(vectorPointer->pointerToDataBlock[1], shopItem2) == TRUE);
	assert(shopItem_areSame(vectorPointer->pointerToDataBlock[2], shopItem3) == TRUE);
	assert(GET_POINTER_SHOPITEM(vectorPointer, 0)->id == 1);
	assert(GET_POINTER_SHOPITEM(vectorPointer, 1)->id == 2);
	assert(GET_POINTER_SHOPITEM(vectorPointer, 2)->id == 3);
	shopItemVector_destroy(vectorPointer);
	return;
}

void shopItemVector_removeElementWithIndexTest()
{
	vector* emptyVector = shopItemVector_create();
	// we try to remove an item when the vector is empty (it shouldn t crash)
	shopItemVector_removeElementWithIndex(emptyVector, 10);
	shopItemVector_destroy(emptyVector);
	// we add a few items
	vector*  testVector = setUpStock();
	// we try to remove an item with an index > size of vector
	shopItemVector_removeElementWithIndex(testVector, 10);
	// we remove the second item
	shopItemVector_removeElementWithIndex(testVector, 1);
	// we check that the item has been removed
	assert(testVector->size == 3);
	assert(GET_POINTER_SHOPITEM(testVector, 0)->id == 1);
	assert(GET_POINTER_SHOPITEM(testVector, 1)->id == 3);
	assert(GET_POINTER_SHOPITEM(testVector, 2)->id == 4);
	// we remove the first item
	shopItemVector_removeElementWithIndex(testVector, 0);
	// we check that the item has been removed
	assert(testVector->size == 2);
	assert(GET_POINTER_SHOPITEM(testVector, 0)->id == 3);
	assert(GET_POINTER_SHOPITEM(testVector, 1)->id == 4);
	// we remove the last item
	shopItemVector_removeElementWithIndex(testVector, 1);
	// we check that the item has been removed
	assert(testVector->size == 1);
	assert(GET_POINTER_SHOPITEM(testVector, 0)->id == 3);
	shopItemVector_destroy(testVector);
	return;
}

void getElementWithIndexTest() 
{
	vector* testVector = setUpStock();
	shopItem_type* shopItem1 = getElementWithIndex(testVector, 2);
	assert(shopItem1->id == 3);
	shopItemVector_destroy(testVector);
}

void shopItemVector_replaceElementWithIndexWithTest() 
{
	vector* emptyVector = shopItemVector_create();
	shopItem_type* newShopItem = createShopItem(42, "microwave", "Apple", "MW-201", 550, 10);
	// the test cases are similar to ones from the remove operation
	shopItemVector_replaceElementWithIndexWith(emptyVector, 10, newShopItem);
	shopItemVector_destroy(emptyVector);
	vector* testVector = setUpStock();
	shopItemVector_replaceElementWithIndexWith(testVector, 5, newShopItem);
	// finally, we replace the second item
	shopItemVector_replaceElementWithIndexWith(testVector, 1, newShopItem);
	assert(GET_POINTER_SHOPITEM(testVector, 1)->id == 42);
	assert(GET_POINTER_SHOPITEM(testVector, 1)->price == 550);
	assert(GET_POINTER_SHOPITEM(testVector, 1)->quantity == 10);
	assert(shopItem_areSame(testVector->pointerToDataBlock[1], newShopItem));
	shopItemVector_destroy(testVector);
	return;
}

// This function is used for testing the sort function of the vector type
int compareShopItemsByPrice(shopItem_type* thisShopItem, shopItem_type* otherShopItem)
{
	if (thisShopItem->price <= otherShopItem->price)
		return TRUE;
	return FALSE;
}

void compareShopItemsByPriceTest()
{
	shopItem_type* shopItem1 = createShopItem(1,"smartphone","Apple","S10",500.0f,10);
	shopItem_type* shopItem2 = createShopItem(2,"smartphone","Apple","S11",600.0f,5);
	assert(compareShopItemsByPrice(shopItem1, shopItem2) == TRUE);
	assert(compareShopItemsByPrice(shopItem2, shopItem1) == FALSE);
	destroyShopItem(shopItem1);
	destroyShopItem(shopItem2);
	return;
}

void shopItemVector_sortTest()
{
	vector* testVector = setUpStock();
	compareShopItemsByPriceTest();
	// we sort in ascending order
	shopItemVector_sort(testVector, FALSE, compareShopItemsByPrice);
	assert(GET_POINTER_SHOPITEM(testVector, 0)->id == 1);
	assert(GET_POINTER_SHOPITEM(testVector, 1)->id == 4);
	assert(GET_POINTER_SHOPITEM(testVector, 2)->id == 3);
	assert(GET_POINTER_SHOPITEM(testVector, 3)->id == 2);
	// we sort in descending order
	shopItemVector_sort(testVector, TRUE, compareShopItemsByPrice);
	assert(GET_POINTER_SHOPITEM(testVector, 0)->id == 3);
	assert(GET_POINTER_SHOPITEM(testVector, 1)->id == 2);
	assert(GET_POINTER_SHOPITEM(testVector, 2)->id == 1);
	assert(GET_POINTER_SHOPITEM(testVector, 3)->id == 4);
	shopItemVector_destroy(testVector);
	return;
}

void runShopItemVectorTests()
{
	shopItemVector_createTest();
	pushBackTest();
	shopItemVector_removeElementWithIndexTest();
	getElementWithIndexTest();
	shopItemVector_replaceElementWithIndexWithTest();
	shopItemVector_sortTest();
	copyVectorTest();
	listOfListsTest();
	popUndoListTest();
	return;
}

// ------------------SERVICE TESTS----------------------



void service_addShopItemTest() {
	// we declare our validation flags for one item
	// Note: keep in mind that we must destroy the objects we created outside the service
	shopItemValidationFlags_type validationFlags;
	vector* shopItemVector_pointer = setUpStock();
	vector* undoListTest = shopItemVector_create();
	// we add an existing item 
	shopItem_type* shopItem1 = createShopItem(100,"smartphone","Apple","S10",500.0f,40);
	service_addShopItem(shopItemVector_pointer,undoListTest,100,"smartphone","Apple","S10",500.0f,40,&validationFlags);
	// we check if the quantity increased by 40
	shopItem_type* shopItem = getElementWithIndex(shopItemVector_pointer, 0);
	assert(shopItem_areSame(shopItem1, shopItem) == 1);
	assert(shopItem->quantity == 50);
	destroyShopItem(shopItem1);
	// we try to add an item with the same id with some item from the stock, but are not the same
	shopItem_type* shopItem2 = createShopItem(1,"smartphone","Apple","S",500.0f,40);
	service_addShopItem(shopItemVector_pointer,undoListTest,1,"smartphone","Apple","S",500.0f,40,&validationFlags);
	// we check that the item wasn t added
	assert(getSize(shopItemVector_pointer) == 4);
	destroyShopItem(shopItem2);
	// we try to add an invalid item (the flags will be set to 0)
	shopItem_type* invalidShopItem= createShopItem(-100,"SmartTv","","",500.0f,30);
	service_addShopItem(shopItemVector_pointer,undoListTest,-100,"SmartTv","","",500.0f,30,&validationFlags);
	// we check that the item wasn t added
	assert(getSize(shopItemVector_pointer) == 4);
	destroyShopItem(invalidShopItem);
	//finally we try to add a new item
	shopItem_type* newShopItem = createShopItem(5,"samrttv","Samsung","2k19",5000.0f,10);
	service_addShopItem(shopItemVector_pointer,undoListTest,5,"samrttv","Samsung","2k19",5000.0f,10,&validationFlags);
	shopItem_type* lastItem = getElementWithIndex(shopItemVector_pointer,4);
	assert(shopItem_areSame(lastItem, newShopItem));
	shopItemVector_destroy(shopItemVector_pointer);
	destroyShopItem(newShopItem);
	destroy(undoListTest, shopItemVector_destroy);
	return;
}

void service_updateShopItemTest()
{
	vector* shopItemVector_pointer = setUpStock();
	vector* undoVectorTest = shopItemVector_create();
	// we try to update an item which not exists
	service_updateShopItem(shopItemVector_pointer, undoVectorTest, 1000, 10.0f, 10);
	// we check that the items didn t change
	shopItem_type* shopItem1 = getElementWithIndex(shopItemVector_pointer, 0);
	shopItem_type* shopItem2 = getElementWithIndex(shopItemVector_pointer, 1);
	shopItem_type* shopItem3 = getElementWithIndex(shopItemVector_pointer, 2);
	shopItem_type* shopItem4 = getElementWithIndex(shopItemVector_pointer, 3);
	assert(shopItem1->price == (float)500.0f);
	assert(shopItem1->quantity == 10);
	assert(shopItem2->price == (float)600.0f);
	assert(shopItem2->quantity == 5);
	assert(shopItem3->price == (float)600.0f);
	assert(shopItem3->quantity == 20);
	assert(shopItem4->price == (float)500.0f);
	assert(shopItem4->quantity == 12);
	// now we update the item with id 1
	service_updateShopItem(shopItemVector_pointer,undoVectorTest, 1, (float)7.5, 1);
	shopItem1 = getElementWithIndex(shopItemVector_pointer, 0);
	assert(shopItem1->price == (float)7.5);
	assert(shopItem1->quantity == 1);
	shopItemVector_destroy(shopItemVector_pointer);
	destroy(undoVectorTest, shopItemVector_destroy);
	return;
}

void service_removeShopItemFromStockTest() 
{
	vector* shopItemVector_pointer = setUpStock();
	vector* undoListTest = shopItemVector_create();
	// we try to delete a item that doesn t exist
	service_removeShopItemFromStock(shopItemVector_pointer,undoListTest, 1000);
	// we check that the size of the stock is the same
	assert(getSize(shopItemVector_pointer) == 4);
	// we delete the item with id 2
	service_removeShopItemFromStock(shopItemVector_pointer,undoListTest, 2);
	// we check that the size decreased to 3
	assert(getSize(shopItemVector_pointer) == 3);
	// we check that the item has been removed
	for (size_t i = 0; i < 3; i++)
	{
		shopItem_type* curentItem = getElementWithIndex(shopItemVector_pointer, i);
		assert(curentItem->id != 2);
	}
	shopItemVector_destroy(shopItemVector_pointer);
	destroy(undoListTest, shopItemVector_destroy);
	return;
}

void service_sortStockItemsByPriceAndQuantityTest()
{
	vector* shopItemVector_pointer = setUpStock();
	// we sort the list in ascending order
	service_sortStockItemsByPriceAndQuantity(shopItemVector_pointer, FALSE);
	//we check that the items have been sorted in ascending order
	shopItem_type* shopItem1 = getElementWithIndex(shopItemVector_pointer, 0);
	shopItem_type* shopItem2 = getElementWithIndex(shopItemVector_pointer, 1);
	shopItem_type* shopItem3 = getElementWithIndex(shopItemVector_pointer, 2);
	shopItem_type* shopItem4 = getElementWithIndex(shopItemVector_pointer, 3);
	assert(shopItem1->id == 1);
	assert(shopItem2->id == 4);
	assert(shopItem3->id == 2);
	assert(shopItem4->id == 3);
	shopItemVector_destroy(shopItemVector_pointer);
	shopItemVector_pointer = setUpStock();
	service_sortStockItemsByPriceAndQuantity(shopItemVector_pointer, TRUE);
	shopItem1 = getElementWithIndex(shopItemVector_pointer, 0);
	shopItem2 = getElementWithIndex(shopItemVector_pointer, 1);
	shopItem3 = getElementWithIndex(shopItemVector_pointer, 2);
	shopItem4 = getElementWithIndex(shopItemVector_pointer, 3);
	assert(shopItem4->id == 1);
	assert(shopItem3->id == 4);
	assert(shopItem2->id == 2);
	assert(shopItem1->id == 3);
	shopItemVector_destroy(shopItemVector_pointer);
	return;
}

void service_filterStockItemsByManufacturerPriceOrQuantityTest() 
{
	vector* shopItemVector_pointer = setUpStock();
	// we filter the stock by the manufacturer
	vector* resultOfFiltration = shopItemVector_create();
	char manufacturerKey[] = "Apple";
	service_filterStockItemsByManufacturerPriceOrQuantity(shopItemVector_pointer, resultOfFiltration, "manufacturer",(char*)manufacturerKey);
	assert(getSize(resultOfFiltration) == 2);
	shopItem_type* item1 = getElementWithIndex(resultOfFiltration, 0);
	shopItem_type* item2 = getElementWithIndex(resultOfFiltration, 1);
	assert(item1->id == 1);
	assert(item2->id == 2);
	vector* resultOfFiltration2 = shopItemVector_create();
	// we filter the stock by price
	float priceKey = (float)550;
	void* pointerToKey = &priceKey;
	service_filterStockItemsByManufacturerPriceOrQuantity(shopItemVector_pointer,resultOfFiltration2,"price",(float*)pointerToKey);
	assert(getSize(resultOfFiltration2) == 2);
	item1 = getElementWithIndex(resultOfFiltration2, 0);
	item2 = getElementWithIndex(resultOfFiltration2, 1);
	assert(item1->id == 1);
	assert(item2->id == 4);
	vector* resultOfFiltration3 = shopItemVector_create();
	// we filter the stock by quantity
	int quantityKey = 15;
	pointerToKey = &quantityKey;
	service_filterStockItemsByManufacturerPriceOrQuantity(shopItemVector_pointer,resultOfFiltration3,"quantity",(int*)pointerToKey);
	assert(getSize(resultOfFiltration3) == 3);
	item1 = getElementWithIndex(resultOfFiltration3, 0);
	item2 = getElementWithIndex(resultOfFiltration3, 1);
	shopItem_type* item3 = getElementWithIndex(resultOfFiltration3, 2);
	assert(item1->id == 1);
	assert(item2->id == 2);
	assert(item3->id == 4);
	shopItemVector_destroy(resultOfFiltration);
	shopItemVector_destroy(resultOfFiltration2);
	shopItemVector_destroy(resultOfFiltration3);
	shopItemVector_destroy(shopItemVector_pointer);
	return;
}

void service_multipleFilterTest()
{
	vector* myVector = setUpStock();
	vector* resultFiltration = shopItemVector_create();
	char model[] = "S10";
	float price = 600.0f;
	void* pointerToPrice = &price;
	int quantity = 15;
	void* pointerToQuantity = &quantity;
	service_multipleFilter(myVector, resultFiltration, (char*)model, (float*)pointerToPrice, (int*)pointerToQuantity);
	assert(getSize(resultFiltration) == 1);
	assert(GET_POINTER_SHOPITEM(resultFiltration, 0)->id == 1);
	assert(strcmp(GET_POINTER_SHOPITEM(resultFiltration, 0)->manufacturer, "Apple") == 0);
	shopItemVector_destroy(resultFiltration);
	vector* result2 = shopItemVector_create();
	char model2[] = "S10";
	float price2 = 400.0f;
	pointerToPrice = &price2;
	int quantity2 = 15;
	pointerToQuantity = &quantity2;
	service_multipleFilter(myVector, resultFiltration, (char*)model2, (float*)pointerToPrice, (int*)pointerToQuantity);
	assert(getSize(result2) == 0);
	shopItemVector_destroy(result2);
	vector* result3 = shopItemVector_create();
	char model3[] = "S10";
	float price3 = 800.0f;
	pointerToPrice = &price3;
	int quantity3 = 2;
	pointerToQuantity = &quantity3;
	service_multipleFilter(myVector, resultFiltration, (char*)model3, (float*)pointerToPrice, (int*)pointerToQuantity);
	assert(getSize(result3) == 0);
	shopItemVector_destroy(result3);
	shopItemVector_destroy(myVector);
	return;
}

void serviceUndoTest()
{
	vector* myVector = setUpStock();
	vector* undoVectorTest = shopItemVector_create();
	shopItemValidationFlags_type validationFlags;
	pushBack(undoVectorTest, createCopyOfVector(myVector));
	service_addShopItem(myVector, undoVectorTest, 7, "smartphone", "Apple", "S", 500.0f, 40, &validationFlags);
	assert(getSize(myVector) == 5);
	assert(getSize(undoVectorTest) == 2);
	serviceUndo(&myVector, undoVectorTest);
	assert(getSize(undoVectorTest) == 1);
	assert(getSize(myVector) == 4);
	assert(GET_POINTER_SHOPITEM(myVector, 0)->id == 1);
	assert(GET_POINTER_SHOPITEM(myVector, 1)->id == 2);
	assert(GET_POINTER_SHOPITEM(myVector, 2)->id == 3);
	assert(GET_POINTER_SHOPITEM(myVector, 3)->id == 4);
	assert(strcmp(GET_POINTER_SHOPITEM(myVector, 0)->model,"S10")==0);
	shopItemVector_destroy(myVector);
	destroy(undoVectorTest, shopItemVector_destroy);
	return;}

void runServiceTests() 
{
	service_addShopItemTest();
	service_updateShopItemTest();
	service_removeShopItemFromStockTest();
	service_sortStockItemsByPriceAndQuantityTest();
	service_filterStockItemsByManufacturerPriceOrQuantityTest();
	serviceUndoTest();
	service_multipleFilterTest();
	return;
}

//-------------------------------UTILS TESTS----------------------------------

void stripSpacesFromStringTest() {
	char string1[] = "     ";
	char string2[] = "1     ";
	char string3[] = "   1231";
	char string4[] = "absvdsas 122343";
	char string5[] = "  adsafa   ";

	stripSpacesFromString(string1);
	stripSpacesFromString(string2);
	stripSpacesFromString(string3);
	stripSpacesFromString(string4);
	stripSpacesFromString(string5);

	assert(strlen(string1) == 0);

	assert(strlen(string2) == 1);
	assert(strcmp(string2, "1") == 0);
	
	assert(strlen(string3) == 4);
	assert(strcmp(string3, "1231") == 0);

	assert(strlen(string4) == 15);
	assert(strcmp(string4, "absvdsas 122343") == 0);

	assert(strlen(string5) == 6);
	assert(strcmp(string5, "adsafa") == 0);

	return;
}
void isStringIntegerTest()
{
	char string1[] = "1234567";
	char string2[] = "";
	char string3[] = "1";
	char string4[] = "absvdsas 122343";
	char string5[] = "12312.232 adsafa";
	char string6[] = "-122323";
	char string7[] = "-121-123";
	char string8[] = "123-1231";

	assert(isStringInteger(string1) == TRUE);
	assert(isStringInteger(string2) == FALSE);
	assert(isStringInteger(string3) == TRUE);
	assert(isStringInteger(string4) == FALSE);
	assert(isStringInteger(string5) == FALSE);

	assert(isStringInteger(string6) == TRUE);
	assert(isStringInteger(string7) == FALSE);
	assert(isStringInteger(string8) == FALSE);
	
	return;
}

void isStringFloatTest() {
	char string1[] = "123.3434";
	char string2[] = ".4556";
	char string3[] = "123.23423.123";
	char string4[] = "1234 aksdfd";
	char string5[] = "laskda";
	char string6[] = "1231.";
	char string7[] = "123.-23";

	assert(isStringFloat(string1) == TRUE);
	assert(isStringFloat(string2) == FALSE);
	assert(isStringFloat(string3) == FALSE);
	assert(isStringFloat(string4) == FALSE);
	assert(isStringFloat(string5) == FALSE);
	assert(isStringFloat(string6) == FALSE);
	assert(isStringFloat(string7) == FALSE);
	return;
}

void runUtilsTests()
{
	stripSpacesFromStringTest();
	isStringIntegerTest();
	isStringFloatTest();

	return;
}

void runAllTests()
{
	runDomainTests();
	runShopItemVectorTests();
	runServiceTests();
	runUtilsTests();

	printf("All tests passed! :D \n");
	return;
}
