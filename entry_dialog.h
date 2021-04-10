#ifndef ENTRY_DIALOG_H
#define ENTRY_DIALOG_H

#include <QDialog>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QFile>
#include <QString>
#include <QFileDialog>
#include <QTextEdit>
#include <QIODevice>
#include "mainwindow.h"
#include "recipemodel.h"
#include "ingredienttable.h"

namespace Ui {
class Entry_Dialog;
}

class Entry_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Entry_Dialog(QWidget *parent = nullptr);
    explicit Entry_Dialog(QWidget *parent, RecipeModel::Recipe recipe);
    RecipeModel::Recipe recipe;
    ~Entry_Dialog();


private slots:

    void on_saveRecipeButton_clicked();

    void on_CancelRecipeButton_clicked();

    void on_add_ingredient_clicked();

    void on_delete_ingredient_clicked();

private:
    Ui::Entry_Dialog *ui;
    IngredientTable  *ingredientMod;

};

#endif // ENTRY_DIALOG_H
