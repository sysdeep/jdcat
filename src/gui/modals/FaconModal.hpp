#ifndef FACONMODAL_HPP
#define FACONMODAL_HPP

#include <QDialog>
#include <QWidget>
#include <QListWidget>

class FaconModal : public QDialog
{
    Q_OBJECT
public:
    explicit FaconModal(QWidget *parent = nullptr);

private:
    QListWidget *__list;
	QListWidget *__ll;
signals:

};

#endif // FACONMODAL_HPP
