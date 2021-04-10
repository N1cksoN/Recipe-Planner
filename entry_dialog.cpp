#include "entry_dialog.h"
#include "ui_entry_dialog.h"


Entry_Dialog::Entry_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Entry_Dialog)
{
    ui->setupUi(this);
    IngredientTable* model = new IngredientTable();
    ingredientMod = model;
    ui->tableEdit->setModel(model);
}

Entry_Dialog::Entry_Dialog(QWidget *parent, RecipeModel::Recipe recipe) :
    QDialog(parent),
    ui(new Ui::Entry_Dialog)
{
    ui->setupUi(this);
    IngredientTable* model = new IngredientTable(recipe.ingredients);
    ingredientMod = model;
    ui->tableEdit->setModel(model);
    ui->textEditName->setText(recipe.name);
    ui->textEditRecipe->setText(recipe.recipes);
}

Entry_Dialog::~Entry_Dialog()
{
    delete ui;
}

void Entry_Dialog::on_saveRecipeButton_clicked()
{
   recipe.name=ui->textEditName->toPlainText();
   recipe.recipes=ui->textEditRecipe->toPlainText();
   recipe.ingredients=ingredientMod->getIngredients();
   accept();
}


void Entry_Dialog::on_CancelRecipeButton_clicked()
{
    close();
}

void Entry_Dialog::on_add_ingredient_clicked()
{
    ui->tableEdit->model()->insertRows(0, 1);
}

void Entry_Dialog::on_delete_ingredient_clicked()
{
    auto del = ui->tableEdit->selectionModel()->selectedRows();
    ingredientMod->removeRows(del.at(0).row(), del.count());
}
