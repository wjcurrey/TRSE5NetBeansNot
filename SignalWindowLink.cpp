/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "SignalWindowLink.h"

SignalWindowLink::SignalWindowLink() : QDialog(){
    this->setFixedSize(200, 60);

    QPushButton* ok = new QPushButton("OK");
    QPushButton* cancel = new QPushButton("Cancel");
    connect(ok, SIGNAL (released()), this, SLOT (ok()));
    connect(cancel, SIGNAL (released()), this, SLOT (cancel()));

    QFormLayout *vlist = new QFormLayout;
    vlist->setSpacing(2);
    vlist->setContentsMargins(3,0,3,0);
    vlist->addRow("from:",&this->from);
    vlist->addRow("to:",&this->to);
    vlist->addRow(ok,cancel);
    vlist->setContentsMargins(1,1,1,1);
    this->setLayout(vlist);
}

SignalWindowLink::~SignalWindowLink() {
}

void SignalWindowLink::cancel(){
    this->changed = false;
    this->close();
}
void SignalWindowLink::ok(){
    this->changed = true;
    this->close();
}