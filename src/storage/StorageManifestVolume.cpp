#include <iostream>
#include "StorageManifestVolume.hpp"

StorageManifestVolume::StorageManifestVolume()
{

}

void StorageManifestVolume::from_json(const QJsonObject &data)
{


	if(data.contains("name")){
		this->name = data.value("name").toString();
	}

	if(data.contains("id")){
		this->id = data.value("id").toString();
	}

	if(data.contains("icon")){
		this->icon = data.value("icon").toInt();
	}

}

QJsonObject StorageManifestVolume::to_json()
{
	auto root = QJsonObject();
	root["name"] = this->name;
	root["id"] = this->id;
	root["icon"] = this->icon;
	return root;
}

void StorageManifestVolume::print()
{
	std::cout << "------------------" << std::endl;
	std::cout << "vol manifest info" << std::endl;
	std::cout << "id: " << this->id.toStdString() << std::endl;
	std::cout << "name: " << this->name.toStdString() << std::endl;
	std::cout << "icon: " << this->icon << std::endl;
	std::cout << "------------------" << std::endl;
}
