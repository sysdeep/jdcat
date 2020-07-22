#include <QDebug>
#include <QUuid>
#include "ScanWorker.hpp"

ScanWorker::ScanWorker(Storage *storage)
{
	this->__storage = storage;
}

ScanWorker::ScanWorker(Storage *storage, const QString &path, const QString &volume_id)
{
	this->__storage = storage;
	this->__path = path;
	this->__volume_id = volume_id;
	this->__is_need_stop = false;
}

void ScanWorker::start(){

	QDir dir(this->__path);

	//--- prescan
	this->__prescan(dir);



	int total_files = this->__files_count + this->__folders_count;

	emit prescan_finished(total_files);

	if(this->__is_need_stop){
		emit scan_finished();
		emit finished();
		return;
	}

	//--- scan
	this->__storage->start_transaction();
	this->__scan_dir(dir, "0", this->__volume_id);
	this->__storage->end_transaction();

	emit scan_finished();
	emit finished();



}

void ScanWorker::set_path(const QString &path){
	qDebug() << "set path: " << path;
	this->__path = path;
}

void ScanWorker::set_volume_id(const QString &volume_id){
	this->__volume_id = volume_id;
}


/**
 * @brief ScanWorker::stop - stop scaning
 */
void ScanWorker::stop(){
	this->__is_need_stop = true;
}

void ScanWorker::__prescan(QDir dir){

	//--- files
	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
	QStringList files = dir.entryList();
	this->__files_count += files.count();

	//--- folders
	dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
	QStringList folders = dir.entryList();
	this->__folders_count += folders.count();
	for(int i=0; i<folders.count(); i++){

		QString newPath = QString("%1/%2").arg(dir.absolutePath()).arg(folders.at(i));
		this->__prescan(QDir(newPath));
	}
}






void ScanWorker::__scan_dir(QDir dir, QString parent_id, QString volume_id)
{
	if(this->__is_need_stop){
		return;
	}



	//--- files
	qDebug() << "--- files ---";
	dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
	QStringList files = dir.entryList();
	for(int i=0; i<files.count(); i++){





		FileModel model = FileModel();
		model.name = files[i];
		model.uuid = QUuid::createUuid().toString().replace("{", "").replace("}", "");
		model.parent_id = parent_id;
		model.ftype = 1;
		model.volume_id = volume_id;


		QString full_path = QString("%1/%2").arg(dir.absolutePath()).arg(files[i]);
		QFileInfo file_info(full_path);

		qDebug() << full_path << " : " << file_info.size();

		model.size = static_cast<unsigned int>(file_info.size());

//		qDebug() << model.parent_id << ":" << model.uuid << " - " << model.name;
		this->__storage->create_file(model);
		this->__inc_current_counter();

//		qDebug() << files[i];
//		qDebug() << QUuid::createUuid();
	}



	//--- folders
	qDebug() << "--- folders ---";
	dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
	QStringList folders = dir.entryList();
	for(int i=0; i<folders.count(); i++){


		FileModel model = FileModel();
		model.name = folders[i];
		model.uuid = QUuid::createUuid().toString().replace("{", "").replace("}", "");
		model.parent_id = parent_id;
		model.ftype = 0;
		model.volume_id = volume_id;



		this->__storage->create_file(model);
		this->__inc_current_counter();





		qDebug() << folders[i];

		QString newPath = QString("%1/%2").arg(dir.absolutePath()).arg(folders.at(i));
		__scan_dir(QDir(newPath), model.uuid, volume_id);
	}
}

void ScanWorker::__inc_current_counter()
{
	this->__current_count++;
	emit current_counter(this->__current_count);
}
