// SPDX-FileCopyrightText: 2024 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: GPL-3.0-or-later
#ifndef PLUGINDETAILSVIEW_H
#define PLUGINDETAILSVIEW_H

#include "framework/lifecycle/pluginmetaobject.h"
#include <dtkwidget_global.h>

#include <DWidget>
#include <DListWidget>

QT_BEGIN_NAMESPACE
class QGridLayout;
class QVBoxLayout;
class QSpacerItem;
class QLabel;
QT_END_NAMESPACE

DWIDGET_BEGIN_NAMESPACE
class DTextEdit;
class DLabel;
DWIDGET_END_NAMESPACE

class AutoZoomWebEngineView;
class DetailsView : public DTK_WIDGET_NAMESPACE::DWidget
{
    Q_OBJECT
public:
    explicit DetailsView(QWidget *parent = nullptr);
    ~DetailsView();

    void update(const dpf::PluginMetaObjectPointer &metaInfo);

private slots:
    void changeLoadBtnState();
    void showCfgWidget();

private:
    void setupUi();
    void initMetaInfoLayout();
    void updateLoadBtnDisplay(bool isEnabled);

    QVBoxLayout *metaInfoLayout {nullptr};
    DTK_WIDGET_NAMESPACE::DLabel *name {nullptr};
    DTK_WIDGET_NAMESPACE::DLabel *version {nullptr};
    DTK_WIDGET_NAMESPACE::DLabel *category {nullptr};
    DTK_WIDGET_NAMESPACE::DLabel *description {nullptr};
    DTK_WIDGET_NAMESPACE::DLabel *vendor {nullptr};
    DTK_WIDGET_NAMESPACE::DLabel *dependency {nullptr};

    DTK_WIDGET_NAMESPACE::DPushButton *loadBtn {nullptr};
    dpf::PluginMetaObjectPointer pluginMetaInfo;
    AutoZoomWebEngineView *webView {nullptr};
    QLabel *logoLabel {nullptr};
};

#endif // PLUGINDETAILSVIEW_H
