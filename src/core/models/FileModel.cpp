#include "FileModel.hpp"

FileModel::FileModel()
{

}



//--- http://programanddesign.com/cpp/human-readable-file-size-in-c/
//char* readable_fs(double size/*in bytes*/, char *buf) {
//    int i = 0;
//    const char* units[] = {"B", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
//    while (size > 1024) {
//        size /= 1024;
//        i++;
//    }
//    sprintf(buf, "%.*f %s", i, size, units[i]);
//    return buf;
//}

//// usage
//struct stat info;
//char buf[10];
//lstat("somefile.txt", &info);
//printf("File size: %s\n", readable_fs(info.st_size, buf));



//--- http://memoirsofacoder.blogspot.com/2014/08/c-get-file-size-in-kbmbgb-format.html
QString FileModel::formatted_size(){
	static const char *SIZES[] = { "B", "KB", "MB", "GB" };
	unsigned int div = 0;
	size_t rem = 0;

	while (this->size >= 1024 && div < (sizeof SIZES / sizeof *SIZES)) {
		rem = (this->size % 1024);
		div++;
		this->size /= 1024;
	}

	double size_d = static_cast<double>(this->size) + rem / 1024.0;

	QString val = QString::number(roundOff(size_d));

//    QString result = convertToString(roundOff(size_d)) + " " + SIZES[div];
	QString result = val + " " + SIZES[div];
	return result;
}

double FileModel::roundOff(double n)
{
	double d = n * 100.0;
	   int i = d + 0.5;
	   d = (float)i / 100.0;
	   return d;
}
