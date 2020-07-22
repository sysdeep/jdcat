#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QList>
#include <iostream>
#include "StorageManifest.hpp"

StorageManifest::StorageManifest(const QString &ipath)
{
	this->path = QDir(ipath).filePath("manifest");

	qDebug() << this->path;
}

bool StorageManifest::write(){
	QFile file(this->path);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
		qDebug() << "unable open file to write: " << this->path;
		return false;
	}

	QJsonDocument doc = this->__to_json();

	file.write(doc.toJson());

	return true;
}



bool StorageManifest::read()
{
	QFile file(this->path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug() << "unable open file to read: " << this->path;
		return false;
	}


	QByteArray saveData = file.readAll();


	// TODO: parse error
	QJsonDocument doc(QJsonDocument::fromJson(saveData));


	this->__from_json(doc);

	return true;
//	auto root = doc.object();
//	if(root.contains("version")){

//		auto version = root.value("version").toInt();
//		qDebug() << "read manifest version: " << version;
//	}else{
//		qDebug() << "read manifest - no version!!!";
//	}


}

void StorageManifest::print(){
	std::cout << "manifest info" << std::endl;
	std::cout << "path: " << this->path.toStdString() << std::endl;
	std::cout << "version: " << this->version << std::endl;
	std::cout << "description: " << this->description.toStdString() << std::endl;

}



/**
 * @brief StorageManifest::__from_json - parse json and fill model
 */
void StorageManifest::__from_json(const QJsonDocument &doc)
{
	QJsonObject root = doc.object();

	if(root.contains("version")){
		this->version = root.value("version").toInt();
	}

	if(root.contains("description")){
		this->description = root.value("description").toString();
	}

	if(root.contains("volumes") && root["volumes"].isArray()){

		QJsonArray volumes_array = root["volumes"].toArray();
//		for(int i=0; i<volumes_array.size(); ++i){
//			auto q = volumes_array[i].toObject();
//			std::cout << "ddd" << std::endl;
//			std::cout << q.value("name").toString().toStdString() << std::endl;
//		}
		for(auto jvolume : volumes_array){
			auto q = jvolume.toObject();
//			std::cout << q.value("name").toString().toStdString() << std::endl;

			StorageManifestVolume vol_obj = StorageManifestVolume();
			vol_obj.from_json(q);
//			vol_obj.print();
			this->volumes.append(vol_obj);
		}

//		this->description = root.value("description").toString();
	}else{
		qDebug() << "no volumes!!!";
	}

}

QJsonDocument StorageManifest::__to_json(){

	auto root = QJsonObject();
	root["version"] = this->version;
	root["description"] = this->description;


	//--- array example
//	QJsonArray levelArray;
//	levelArray.append(QJsonObject());
//	for (const Level &level : mLevels) {
//		QJsonObject levelObject;
////			level.write(levelObject);
//			levelArray.append(levelObject);
//		}
//	root["levels"] = levelArray;



	return QJsonDocument(root);
}








//void StorageManifest::read_file(const QString &path)
//{

//}

//void StorageManifest::write_file(const QString &path)
//{

//}
