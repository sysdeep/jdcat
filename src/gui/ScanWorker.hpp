#ifndef SCANWORKER_HPP
#define SCANWORKER_HPP
#include <QObject>
#include <QString>
#include <QDir>
#include "../storage/Storage.hpp"
#include "core/models/FileModel.hpp"


/*
 * http://blog.harrix.org/article/4826
*/

class ScanWorker : public QObject
{
Q_OBJECT
public:
	ScanWorker(Storage *storage);
	ScanWorker(Storage *storage, const QString &path, const QString &volume_id);

public slots:
	void start();
	void set_path(const QString&);
	void set_volume_id(const QString&);
	void stop();


signals:
	void prescan_finished(int);
	void current_counter(int);
	void scan_finished();
	void finished();


private:
	QString __path;
	QString __volume_id;
	Storage *__storage;

	int __files_count = 0;
	int __folders_count = 0;
	int __current_count = 0;

	void __prescan(QDir dir);
	void __scan_dir(QDir dir, QString parent_id, QString volume_id);
	void __inc_current_counter();

	bool __is_need_stop = false;
};

#endif // SCANWORKER_HPP
