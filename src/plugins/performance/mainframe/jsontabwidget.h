/*
 * Copyright (C) 2022 Uniontech Software Technology Co., Ltd.
 *
 * Author:     huangyu<huangyub@uniontech.com>
 *
 * Maintainer: huangyu<huangyub@uniontech.com>
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
#ifndef JSONTABWIDGET_H
#define JSONTABWIDGET_H

#include <jsoncpp/json/json.h>

#include <QTabWidget>

class JsonTabWidgetPrivate;
class JsonTabWidget : public QTabWidget
{
    Q_OBJECT
    JsonTabWidgetPrivate *const d;
public:
    explicit JsonTabWidget(QWidget *parent = nullptr);
    virtual ~JsonTabWidget();

public slots:
    void parseJson(const Json::Value &data);
};

#endif // JSONTABWIDGET_H