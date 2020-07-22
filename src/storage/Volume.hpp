#ifndef VOLUME_HPP
#define VOLUME_HPP
/*
 * {
 *		"volume_metadata": ...,
 *		"root": Node
 * }
 */
#include <memory>
#include <QString>
#include <QJsonDocument>
#include "./Node.hpp"

class Volume
{
public:
	Volume(const QString &ipath);

	QString path;

	//--- model
	Node root;
	//--- model


	bool open();

	void __from_json(const QJsonDocument &doc);
};

using VolumePtr = std::shared_ptr<Volume>;


#endif // VOLUME_HPP
