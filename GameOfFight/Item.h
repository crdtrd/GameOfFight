#pragma once

#include <string>

using namespace std;

#ifndef ITEM_H
#define ITEM_H

class Item
{
protected:
	string name;
	string description;
	int worth;

public:
	Item();
	Item(string name, string description, int worth);

	void setName(string name);
	string getName() const;

	void setDescription(string description);
	string getDescription() const;

	void setWorth(int worth);
	int getWorth() const;

};

#endif // !ITEM_H