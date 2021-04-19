#pragma once

#include "Item.h" // Item includes string and namespace std
#include <vector>

#ifndef SHOP_H
#define SHOP_H

class Shop
{
private:
	vector<Item> items;

public:
	Shop();

	void clearStock();
	void stockItems();
	
	void selectItem(int itemIndex);

	Item sellItem();
	void recieveItem(Item i);

};
#endif // !SHOP_H


/////// PROLLY NOT USING THIS