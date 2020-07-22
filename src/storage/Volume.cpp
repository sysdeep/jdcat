#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include "Volume.hpp"

Volume::Volume(const QString &ipath){
	this->path = ipath;
}

bool Volume::open(){

	QFile file(this->path);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		qDebug() << "vol - unable open file to read: " << this->path;
		return false;
	}


	QByteArray saveData = file.readAll();


	// TODO: parse error
	QJsonDocument doc(QJsonDocument::fromJson(saveData));


	this->__from_json(doc);

	return true;


	return true;
}

void Volume::__from_json(const QJsonDocument &doc){

	QJsonObject doc_obj = doc.object();

	if(doc_obj.contains("root")){
//		this->version = root.value("version").toInt();

		this->root = Node();

	}


	this->root.from_json(doc_obj.value("root").toObject(), true);


//	if(doc_obj.contains("description")){
//		this->description = root.value("description").toString();
//	}
}


