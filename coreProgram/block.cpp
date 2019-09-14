#include "block.h"

block::block(int total, int start){
	total_sectors = total;
	start_sector_ID = start;
}

block::block(block const& b)
{
	start_sector_ID = b.start_sector_ID;
	total_sectors = b.total_sectors;
}

block::~block()
{
}

int block::getstart()
{
	return start_sector_ID;
}

void block::setstart(int n)
{
	start_sector_ID = n;
}

int block::getTotal()
{
	return total_sectors;
}

void block::setTotal(int n)
{
	total_sectors = n;
}


block& block::operator=(block const& b)
{
	start_sector_ID = b.start_sector_ID;
	total_sectors = b.total_sectors;
	return *this;
}

std::ostream& operator<<(std::ostream& s, block const& b)
{
	std::cout << "start:" << b.start_sector_ID;
	std::cout << "	size:" << b.total_sectors;
	return s;
}
