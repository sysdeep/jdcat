#include <QDebug>
#include <iostream>
#include "Node.hpp"

Node::Node()
{

}

void Node::from_json(const QJsonObject &data, int re)
{
	qDebug() << "node from_json, re: " << re;

	if(data.contains("name")){
		this->name = data.value("name").toString();
	}

	if(data.contains("childrens") && data["childrens"].isArray()){

		QJsonArray chnodes = data["childrens"].toArray();

		for(auto chnode : chnodes){
			auto chq = chnode.toObject();

			Node n = Node();
			n.from_json(chq, re);
			this->childrens.append(n);
		}
	}
}

void Node::reprint(const uint level)
{

	for(int i=0; i<level; i++){
		std::cout << "    ";
	}

	std::cout << this->name.toStdString() << std::endl;

	for(auto ch: this->childrens){
		ch.reprint(level + 1);
	}
}
