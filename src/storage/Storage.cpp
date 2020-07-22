#include <QDir>
#include <QDebug>

#include "Storage.hpp"

Storage::Storage(){
	this->__appdb = new Appdb();
}


/**
 * @brief Storage::create - создание хранилища
 * @param path
 * @return
 */
bool Storage::create(const QString &path)
{

	//--- create storage directory
	if(QDir(path).exists()){
		return false;
	}
	QDir().mkdir(path);


	//--- create storage manifest
	this->manifest = new StorageManifest(path);
	this->manifest->write();




//	int r = std::mkdir(path.toStdString(), 0777);

	return true;
}

bool Storage::open(const QString &path){
	this->path = path;
	this->manifest = new StorageManifest(path);
	auto r = this->manifest->read();
	if(r){
		this->manifest->print();
	}
	return r;
}

bool Storage::save(){
	this->manifest->write();
}

VolumePtr Storage::open_volume(const QString &vol_id)
{

	QString vol_path = QDir(this->path).filePath(vol_id + ".vol");
	Volume vol = Volume(vol_path);
	qDebug() << "storage - open volume: " << vol_path;

	vol.open();
	vol.root.reprint(0);
	return std::make_shared<Volume>(vol);
}








bool Storage::open_db(const QString &full_path){

	//--- закрываем перед новым открытием
	if(this->__appdb->is_opened){
		this->__appdb->close_db();
	}
    return __appdb->open_db(full_path);
}

bool Storage::close_db(){
	this->__appdb->close_db();
}

Volumes Storage::get_volumes(){
	return __appdb->get_volumes();
}

VolumeModel Storage::get_volume(const  QString &volume_id)
{
	return this->__appdb->get_volume(volume_id);
}

Files Storage::get_volume_files(QString &volume_id){
    return __appdb->get_volume_files(volume_id);
}

Files Storage::get_child_files(QString &parent_id){
	return __appdb->get_child_files(parent_id);
}

DBSystem Storage::get_db_system_info(){
	return __appdb->db_system_info;
}

bool Storage::create_volume(const VolumeModel &model){
	return this->__appdb->create_volume_record(model);
}

bool Storage::create_file(const FileModel &model){
	return this->__appdb->create_file_record(model);
}

bool Storage::remove_volume(const QString &volume_id){
	bool r1 = __appdb->remove_volume_files(volume_id);
	bool r2 = __appdb->remove_volume_record(volume_id);

	return r1 && r2;
}

bool Storage::update_volume(const VolumeModel &volume)
{
	return this->__appdb->update_volume_record(volume);
}

void Storage::start_transaction()
{
	__appdb->start_transaction();
}

void Storage::end_transaction()
{
	__appdb->end_transaction();
}
