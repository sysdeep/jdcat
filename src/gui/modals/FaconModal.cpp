#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include "FaconModal.hpp"

#include "../facon/Facon.hpp"


FaconModal::FaconModal(QWidget *parent) : QDialog(parent)
{
    auto *main_layout = new QVBoxLayout(this);
    this->setLayout(main_layout);



    __list = new QListWidget(this);
	__list->setViewMode(QListWidget::IconMode);
//	__list->setIconSize(QSize(128, 128));
	__list->setIconSize(QSize(16, 16));




	__ll = new QListWidget(this);
	__ll->setIconSize(QSize(16, 16));


	auto icon = QFontIcon::icon(0xf030);
	qDebug() << icon.availableSizes();


    //--- model controls

	auto *btn_close = new QPushButton(icon, "Close", this);
	connect(btn_close, &QPushButton::clicked, [this](){
		close();
	});

	auto *btn_plus = new QPushButton(QFontIcon::icon(0xf067), "plus", this);
	connect(btn_plus, &QPushButton::clicked, [this](){
		auto size = this->__list->iconSize();
		this->__list->setIconSize(size + QSize(16,16));
		this->__ll->setIconSize(size + QSize(16,16));
	});

	auto *btn_minus = new QPushButton(QFontIcon::icon(0xf068), "minus", this);
	connect(btn_minus, &QPushButton::clicked, [this](){
		auto size = this->__list->iconSize();
		this->__list->setIconSize(size - QSize(16,16));
		this->__ll->setIconSize(size - QSize(16,16));
	});

	auto *modal_controls = new QHBoxLayout();
	modal_controls->addWidget(btn_plus);
	modal_controls->addWidget(btn_minus);
	modal_controls->addStretch();
    modal_controls->addWidget(btn_close);




    main_layout->addWidget(__list);
	main_layout->addWidget(__ll);
    main_layout->addLayout(modal_controls);



    int code = 0xf030;

    for (int x=0; x<20; x++){
        for (int y=0;y<20; y++){
            auto *item = new QListWidgetItem(QFontIcon::icon(code, QColor(Qt::red)), QString::number(code));
            __list->addItem(item);

			auto *item2 = new QListWidgetItem(QFontIcon::icon(code, QColor(Qt::red)), QString::number(code));
			__ll->addItem(item2);

//            if (y == 5)
//                item->setDisabled(true);

            code++;
        }
    }

}
