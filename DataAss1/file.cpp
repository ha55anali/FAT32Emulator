#include "file.h"

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
	for (sList<block*>::iterator it = blockList.begin(); it != blockList.end(); ++it) {
		delete *it;
	}
}

void File::addBlock(block* b)
{
	blockList.insertAtEnd(b);
}

block& File::getBlock(int n)
{
	return *blockList[n];
}

void File::operator=(File const& s)
{
	blockList = s.blockList;
	name = s.name;
	size = s.size;
}

std::ostream& operator<<(std::ostream& os, File & f)
{
	using namespace std;
	cout << "file name:" << f.name << "	";
	cout << "file size:" << f.size << "	";
	cout << "blocks: ";
	for (sList<block*>::iterator it = f.blockList.begin(); it != f.blockList.end(); ++it) {
		cout << **it << "||";
	}

	return os;
}
