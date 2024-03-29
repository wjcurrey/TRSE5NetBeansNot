/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef ACTIVITYEVENTWINDOW_H
#define	ACTIVITYEVENTWINDOW_H

#include <QtWidgets>

class ActivityEventProperties;
class Activity;

class ActivityEventWindow : public QWidget {
    Q_OBJECT
public:
    ActivityEventWindow(QWidget* parent);
    virtual ~ActivityEventWindow();
    
    ActivityEventProperties *eventProperties = NULL;
public slots:
    void showEvents(Activity* act);
    void eventListSelected(QListWidgetItem * item);
    void eventNameChanged(int id);
    void bNewEventSelected();
    void bDeleteEventSelected();
signals:
    
        
private:
    QWidget actionWidget;
    QWidget locationWidget;
    QWidget timeWidget;
    
    QListWidget actionList;
    QListWidget locationList;
    QListWidget timeList;
    
    
    
    Activity *activity;
    
    QComboBox *cActionTypes;
    QComboBox *cOutcomeTypes;
    QComboBox *cEventNames;
};

#endif	/* ACTIVITYEVENTWINDOW_H */

