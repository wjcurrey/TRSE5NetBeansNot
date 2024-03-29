/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef OGLOBJ_H
#define	OGLOBJ_H

#include <QString>
#include "GLUU.h"
#include "RenderItem.h"

class OglObj {
public:
    enum MaterialType {NONE, TEXTURE, COLOR};
    bool loaded;
    
    OglObj();
    OglObj(const OglObj& orig);
    virtual ~OglObj();
    void init(float* punkty, int ptr, enum RenderItem::VertexAttr v, int type);
    virtual void pushRenderItem();
    virtual void pushRenderItem(int selectionColor, float lod = 0);
    virtual void render();
    virtual void render(int selectionColor, float lod = 0);
    void deleteVBO();
    void setMaterial(float r, float g, float b);
    void setMaterial(QString* path);
    int getTexId();
    void setDistanceRange(float min, float max);
    void setLineWidth(int val);
    bool getSimpleBorder(float* border);
    void setBound(float *b);
    float* mapBuffer();
    void unmapBuffer();
private:
    QOpenGLBuffer VBO;
    QOpenGLVertexArrayObject VAO;
    int length; 
    int shapeType;
    int texId;
    int materialType;
    int lineWidth = 0;
    float bound[6];
    float minDistance = -1;
    float maxDistance = 999999;
    QString *res;
    Vector4f *color = NULL;
    RenderItem::VertexAttr vAttribures = RenderItem::NO_ATTR;
};

#endif	/* OGLOBJ_H */

