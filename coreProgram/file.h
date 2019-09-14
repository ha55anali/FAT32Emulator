#pragma once
#include "list"
#include <string>
#include "block.h"
#include <iostream>

class File {
	//access blockList
	friend class fileSystem;
public:
	File(std::string name, int size);
	File(File const&);
	~File();
	
	void addBlock(block*);
	std::string getName() { return name; };

	block& getBlock(int n);

	void operator=(File const&);
	friend std::ostream& operator<<(std::ostream& os, File &);
private:
	std::string name;
	int size;
	sList<block*> blockList;
};
