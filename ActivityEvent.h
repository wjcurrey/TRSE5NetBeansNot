/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include <QString>
#include <QVector>
#include <QVariant>

#ifndef ACTIVITYEVENT_H
#define	ACTIVITYEVENT_H

class FileBuffer;
class QTextStream;
class GLUU;
class OglObj;
class TextObj;
class OrtsWeatherChange;
class Activity;

class ActivityEvent {

public:
    class Outcome {
    public:
        enum OutcomeCategory {
            CategoryNone = 0,
            CategoryEvent = 1,
            CategoryInfo = 2,
            CategorySoundFile = 3,
            CategoryWeatherChange = 4
        };
        
        enum OutcomeType {
            TypeNone = 0,
            TypeDisplayMessage = 1,
            TypeActivitySuccess = 2,
            TypeActivityFail = 3,
            TypeIncActLevel = 4,
            TypeDecActLevel = 5,
            TypeRestorAactLevel = 6,
            TypeActivateEvent = 7,
            TypeStartIgnoringSpeedLimits = 8,
            TypeStopIgnoringSpeedLimits = 9,
            TypeORTSActSoundFile = 10,
            TypeORTSWeatherChange = 11
        };
        
        static QMap<OutcomeType, QString> OutcomeTypeDescription;
        static QMap<QString, OutcomeType> OutcomeNameType;
        static QMap<OutcomeType, QString> OutcomeTypeName;
        static QMap<OutcomeType, OutcomeCategory> OutcomeTypeCategory;
        
        OutcomeType type;
        OutcomeCategory category;
        QVariant value;
        
        Outcome(OutcomeType t){
            type = t;
            category = OutcomeTypeCategory[type];
        }
        
        void load(FileBuffer* data);
        void save(QTextStream* out);
        void setToNewType(OutcomeType newType);
        void setMessage(QString val);
        void setEventLinkId(int id);
        void setSoundFileName(QString val);
        void setSoundType(QString val);
        void setWeatherName(QString val);
        void setModified(bool val);
        bool isModified();
    protected:
        bool modified = false;
    };

    enum EventType {
        EventTypeNone = 0,
        EventTypeTime = 1,
        EventTypeLocation = 2,
        EventTypeAllstops = 3,
        EventTypePickupWagons = 4,
        EventTypeAssembleTrain = 5,
        EventTypeAssembleTrainAtLocation = 6,
        EventTypeDropoffWagonsAtLocation = 7,
        EventTypePickupPassengers = 8,
        EventTypeReachSpeed = 9,
        EventTypePickUp = 10
    };
    
    static QMap<EventType, QString> EventTypeDescription;
    static QMap<QString, EventType> EventNameType;
    static QMap<EventType, QString> EventTypeName;
    
    enum EventCategory {
        CategoryUndefined = 0,
        CategoryAction = 1,
        CategoryLocation = 2,
        CategoryTime = 3
    };
    
    struct WagonList {
        unsigned int uid;
        unsigned int sidingItem = -1;
        QString description;
        
        WagonList(){
        }
        WagonList(WagonList *o){
            uid = o->uid;
            sidingItem = o->sidingItem;
            description = o->description;
        }
    };
    
    EventCategory category = CategoryUndefined;
    EventType eventType = EventTypeNone;
    QVector<WagonList> wagonList;

    int id = -99999;
    bool reversableEvent = false;
    int activationLevel = -99999;
    QString name;
    int time = -99999;
    int stationStop = -99999;
    float* location = NULL;
    int sidingItem = -99999;
    float speed = -99999;
    int triggerOnStop = -99999;
    int ortsContinue = -99999;
    QVector<int> pickupIdAndAmount;
    QString textToDisplayOnCompletionIfTriggered;
    QString textToDisplayOnCompletionIfNotTriggered;
    QString textToDisplayDescriptionOfTask;
    QVector<Outcome*> outcomes;
    // deprecated - use only for OpenRails 1.2;
    OrtsWeatherChange* ortsWeatherChangeDeprecated = NULL;
    QVector<QString> ortsActSoundFileDeprecated;
    //Outcome* outcome = NULL;
    
    ActivityEvent();
    ActivityEvent(int uid, EventCategory c);
    
    ~ActivityEvent();
    
    int newOutcome();
    void removeOutcome(int id);
    void setModified(bool val);
    void setActivationLevel(int val);
    void setName(QString val);
    void setTriggeredText(QString val);
    void setUntriggeredText(QString val);
    void setLocation(int X, int Z, float x, float z);
    void setNotes(QString val);
    void setSpeed(int val);
    void setLocationRadius(int val);
    void setLocationStop(bool val);
    void setReversable(bool val);
    void setAutoContinue(int val);
    void setActionToNewType(EventType newType);
    void setStationStop(int tid);
    void setTime(int val);
    int getWagonListSize();
    QString getWagonListDescription(int i);
    QString getWagonListIdDescription(int i);
    bool isModified();
    bool isSelected();
    bool setSelected(bool val);
    bool unselect();
    bool select();
    void load(FileBuffer* data);
    void save(QTextStream* out);
    void addSelectedWagonToList();
    void removeWagonListItem(int id);
    QString getWagonListItemDescription(int id);
    void setWagonListItemDescription(int id, QString val);
    bool getWagonListItemPosition(int id, float *posTW);
    QString getSidingDescription();
    bool setSidingFromSelected();
    void setParentActivity(Activity* a);
    void render(GLUU* gluu, float * playerT, float playerRot, int renderMode);
    
protected:
    Activity *parentActivity = NULL;
    static OglObj *simpleMarkerObj;
    TextObj* txtMarkerObj = NULL;
    bool modified = false;
    bool isWagonList = false;
    bool selected = false;
};

#endif	/* ACTIVITYEVENT_H */

