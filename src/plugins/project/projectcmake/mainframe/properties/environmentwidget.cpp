/*
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     huangyu<huangyub@uniontech.com>
 *
 * Maintainer: huangyu<huangyub@uniontech.com>
 *             zhouyi<zhouyi1@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "environmentwidget.h"

#include <QVBoxLayout>
#include <QCheckBox>
#include <QHeaderView>
#include <QTableView>

class EnvironmentModelPrivate
{
    friend class EnvironmentModel;
    QMap<QString, QString> envs;
};

EnvironmentModel::EnvironmentModel(QObject *parent)
    : QAbstractTableModel(parent)
    , d (new EnvironmentModelPrivate())
{

}

EnvironmentModel::~EnvironmentModel()
{
    if (d)
        delete d;
}

int EnvironmentModel::rowCount(const QModelIndex &) const
{
    return d->envs.keys().size();
}

int EnvironmentModel::columnCount(const QModelIndex &) const
{
    return kColumnCount;
}

QVariant EnvironmentModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        auto var = d->envs.keys()[index.row()];
        switch (index.column()) {
        case kVaribale:
            return var;
        case kValue:
            return d->envs.value(var);
        default:
            break;
        }
    }
    return {};
}

QVariant EnvironmentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {
        case kVaribale:
            return "Variable";
        case kValue:
            return "Value";
        default:
            break;
        }
    }
    return {};
}

void EnvironmentModel::append(const QString &key, const QString &value)
{
    beginInsertRows({}, d->envs.keys().count(), d->envs.keys().count());
    d->envs.insert(key, value);
    endInsertRows();
}

void EnvironmentModel::update(const QMap<QString, QString> &data)
{
    beginResetModel();
    d->envs.clear();
    d->envs = data;
    endResetModel();
}

const QMap<QString, QString> EnvironmentModel::getEnvironment() const
{
    return d->envs;
}

class EnvironmentWidgetPrivate
{
    friend class EnvironmentWidget;

    QVBoxLayout *vLayout{nullptr};
    QTableView *tableView{nullptr};
    QCheckBox *checkBox{nullptr};
    EnvironmentModel *model{nullptr};

    config::EnvironmentItem *envShadow{nullptr};
};


EnvironmentWidget::EnvironmentWidget(QWidget *parent)
    : QWidget(parent)
    , d(new EnvironmentWidgetPrivate)
{
    setAutoFillBackground(true);

    if (!d->vLayout)
        d->vLayout = new QVBoxLayout();
    this->setLayout(d->vLayout);

    if (!d->tableView) {
        d->tableView = new QTableView();

        // Initialize view
        d->tableView->setShowGrid(false);
        QHeaderView* headerView = d->tableView->horizontalHeader();
        headerView->setSectionResizeMode(QHeaderView::ResizeToContents);
    }

    if (!d->model)
        d->model = new EnvironmentModel();

    d->tableView->setModel(d->model);

    if (!d->checkBox)
        d->checkBox = new QCheckBox();

    connect(d->checkBox, &QCheckBox::clicked, [this](){
        d->envShadow->enable = d->checkBox->isChecked();
    });

    d->checkBox->setText(tr("Enable All Environment"));
    d->checkBox->setChecked(true);
    d->vLayout->setSpacing(0);
    d->vLayout->setMargin(0);
    d->vLayout->addWidget(d->checkBox);
    d->vLayout->addWidget(d->tableView);
}

EnvironmentWidget::~EnvironmentWidget()
{
    if(d)
        delete d;
}

void EnvironmentWidget::getValues(config::EnvironmentItem &env)
{
    env.enable = d->checkBox->isChecked();
    env.environments = d->model->getEnvironment();
}

void EnvironmentWidget::setValues(const config::EnvironmentItem &env)
{
    d->checkBox->setChecked(env.enable);
    d->model->update(env.environments);
}

void EnvironmentWidget::bindValues(config::EnvironmentItem *env)
{
    d->envShadow = env;
    d->checkBox->setChecked(env->enable);
    d->model->update(env->environments);
}


