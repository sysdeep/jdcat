#include "EditVolumeModal.hpp"
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QDebug>
#include "lib/constants.hpp"

EditVolumeModal::EditVolumeModal(VolumeModel *model, QWidget *parent) : QDialog(parent){

    this->__edit_model = model;
    this->setWindowTitle("Изменение - " + this->__edit_model->name);


	this->__main_layout = new QVBoxLayout(this);



	//--- main
	QGridLayout * __grid = new QGridLayout();

    int row = 0;
	this->__edit_name = new QLineEdit();
    __grid->addWidget(new QLabel("Название тома:"), row, 0, Qt::AlignRight);
    __grid->addWidget(this->__edit_name, row, 1);

    row++;
	this->__edit_icon = new QComboBox();
    __grid->addWidget(new QLabel("Иконка:"), row, 0, Qt::AlignRight);
    __grid->addWidget(this->__edit_icon, row, 1);

    row++;
	this->__edit_description = new QTextEdit();
    __grid->addWidget(new QLabel("Описание:"), row, 0, Qt::AlignRight | Qt::AlignTop);
    __grid->addWidget(this->__edit_description, row, 1);

    row++;
    this->__label_created = new QLabel();
    __grid->addWidget(new QLabel("Создание"), row, 0);
    __grid->addWidget(this->__label_created, row, 1);

    row++;
    this->__label_updated = new QLabel();
    __grid->addWidget(new QLabel("Обновление"), row, 0);
    __grid->addWidget(this->__label_updated, row, 1);

	this->__main_layout->addLayout(__grid);
//	this->__main_layout->addStretch();

	//--- controls
	QHBoxLayout *controls = new QHBoxLayout();
	this->__main_layout->addLayout(controls);

	QPushButton * __close_btn = new QPushButton("Закрыть");
    __close_btn->setIcon(QIcon(":/icons/media/icons/exit_16.png"));
	connect(__close_btn, &QPushButton::clicked, this, &QDialog::close);

	QPushButton * __save_btn = new QPushButton("Сохранить");
	connect(__save_btn, &QPushButton::clicked, this, [=](){
		qDebug() << "save";
		this->__apply();
//		this->setResult(QDialog::Accepted);
//		this->close();
		this->accept();
	});

	controls->addStretch();
	controls->addWidget(__save_btn);
	controls->addWidget(__close_btn);






	//--- fill controls
	this->__edit_name->setText(this->__edit_model->name);
	this->__edit_description->setPlainText(this->__edit_model->description);

	//--- fill volume type
	int current_index = -1;
	int counter = 0;
	QMap<QString, QString>::const_iterator i = VolumeIconsMap.constBegin();
	while(i != VolumeIconsMap.constEnd()){
		this->__edit_icon->addItem(QIcon(i.value()), i.key());
//		qDebug() << i.key();
		if(__edit_model->vtype == i.key()){
			current_index = counter;
		}

		++i;
		counter++;
	}

	if(current_index > -1){
		this->__edit_icon->setCurrentIndex(current_index);
	}


    //--- fill datetime labels
    auto created_text = __edit_model->created.isValid()? __edit_model->created.toString("yyyy.MM.dd hh:mm:ss") : QString("invalid");
    auto updated_text = __edit_model->updated.isValid()? __edit_model->updated.toString("yyyy.MM.dd hh:mm:ss") : QString("invalid");

    this->__label_created->setText(created_text);
    this->__label_updated->setText(updated_text);


}



/**
 * @brief EditVolumeModal::__apply - применение изменений
 */
void EditVolumeModal::__apply(){

    // TODO: validation
	this->__edit_model->name = this->__edit_name->text();
	this->__edit_model->description = this->__edit_description->toPlainText();
	this->__edit_model->vtype = this->__edit_icon->currentText();
}

