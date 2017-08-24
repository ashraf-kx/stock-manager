/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mdlineedit.h"
#include "mdlineeditplugin.h"

#include <QtPlugin>

//! [0]
MDLineEditPlugin::MDLineEditPlugin(QObject *parent)
    : QObject(parent)
    , initialized(false)
{
}
//! [0]

//! [1]
void MDLineEditPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}
//! [1]

//! [2]
bool MDLineEditPlugin::isInitialized() const
{
    return initialized;
}
//! [2]

//! [3]
QWidget *MDLineEditPlugin::createWidget(QWidget *parent)
{
    return new MDLineEdit(parent);
}
//! [3]

//! [4]
QString MDLineEditPlugin::name() const
{
    return "MDLineEdit";
}
//! [4]

//! [5]
QString MDLineEditPlugin::group() const
{
    return "Material Design Widgets";
}
//! [5]

//! [6]
QIcon MDLineEditPlugin::icon() const
{
    return QIcon("://MDLineEditIcon.png");
}
//! [6]

//! [7]
QString MDLineEditPlugin::toolTip() const
{
    return "";
}
//! [7]

//! [8]
QString MDLineEditPlugin::whatsThis() const
{
    return "";
}
//! [8]

//! [9]
bool MDLineEditPlugin::isContainer() const
{
    return false;
}
//! [9]

//! [10]
QString MDLineEditPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
               " <widget class=\"MDLineEdit\" name=\"MDLineEdit\">\n"
    ////! [11]
    //           "  <property name=\"geometry\">\n"
    //           "   <rect>\n"
    //           "    <x>0</x>\n"
    //           "    <y>0</y>\n"
    //           "    <width>200</width>\n"
    //           "    <height>90</height>\n"
    //           "   </rect>\n"
    //           "  </property>\n"
    ////! [11]
    //           "  <property name=\"toolTip\" >\n"
    //           "   <string>My custom Line Edit Support MD </string>\n"
    //           "  </property>\n"

    //           "  <property name=\"whatsThis\" >\n"
    //           "   <string>Styled Input Text.</string>\n"
    //           "  </property>\n"

    //           "  <property name=\"xxxxxx\" >\n"
    //           "   <string>xxxxxx</string>\n"
    //           "  </property>\n"

    //           "<property name=\"labelText\" >\n"
    //            "<string> Label Text ..</string>\n"
    //           "</property>\n"

              " </widget>\n"
               "</ui>\n";
}
//! [10]

//! [12]
QString MDLineEditPlugin::includeFile() const
{
    return "mdlineedit.h";
}
//! [12]
