#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>

#include "DBInfoModal.hpp"
#include "gui/facon/Facon.hpp"


DBInfoModal::DBInfoModal(const DBSystem &db_info, QWidget *parent) : QDialog(parent)
{

    //--- main layout
    QVBoxLayout *main_layout = new QVBoxLayout(this);
    this->setLayout(main_layout);


    //--- main grid
    QGridLayout *info_grid = new QGridLayout();

    int row = 0;

    info_grid->addWidget(new QLabel("DB path"), row, 0);
    info_grid->addWidget(new QLabel(db_info->path), row, 1);

    row++;
    info_grid->addWidget(new QLabel("DB version"), row, 0);
    info_grid->addWidget(new QLabel(db_info->version), row, 1);


    //--- modal controls
    QHBoxLayout *modal_controls = new QHBoxLayout();
    QPushButton *btn_quit = new QPushButton(QIcon(":/icons/media/icons/exit.png"), "Закрыть");
    connect(btn_quit, &QPushButton::clicked, [this](){
       this->close();
    });

    modal_controls->addStretch();
    modal_controls->addWidget(btn_quit);


    //--- pack elements
    main_layout->addLayout(info_grid);
    main_layout->addStretch();
    main_layout->addLayout(modal_controls);



    QElapsedTimer timer;
    timer.start();


    qDebug() << "load fonts: " << timer.elapsed() << "ms";

    //    auto files = this->storage->get_child_files(selected_file_uuid);

    //    qDebug() << "get_child_files took " << timer.elapsed() << "ms";

    //    timer.restart();








}

DBInfoModal::~DBInfoModal(){

}


