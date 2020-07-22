#ifndef FILEMODEL_HPP
#define FILEMODEL_HPP
#include <list>
#include <QString>

/*
 * self.volume_id	= ""
		self.parent_id	= ""
		self.uuid	= ""
		self.name	= ""
		self.ftype	= 0

		self.rights	= 0

		self.owner	= ""
		self.group	= ""

		self.ctime	= 0
		self.atime	= 0
		self.mtime	= 0

		self.category	= 0
		self.description	= ""

		self.size	= 0


		self.parents = []					# спсиок родителей для рекурсивного поиска

*/

class FileModel
{
public:
	FileModel();

	QString volume_id;
	QString parent_id;
	QString uuid;
	QString name;
	int ftype = 0;				// 0 - folder, 1 - file
	unsigned int size = 0;

//	self.rights	= 0

//	self.owner	= ""
//	self.group	= ""

//	self.ctime	= 0
//	self.atime	= 0
//	self.mtime	= 0

//	self.category	= 0
//	self.description	= ""

	QString		formatted_size();

private:
	double roundOff(double n);
};



using Files = std::list<FileModel>;

#endif // FILEMODEL_HPP
