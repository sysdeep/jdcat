#ifndef EDITVOLUMEMODAL_HPP
#define EDITVOLUMEMODAL_HPP

#include <QObject>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include "core/models/VolumeModel.hpp"






class EditVolumeModal : public QDialog
{
	Q_OBJECT
public:
	explicit EditVolumeModal(VolumeModel *model, QWidget *parent = nullptr);

private:
	QVBoxLayout *__main_layout;

	QLineEdit * __edit_name;
	QComboBox * __edit_icon;
	QTextEdit * __edit_description;
    QLabel * __label_created;
    QLabel * __label_updated;

	VolumeModel * __edit_model;

	void __apply();

signals:

public slots:
};

#endif // EDITVOLUMEMODAL_HPP
