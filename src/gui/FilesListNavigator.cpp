#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDebug>
#include "FilesListNavigator.hpp"

FilesListNavigator::FilesListNavigator(QWidget *parent) : QWidget(parent)
{
    this->setLayout(new QHBoxLayout());
    this->layout()->setContentsMargins(0, 0, 0, 0);

    __btn_back = new QPushButton("back");
	connect(__btn_back, &QPushButton::clicked, [this](){
		this->__on_back();
	});

    __edit_path = new QLineEdit();
	__edit_path->setDisabled(true);


    this->layout()->addWidget(__btn_back);
    this->layout()->addWidget(__edit_path);


	__path_items_id = new QStringList();
	__path_items_name = new QStringList();

	//--- statr
	__update();
}

void FilesListNavigator::push(QString path_item_id, QString path_item_name)
{
	__path_items_name->push_back(path_item_name);
	__path_items_id->push_back(path_item_id);
    __update();
}

void FilesListNavigator::pop()
{

}

void FilesListNavigator::clear()
{
	__path_items_id->clear();
	__path_items_name->clear();
    __update();
}

void FilesListNavigator::__update(){
	bool is_items = __path_items_name->count() > 0;
    __btn_back->setEnabled(is_items);


//    QString path("/");
	QString path = __path_items_name->join("/");
    __edit_path->setText("/" + path);

//    for(auto &item : *__path_items){
//        path.append(item )
	//    }
}

void FilesListNavigator::__on_back()
{
	if(__path_items_id->count() > 1){
		auto prev_id = __path_items_id->at(__path_items_id->count()-2);

		qDebug() << prev_id;
		emit(open_folder(prev_id));

		__path_items_name->pop_back();
		__path_items_id->pop_back();
		__update();
	}else{
		qDebug() << "go to root";
		emit(open_root());
	}

	// todo: drop from stack

}
