#include "coreProgram/file.h"

File::File(std::string n, int s):blockList() {
	name = n;
	size = s;
}

File::File(File const& source)
	:name(source.name),size(source.size),blockList(source.blockList)
{

}

File::~File()
{
}

void File::addBlock(block* b)
{
	blockList.insertAtEnd(b);
}

void File::operator=(File const& s)
{
	blockList = s.blockList;
	name = s.name;
	size = s.size;
}

