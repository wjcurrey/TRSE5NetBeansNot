/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef RULEROBJ_H
#define	RULEROBJ_H

#include "WorldObj.h"
#include <QString>
#include "FileBuffer.h"
#include "ComplexLine.h"

class OglObj;

class RulerObj : public WorldObj {
public:
    static bool TwoPointRuler;
    static bool DrawPoints;
    
    RulerObj();
    RulerObj(const RulerObj& o);
    WorldObj* clone();
    virtual ~RulerObj();
    bool allowNew();
    void reload();
    void setTemplate(QString name);
    void load(int x, int y);
    void set(QString sh, QString val);
    void set(QString sh, FileBuffer* data);
    void setPosition(int x, int z, float* p);
    bool select(int value);
    void save(QTextStream* out);
    bool hasLinePoints();
    void getLinePoints(float *&punkty);
    void getPosition(float len, float* pos);
    float getLength();
    float getGeoLength();
    float getElevation();
    void createRoadPaths();
    void removeRoadPaths();
    void enableShape();
    void render(GLUU* gluu, float lod, float posx, float posz, float* playerW, float* target, float fov, int selectionColor, int renderMode);

private:
    struct Point {
        bool selected = false;
        int shapeType = 0;
        float position[3];
        QVector<OglObj*> procShape;
        float quat[4];
        float matrix[16];
    };
    
    QVector<Point> points;
    OglObj* point3d = NULL;
    OglObj* line3d = NULL;
    OglObj* point3dSelected = NULL;
    int selectionValue = 0;
    float length = 0;
    float geoLength = 0;
    
    void refreshLength();
    bool shapeEnabled = false;
    bool proceduralShapeInit = false;

};

#endif	/* RULEROBJ_H */

