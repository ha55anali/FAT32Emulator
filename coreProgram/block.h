#pragma once
#include "coreProgram/list.h"
#include <iostream>

class block{
public:
	//parameters in sector unit
	block(int total, int start);
	block(block const&);
	~block();

	int getstart();
	void setstart(int);
	int getTotal();
	void setTotal(int);

	block& operator=(block const&);
	friend std::ostream& operator<<(std::ostream& s, block const&);
private:
	int start_sector_ID;
	int total_sectors;
};
