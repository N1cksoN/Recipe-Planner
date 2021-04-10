#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QFile>
#include <QString>
#include <QFileDialog>
#include <QIODevice>
#include <QStringList>
#include <QDebug>
#include <QList>
#include <QStandardItem>
#include <QMessageBox>
#include <QVector>
#include "recipemodel.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//struct MainWin
//{
//    QString name;
//    QString description;
//};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool loadJFile();
    bool saveJFile() const;

private slots:
    void on_add_recipe_clicked();

    void on_menu_dialog_clicked();

    void on_edit_recipe_clicked();

    void on_delete_recipe_clicked();

private:
    Ui::MainWindow *ui;
    RecipeModel  *recipeMod;

};
#endif // MAINWINDOW_H
