#include "coreProgram/fileSystem.h"
#include <cmath>
#include <iostream>

fileSystem::fileSystem(int sectors, int sectorSize)
{
	numOfSectors = sectors;
	sizeOfSectors = sectorSize;
	numOfSectPool = numOfSectors;

	//new block with all available sectors
	block* temp = new block(sectors,0);
	pool.insertAtStart(temp);

	//initialize disk
	int sizeDisk = numOfSectors * sizeOfSectors;
	disk = new char[sizeDisk+1];
}

fileSystem::~fileSystem()
{
	delete[] disk;
	for (sList<block*>::iterator it = pool.begin(); it != pool.end(); ++it) {
		delete* it;
	}
	for (sList<File*>::iterator it = files.begin(); it != files.end(); ++it) {
		delete* it;
	}
}

void fileSystem::saveFile(std::string fname, std::string fcontent, int fsize)
{
	//checks if space in pool
	int fileSectors = ceil(float(fsize) / float(sizeOfSectors));
	if (fileSectors > numOfSectPool) 
		throw std::invalid_argument("not enough free space");
	else {
		//checks if filename unique
		bool uniqueName = 1;
		File* tempFile;
		for (sList<File*>::iterator it = files.begin(); it != files.end();++it) {//int i = 0; i < files.getSize(); ++i) {
			if (fname == it->getName()) {
				uniqueName = 0;
				break;
			}
		}

		if (uniqueName==0) 
			throw std::invalid_argument("file name not unique");
		else {
			File* tempFile = new File(fname, fileSectors);
			files.insertAtEnd(tempFile);

			int fileSectLeft = fileSectors;

			while (fileSectLeft > 0) {
				allocateSector(fileSectLeft, tempFile, fcontent);
			}
		}
	}
}

void fileSystem::deleteFile(std::string fname)
{
	//find file
	File* tempFile=nullptr;
	bool Filefound = 0;
	for (sList<File*>::iterator it = files.begin(); it != files.end();++it) {
		tempFile = *it;
		if (tempFile->getName() == fname) {
			Filefound = 1;
			break;
		}
	}

	if (Filefound == 0) throw std::invalid_argument("file with name doesnt exist");
	else {
		block* tempBlock;
		for (sList<block*>::iterator it = tempFile->blockList.begin(); it != tempFile->blockList.end(); ) {
			tempBlock = *it;
			tempFile->blockList.removeWithoutDel(tempBlock);
			//insert tempBlock in pool
			insertBlockinPool(tempBlock);
		}

		mergePoolBlocks();

		delete tempFile;
		files.remove(tempFile);
	}
}

std::string fileSystem::readFile(std::string fname)
{
	File* tempFile = nullptr;
	bool fileFound = 0;
	for (sList<File*>::iterator it = files.begin(); it != files.end(); ++it){
		tempFile = *it;
		if (tempFile->getName() == fname) {
			fileFound = 1;
			break;
		}
	}

	if (fileFound == 0) throw std::invalid_argument("file doesnt exist");
	else {
		std::string str;
		block* tempBlock = nullptr;
		for (sList<block*>::iterator it = tempFile->blockList.begin(); it != tempFile->blockList.end(); ++it) {
			tempBlock = *it;
			str.append(readDisk(tempBlock->getstart(),tempBlock->getTotal()));
		}

		return str;
	}
	return std::string();
}

void fileSystem::printDisk()
{
	for (int i = 0; i < numOfSectors * sizeOfSectors; ++i) {
		if (disk[i] == '\0') std::cout << "/";
		else std::cout << disk[i];
	}
}

void fileSystem::allocateSector(int& FileSectLeft, File* tempFile, std::string content)
{
	block* poolBlock = pool[0];

	//block in pool bigger than needed
	if (poolBlock->getTotal() > FileSectLeft) {
		block* tempBlock = new block(FileSectLeft, poolBlock->getstart());
		poolBlock->setstart(poolBlock->getstart() + FileSectLeft);
		poolBlock->setTotal(poolBlock->getTotal() - FileSectLeft);
		numOfSectPool -= FileSectLeft;
		tempFile->addBlock(tempBlock);
		FileSectLeft = 0;
		writeToDisk(tempBlock->getstart(), tempBlock->getTotal(),content);
	}
	//equal or smaller than needed
	else {
		pool.removeWithoutDel(poolBlock);
		tempFile->addBlock(poolBlock);
		numOfSectPool -= FileSectLeft;
		FileSectLeft -= poolBlock->getTotal();
		writeToDisk(poolBlock->getstart(), poolBlock->getTotal(),content);
	}
}

void fileSystem::writeToDisk(int startSector, int sizeinSector, std::string content)
{
	int start = startSector * sizeOfSectors;
	int size=sizeinSector* sizeOfSectors;
	int stringSize = content.size();
	for (int i = 0; i < size; ++i) {
		if (i < stringSize) {
			disk[start + i] = content[0];
			content = content.substr(1); //O(N)
		}
		else disk[start + i] = '\0';
	}
}

void fileSystem::insertBlockinPool(block* b)
{
	block* tempBlock = nullptr;
	bool inserted = 0;
	for (int i = 0; i < pool.getSize(); ++i) {
		tempBlock = pool[i];
		
		if (tempBlock->getstart() > b->getstart()) {
			if (i == 0) pool.insertAtStart(b);
			else pool.insertAfter(b,pool[i - 1]);
			numOfSectPool += b->getTotal();
			inserted = 1;
			break;
		}
	}
	if (inserted == 0) {
		pool.insertAtEnd(b);
		numOfSectPool += b->getTotal();
	}
}

void fileSystem::mergePoolBlocks()
{
	block* temp0 = nullptr;
	block* temp1 = nullptr;
	for (int i = 0; i < pool.getSize() - 1; ++i) {
		temp0 = pool[i];
		temp1 = pool[i + 1];
		if (temp0->getstart() + temp0->getTotal() == temp1->getstart()) {
			temp0->setTotal(temp0->getTotal() + temp1->getTotal());
			delete temp1;
			pool.remove(temp1);
			--i;
		}
	}
}

std::string fileSystem::readDisk(int startSector, int sizeinSector)
{
	int start = startSector * sizeOfSectors;
	int size = sizeinSector * sizeOfSectors;
	char* temp = new char[size + 1];

	for (int i = 0; i < size; ++i) {
		temp[i]=disk[start + i];
		temp[i + 1] = '\0';
	}
	return temp;
}

std::ostream& operator<<(std::ostream& os, fileSystem & fS)
{
	std::cout << "==================================" << std::endl;
	std::cout << "pool:" << std::endl << "_______________________" << std::endl;
	for (int i = 0; i < fS.pool.getSize(); ++i) {
		std::cout << *(fS.pool[i]) << std::endl;
	}
	std::cout << std::endl;
	std::cout << "files:"<<std::endl << "_______________________" << std::endl;
	for (int i = 0; i < fS.files.getSize(); ++i) {
		std::cout << *(fS.files[i]) << std::endl;
	}
	std::cout << std::endl;
	std::cout << "disk:	"<<std::endl<< "_______________________" << std::endl;
	fS.printDisk();
	std::cout<< std::endl << "_______________________" << std::endl;;
	std::cout <<"Total sectors: "<< fS.numOfSectors<< std::endl;
	std::cout << "Sectors in pool: " << fS.numOfSectPool << std::endl;
	std::cout << "pool: ";
	for (sList<block*>::iterator it = fS.pool.begin(); it != fS.pool.end(); ++it) {
		std::cout << **it << "||";
	}
	std::cout << std::endl<<"===================================" << std::endl;
	return os;
}
