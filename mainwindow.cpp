#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "entry_dialog.h"
#include "menu_dialog.h"
#include "recipemodel.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadJFile();
    saveJFile();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_add_recipe_clicked()
{
    Entry_Dialog* dlg = new Entry_Dialog(this);
    //dlg -> exec();
    auto result = dlg->exec();
    if(result == QDialog::Accepted) {
        auto r = dlg->recipe;
        recipeMod->addRecipe(r);
        saveJFile();
    }
}



void MainWindow::on_edit_recipe_clicked()
{
    auto rr = ui->tableView->selectionModel()->selectedRows().at(0);
    //Entry_Dialog* dlg = new Entry_Dialog(this);
    Entry_Dialog* dlg = new Entry_Dialog(this, recipeMod->getRecipes().at(rr.row()));
    auto result = dlg->exec();
    if(result == QDialog::Accepted) {
        auto r = dlg->recipe;
        recipeMod->editRecipe(r ,rr);
        saveJFile();
    }

}

void MainWindow::on_delete_recipe_clicked()
{
   auto del = ui->tableView->selectionModel()->selectedRows();
   recipeMod->removeRows(del.at(0).row(), del.count());
   saveJFile();
}

void MainWindow::on_menu_dialog_clicked()
{
    Menu_Dialog* mdlg = new Menu_Dialog(this, recipeMod->getRecipes());
    mdlg -> exec();

}


bool MainWindow::loadJFile()
{
    QFile loadFile(QStringLiteral("/Users/nickson/Desktop/UNI/EGUI/qt_lab1/build-lab1_Shevchenko-Desktop_Qt_5_15_2_clang_64bit-Debug/recipe.json"));


    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));

    //QMessageBox msgBox;
    auto json=loadDoc.object();

    QString a;
    foreach (auto key, json.keys()) {
        a+=key;
    }
    loadDoc.object().keys();
    //msgBox.setText(a);
    //msgBox.exec();
    QVector<RecipeModel::Recipe> mainWin;
    foreach(auto key, json.keys()) {
       auto rec = json[key].toObject();
       RecipeModel::Recipe r;
       r.name=key;

       foreach(auto line, rec["recipe"].toArray()) {
           if(line == rec["recipe"].toArray().last()) {
               r.recipes+=line.toString();
           } else {
             r.recipes+=line.toString()+"\n";
           }
       }

       foreach(auto lineIn, rec.keys()) {
           if(lineIn == "recipe") {
               continue;
           }
           RecipeModel::Ingredient ing;
           ing.name=lineIn;
           ing.quantity=rec[lineIn].toString().split(" ")[0].toFloat();
           int index = rec[lineIn].toString().indexOf(" ");
           ing.unit=rec[lineIn].toString().mid(index+1);

           r.ingredients.append(ing);

       }
       mainWin.append(r);
    }
    RecipeModel* model = new RecipeModel(mainWin);
    recipeMod = model;
    ui->tableView->setModel(model);



    return true;
}

bool MainWindow::saveJFile() const
{
    QFile saveFile(QStringLiteral("/Users/nickson/Desktop/UNI/EGUI/qt_lab1/build-lab1_Shevchenko-Desktop_Qt_5_15_2_clang_64bit-Debug/recipe.json"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject jFileObject;
//    QJsonObject jValue;
//    jValue.insert("egg","1.0 pcs");
//    jFileObject.insert("pizza", jValue);
    foreach(auto key, recipeMod->getRecipes()) {
        QJsonObject jValue;
        QJsonArray recipeAr;
        jValue.insert("recipe", recipeAr.fromStringList(key.recipes.split("\n")));
        foreach(auto keyIn, key.ingredients){
            jValue.insert(keyIn.name, QString::number(keyIn.quantity) + " " + keyIn.unit);
        }
        jFileObject.insert(key.name, jValue);
    }

    saveFile.write(QJsonDocument(jFileObject).toJson());

    return true;
}

