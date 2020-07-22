#ifndef MODELS_HPP
#define MODELS_HPP
#include "QString"
#include <memory>

struct DBSystemModel {
	QString version;
	QString path;
};

using DBSystem = std::shared_ptr<DBSystemModel>;



#endif // MODELS_HPP
