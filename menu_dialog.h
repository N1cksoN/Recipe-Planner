#ifndef MENU_DIALOG_H
#define MENU_DIALOG_H

#include <QDialog>
#include "recipemodel.h"
#include "ingredienttable.h"
#include "entry_dialog.h"

namespace Ui {
class Menu_Dialog;
}

class Menu_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Menu_Dialog(QWidget *parent = nullptr);
    explicit Menu_Dialog(QWidget *parent, QVector<RecipeModel::Recipe> recipe);
    ~Menu_Dialog();

private slots:

   // void on_recipe_input_copyAvailable(bool b);

   // void on_ingr_output_activated(const QModelIndex &index);

    void on_apply_button_clicked();

    void on_cancel_button_clicked();

private:
    Ui::Menu_Dialog *ui;
    IngredientTable  *ingr;
    QVector<RecipeModel::Recipe> recipes;
};

#endif // MENU_DIALOG_H
