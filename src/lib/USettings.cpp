#include <QDebug>
#include <QDir>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "USettings.hpp"

/**
 * https://doc.qt.io/qt-5/qtcore-serialization-savegame-example.html
 */






USettings::USettings(const QString dirname, const QString filename){

	this->dir_name = dirname;
	this->file_name = filename;

	//--- check exists
	auto file_path = this->__expand_file_path();
	QDir fp;
	if(!fp.exists(file_path)){
        qDebug() << file_path;
		qDebug() << "!exists";

        bool init_dir_result = this->__init_path();
        if(init_dir_result == false){
            qDebug() << "Error - unable create settings dir...";
        }else{
            qDebug() << "created settings dir, store default settings...";
            this->save();
        }
	}else{
		qDebug() << "exists";
		this->read();
	}

}

bool USettings::read(){

	auto full_file_path = this->__expand_file_path();
	qDebug() << "full config path: " << full_file_path;


	QFile sfile(full_file_path);

	if(!sfile.open(QIODevice::ReadOnly)){
		qWarning("unable open file...");
		return false;
	}

	QByteArray file_data = sfile.readAll();
	sfile.close();
	QJsonDocument json_doc(QJsonDocument::fromJson(file_data));

	bool result = this->__read_json(json_doc.object());


	if(result){
		return true;
	}else{
		return false;
	}

}

bool USettings::save(){
	auto full_file_path = this->__expand_file_path();

	QFile sfile(full_file_path);
	if(!sfile.open(QIODevice::WriteOnly)){
		qWarning("unable open file...");
		return false;
	}

	QJsonObject data = this->__write_json();
	QJsonDocument json_doc(data);

	sfile.write(json_doc.toJson());
	sfile.close();

	return false;
}

bool USettings::last_database_exists(){
	if(!this->data.lastbases.isEmpty()){

		QDir fp;
		auto base_path = this->get_last_database();
		return fp.exists(base_path);

	}else{
		return false;
	}
}

QString USettings::get_last_database(){
    return this->data.lastbases.last();
}

/**
 * @brief USettings::add_database - добавить базу в историю
 * @param db_path - полный путь до базы
 * @return
 */
bool USettings::add_database(const QString &db_path){

    //--- если такой путь уже есть в списке - удаляем его
    if(this->data.lastbases.contains(db_path)){
        this->data.lastbases.removeAll(db_path);
    }

    //--- заносим путь в конец списка
    this->data.lastbases.push_back(db_path);
    this->save();
    return true;
}

QString USettings::__expand_file_path(){

    QString full_path = QDir::toNativeSeparators(QDir::homePath()) + QDir::separator() + this->dir_name + QDir::separator() + this->file_name;

	return full_path;
}






bool USettings::__read_json(const QJsonObject &json){
	if(json.contains("version")){
		this->data.version = json["version"].toString();
	}

	if(json.contains("open_last")){
		bool result;
		if(json["open_last"].isBool()){
			result = json["open_last"].toBool();

		}else{
			int r = json["open_last"].toInt();
			result = r==1? true : false;
		}
		this->data.open_last = result;
	}

	if(json.contains("max_last_bases")){
		this->data.max_last_bases = json["max_last_bases"].toInt();
	}

	if(json.contains("lastbases")){
		QJsonArray bases = json["lastbases"].toArray();
		for(auto base : bases){

			this->data.lastbases.append(base.toString());
		}
	}

	return true;

}

/**
 * @brief USettings::__write_json - записать данные настроек в json
 * @return
 */
QJsonObject USettings::__write_json(){

	QJsonObject result;
	result["version"] = this->data.version;
	result["open_last"] = this->data.open_last;
	result["max_last_bases"] = this->data.max_last_bases;

	QJsonArray bases;
	for(const auto &base_path : this->data.lastbases){
		bases.append(base_path);
	}

	result["lastbases"] = bases;

	return result;
}


/**
 * @brief USettings::__init_path - init path on settings is not exeists
 * @return
 */
bool USettings::__init_path(){
    QDir base_path = QDir(QDir::home());
    return base_path.mkdir(this->dir_name);
}

