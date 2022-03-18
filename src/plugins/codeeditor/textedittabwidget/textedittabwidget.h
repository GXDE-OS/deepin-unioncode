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
#ifndef TEXTEDITTABWIDGET_H
#define TEXTEDITTABWIDGET_H

#include "common/common.h"

#include <QWidget>

class ScintillaEditExtern;
class TextEditTabWidgetPrivate;
class TextEditTabWidget : public QWidget
{
    Q_OBJECT
    friend class TextEditTabWidgetPrivate;
    TextEditTabWidgetPrivate *const d;
public:
    explicit TextEditTabWidget(QWidget *parent = nullptr);
    virtual ~TextEditTabWidget();
    static TextEditTabWidget *instance();

public slots:
    void openFile(const QString &filePath, const QString &rootPath);
    void closeFile(const QString &filePath);
    void jumpToLine(const QString &filePath, int line);
    void jumpToRange(const QString &filePath, const lsp::Range &range);
    void runningToLine(const QString &filePath, int line);
    void runningEnd();
    void debugPointClean();
    void replaceRange(const QString &filePath, const lsp::Range &range,const QString &text);

private slots:
    void setDefaultFileEdit();
    void hideFileEdit(const QString &file);
    void showFileEdit(const QString &file);
    void hideFileStatusBar(const QString &file);
    void showFileStatusBar(const QString &file);
    void removeFileStatusBar(const QString &file);
    void removeFileEdit(const QString &file);
    void removeFileTab(const QString &file);
    void fileModifyed(const QString &file);
    void fileDeleted(const QString &file);
    void fileMoved(const QString &file);
    ScintillaEditExtern *switchFileAndToOpen(const QString &filePath);
};

#endif // TEXTEDITTABWIDGET_H