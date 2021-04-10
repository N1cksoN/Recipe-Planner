#include "recipemodel.h"

RecipeModel::RecipeModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

RecipeModel::RecipeModel(const QVector<Recipe> &recipes, QObject *parent)
    : QAbstractTableModel(parent),
      recipes(recipes)
{
}


QVariant RecipeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");
            //case 1:
                //return tr("Ingredients");
            default:
                break;
        }
    }
    return QVariant();
}

int RecipeModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : recipes.size();
}

int RecipeModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 1;
}

QVariant RecipeModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= recipes.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &contact = recipes.at(index.row());

        switch (index.column()) {
            case 0:
                return contact.name;
           // case 1:
             //   return contact.recipes;
            default:
                break;
        }
    }
    return QVariant();
}

bool RecipeModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        recipes.removeAt(position);

    endRemoveRows();
    return true;
}

QVector<RecipeModel::Recipe> RecipeModel::getRecipes()
{
    return recipes;
}

void RecipeModel::addRecipe(Recipe recipe) {
    beginInsertRows(QModelIndex(), recipes.size(), recipes.size()); //(QModelIndex(), rowCount(), rowCount())
    recipes.append(recipe);
    endInsertRows();
}

void RecipeModel::editRecipe(Recipe recipe, QModelIndex index) {
   recipes.replace(index.row(), recipe);
   emit dataChanged(index, index);
}

