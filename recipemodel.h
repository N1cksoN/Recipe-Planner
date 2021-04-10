#ifndef RECIPEMODEL_H
#define RECIPEMODEL_H

#include <QAbstractTableModel>
//#include <mainwindow.h>
#include <QVector>



class RecipeModel : public QAbstractTableModel
{
    Q_OBJECT

public:

    struct Ingredient
    {
        QString name;
        float quantity;
        QString unit;

        bool operator==(const Ingredient &other) const
        {
            return name == other.name && quantity == other.quantity && unit == other.unit;
        }
    };

    struct Recipe
    {
        QString name;
        QString recipes;
        QVector<Ingredient> ingredients;

        bool operator==(const Recipe &other) const
        {
            return name == other.name && recipes == other.recipes && ingredients == other.ingredients;
        }
    };


    explicit RecipeModel(QObject *parent = nullptr);

    RecipeModel(const QVector<Recipe> &recipes, QObject *parent = nullptr);
    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    void addRecipe(Recipe recipe);
    void editRecipe(Recipe recipe, QModelIndex index);

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVector<Recipe> getRecipes();


private:
    QVector<Recipe> recipes;
};

#endif // RECIPEMODEL_H
