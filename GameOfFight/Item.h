#pragma once

#include <string>

using namespace std;

#ifndef ITEM_H
#define ITEM_H

class Item
{
protected:
	string name;
	int worth;

public:
	Item();
	Item(string name, int worth);

	void setName(string name);
	string getName() const;

	void setWorth(int worth);
	int getWorth() const;

	virtual string toString() const;

	virtual ~Item(); // added this for dynamic casting. really should add this for everything
};

#endif // !ITEM_H