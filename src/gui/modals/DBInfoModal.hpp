#ifndef DBINFOMODAL_HPP
#define DBINFOMODAL_HPP

#include <QDialog>
#include "storage/dbsqlite/models.hpp"


class DBInfoModal : public QDialog
{
	Q_OBJECT

public:
    explicit DBInfoModal(const DBSystem &db_info, QWidget *parent = 0);
	~DBInfoModal();


};

#endif // DBINFOMODAL_HPP
