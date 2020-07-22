#ifndef FILESLIST_HPP
#define FILESLIST_HPP

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeView>
#include <QStandardItemModel>
#include "core/models/FileModel.hpp"
#include "FilesListNavigator.hpp"

class FilesList : public QWidget
{
    Q_OBJECT
public:
    explicit FilesList(QWidget *parent = nullptr);

	void clear();
	void set_files(Files &files);
    void clear_history();



private:
    QTreeView *__tree;
    QStandardItemModel* __files_model;
    FilesListNavigator *__navigator;

	void __on_navigator_folder(QString id);
	void __on_navigator_root();

private slots:
	void __on_file_dclicked(const QModelIndex &);

signals:
	void open_folder(QString);
	void open_root();
};

#endif // FILESLIST_HPP
