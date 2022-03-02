// This file contains all the constants used in the program

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// this is used in the utils file 
#define MAX_STRING_SIZE 255

// these are used in the vector implementation
#define RESIZE_FACTOR 2
#define INITIAL_CAPACITY 1

// these are bool values used in the program
#define TRUE 1
#define FALSE 0

// these are used in the ui
#define BUFFER_SIZE 255
#define FILTER_SIZE 20


// this is the actual number of commands; for now, it is set to 9
#define NUMBER_OF_COMMANDS 12

// the value of one ui command must be greater or equal than 1 and smaller than NUMBER_OF_COMMANDS
#define ADD_SHOP_ITEM_COMMAND 1
#define UPDATE_SHOP_ITEM_COMMAND 2
#define REMOVE_SHOP_ITEM_COMMAND 3
#define SORT_STOCK_COMMAND	 4
#define FILTER_STOCK_COMMAND 5
#define MULTIPLE_FILTER 6
#define SET_ORDER_COMMAND 7
#define SET_FILTER_COMMMAND 8
#define UNDO_COMMAND 9
#define FILTER_SORT 10
#define PRINT_MENIU_COMMAND 11
#define EXIT_COMMAND 12

#endif
