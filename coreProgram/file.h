#pragma once
#include "coreProgram/list.h"
#include <string>
#include "coreProgram/block.h"
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
    friend std::ostream& operator<<(std::ostream& os, File & f){
        using namespace std;
        cout << "file name:" << f.name << "	";
        cout << "file size:" << f.size << "	";
        cout << "blocks: ";
        f.blockList.print();

        return os;
    }
private:
	std::string name;
	int size;
	sList<block*> blockList;
};
