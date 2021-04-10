#include "ingredienttable.h"

IngredientTable::IngredientTable(QObject *parent)
    : QAbstractTableModel(parent)
{
}

IngredientTable::IngredientTable(const QVector<RecipeModel::Ingredient> &ingredients, QObject *parent)
    : QAbstractTableModel(parent),
      ingredients(ingredients)
{
}

QVariant IngredientTable::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Name");
            case 1:
                return tr("Quantity");
            case 2:
                return tr("Unit");
            default:
                break;
        }
    }
    return QVariant();
}

int IngredientTable::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : ingredients.size();
}

int IngredientTable::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : 3;
}

QVariant IngredientTable::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= ingredients.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &contact = ingredients.at(index.row());

        switch (index.column()) {
            case 0:
                return contact.name;
            case 1:
                return contact.quantity;
            case 2:
                return contact.unit;
            default:
                break;
        }
    }
    return QVariant();
}

bool IngredientTable::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        auto contact = ingredients.value(row);

        switch (index.column()) {
            case 0:
                contact.name = value.toString();
                break;
            case 1:
                contact.quantity = value.toFloat();
                break;
            case 2:
                contact.unit = value.toString();
                break;
            default:
                return false;
        }
        ingredients.replace(row, contact);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

        return true;
    }

    return false;
}

Qt::ItemFlags IngredientTable::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

bool IngredientTable::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)

        ingredients.insert(position, { QString(), 0, QString() });

    endInsertRows();
    return true;
}

bool IngredientTable::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        ingredients.removeAt(position);

    endRemoveRows();
    return true;
}

QVector<RecipeModel::Ingredient> IngredientTable::getIngredients()
{
    return ingredients;
}

void IngredientTable::addIngredients(RecipeModel::Ingredient input) {
    for(auto r=0; r<ingredients.count(); r++) {
        if( input.name == ingredients.at(r).name && input.unit == ingredients.at(r).unit ) {
           input.quantity += ingredients.at(r).quantity;
           ingredients.replace(r, input);
           emit dataChanged(index(r, 0), index(r, 0));
           return;
        }
    }
    beginInsertRows(QModelIndex(), ingredients.size(), ingredients.size()); //(QModelIndex(), rowCount(), rowCount())
    ingredients.append(input);
    endInsertRows();
}
