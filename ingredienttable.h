#ifndef INGREDIENTTABLE_H
#define INGREDIENTTABLE_H

#include <QAbstractTableModel>
#include <QString>
#include "recipemodel.h"

class IngredientTable : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit IngredientTable(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;


    IngredientTable(const QVector<RecipeModel::Ingredient> &ingredients, QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    void addIngredients(RecipeModel::Ingredient input);

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;


    QVector<RecipeModel::Ingredient> getIngredients();

private:
    QVector<RecipeModel::Ingredient> ingredients;
};

#endif // INGREDIENTTABLE_H
