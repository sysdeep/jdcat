#ifndef NODE_HPP
#define NODE_HPP
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QList>

class Node;

using NodesList = QList<Node>;

class Node
{
public:
	Node();

	QString name;
	NodesList childrens;


	void from_json(const QJsonObject &data, int re=false);

	void reprint(const uint level=0);
};




#endif // NODE_HPP
