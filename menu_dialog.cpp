#include "menu_dialog.h"
#include "ui_menu_dialog.h"

Menu_Dialog::Menu_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu_Dialog)
{
    ui->setupUi(this);

}


Menu_Dialog::Menu_Dialog(QWidget *parent, QVector<RecipeModel::Recipe> recipe) :
    QDialog(parent),
    ui(new Ui::Menu_Dialog)
{
    ui->setupUi(this);
    recipes = recipe;

    //ui->recipeInput->setText(recipe.name);
    IngredientTable* model = new IngredientTable();
    ingr = model;
    ui->ingrOutput->setModel(model);
}


Menu_Dialog::~Menu_Dialog()
{
    delete ui;
}


//void Menu_Dialog::on_recipe_input_copyAvailable(bool b)
//{

//}

//void Menu_Dialog::on_ingr_output_activated(const QModelIndex &index)
//{

//}

void Menu_Dialog::on_apply_button_clicked()
{
    if(ingr->getIngredients().count()>0)
        ingr->removeRows(0, ingr->getIngredients().count());
    auto names = ui->recipeInput->toPlainText().split("\n");

    foreach(auto k, names) {
        foreach(auto r, recipes) {
          if(k == r.name) {
              foreach(auto ing, r.ingredients) {
                ingr->addIngredients(ing);
              }
              break;
          }
        }
    }

}

void Menu_Dialog::on_cancel_button_clicked()
{
    close();
}
