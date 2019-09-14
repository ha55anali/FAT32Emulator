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

std::ostream& operator<<(std::ostream& os, File const& f)
{
	using namespace std;
	cout << "file name:" << f.name << "	";
	cout << "file size:" << f.size << "	";
	cout << "blocks: ";
	f.blockList.print();

	return os;
}
