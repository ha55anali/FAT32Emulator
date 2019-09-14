#pragma once

#include "block.h"
#include "list.h"
#include "file.h"

#include <string>

class fileSystem {
public:
	fileSystem(int sectors, int sectorSize);
	~fileSystem();

	//throws invalid argument
	void saveFile(std::string fname, std::string fcontent, int fsize);
	void deleteFile(std::string fname);
	std::string readFile(std::string fname);

	friend std::ostream& operator<<(std::ostream& os, fileSystem &);
	void printDisk();
private:
	sList<block*> pool;//sorted
	sList<File*> files;
	char* disk;
	int numOfSectors;
	int numOfSectPool;
	int sizeOfSectors;

	void allocateSector(int& FileSectLeft, File* tempFile, std::string content);
	void writeToDisk(int startSector, int sizeinSector, std::string content);
	void insertBlockinPool(block*);
	void mergePoolBlocks();
	std::string readDisk(int startSector, int sizeinSector);
};