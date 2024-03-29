/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "TSection.h"
#include <math.h>
#include "GLMatrix.h"
#include <QDebug>
#include "Vector2f.h"
#include "Vector3f.h"
#include "ParserX.h"
#include <QTextStream>
#include "FileBuffer.h"

TSection::TSection() {
    id = 0;
    type = 0;
}

TSection::TSection(int index) {
    id = index;
    type = 0;
}

TSection::TSection(int index, int t, float a, float r) {
    id = index;
    type = t;
    angle = a;
    radius = r;
    val1 = 0;
    size = angle;
}

TSection::TSection(const TSection& orig) {
    id = orig.id;
    type = orig.type;
    angle = orig.angle;
    radius = orig.radius;
    val1 = orig.val1;
    size = orig.size;
}

TSection::~TSection() {
}

float TSection::getDlugosc() {
    if (type == 0) {
        return size;
    } else if (type == 1) {
        return fabs(radius * angle);
    }
    return 0;
}

int TSection::getHash(){
    if (type == 0) {
        return size*200;
    } else if (type == 1) {
        return radius * 100000 + angle*100;
    }
    return 0;
}

float TSection::getAngle() {
    if (type == 0) {
        return 0;
    } else if (type == 1) {
        return angle;
    }
    return 0;
}

int TSection::getLineBufferSize(int pointSize, int step) {
    float kierunek;
    if (type == 0) {
        if (step == 0) {
            return pointSize * 2;
        } else {
            int len = 0;
            for (int i = 0; i < size; i += step) {
                len += pointSize * 2;
            }
            return len;
        }
    } else if (type == 1) {
        kierunek = 1;
        if (angle > 0) kierunek = -1;
        float astep = -0.05;
        if (step != 0)
            astep = -step / radius;
        float aa = astep*kierunek;
        int bufSize = 0;
        for (float angle2 = angle * kierunek; angle2 < 0; angle2 -= astep) {
            if (angle2 > astep) aa = angle2 * kierunek;
            bufSize += pointSize * 2;
        }
        return bufSize;
    }
    return 0;
}

void TSection::drawSection(float* &ptr, float* matrix, float height) {
    drawSection(ptr, matrix, height, -1, 0, 0, 0);
}

void TSection::drawSection(float* &ptr, float* matrix, float height, int idx, int vidx) {
    drawSection(ptr, matrix, height, idx, vidx, 0, 0);
}

void TSection::drawSection(float* &ptr, float* matrix, float height, int idx, int vidx, float offset, int step) {

    float kierunek;
    if (type == 0) {

        float point1[3];
        point1[0] = 0;
        point1[1] = height;
        point1[2] = 0;
        float point2[3];
        point2[0] = 0;
        point2[1] = height;
        point2[2] = size;

        Vec3::transformMat4(point1, point1, matrix);
        Vec3::transformMat4(point2, point2, matrix);
        if (step == 0) {
            *ptr++ = point1[0];
            *ptr++ = point1[1];
            *ptr++ = point1[2];
            if (idx >= 0) {
                *ptr++ = idx;
                *ptr++ = vidx;
                *ptr++ = 0 + offset;
            }
            *ptr++ = point2[0];
            *ptr++ = point2[1];
            *ptr++ = point2[2];
            if (idx >= 0) {
                *ptr++ = idx;
                *ptr++ = vidx;
                *ptr++ = size + offset;
            }
        } else {
            float step2 = 0;
            float point[3];
            for (int i = 0; i < size; i += step) {
                step2 = i + step;
                if (step2 > size) step2 = size;
                point[0] = 0;
                point[1] = height;
                point[2] = i;
                Vec3::transformMat4(point, point, matrix);
                *ptr++ = point[0];
                *ptr++ = point[1];
                *ptr++ = point[2];
                if (idx >= 0) {
                    *ptr++ = idx;
                    *ptr++ = vidx;
                    *ptr++ = i + offset;
                }
                point[0] = 0;
                point[1] = height;
                point[2] = step2;
                Vec3::transformMat4(point, point, matrix);
                *ptr++ = point[0];
                *ptr++ = point[1];
                *ptr++ = point[2];
                if (idx >= 0) {
                    *ptr++ = idx;
                    *ptr++ = vidx;
                    *ptr++ = step2 + offset;
                }
            }
        }
    }        //krzywa
    else if (type == 1) {
        kierunek = 1;
        if (angle > 0) kierunek = -1;
        float astep = -0.05;
        if (step != 0)
            astep = -step / radius;
        float aa = astep*kierunek;
        float point1[3];
        float point2[3];
        for (float angle2 = angle * kierunek; angle2 < 0; angle2 -= astep) {
            if (angle2 > astep) aa = angle2 * kierunek;

            Vector2f a(0, 0);
            a.rotate(aa, radius);

            point1[0] = 0;
            point1[1] = height;
            point1[2] = 0;
            point2[0] = kierunek * a.x;
            point2[1] = height;
            point2[2] = kierunek * a.y;

            Vec3::transformMat4(point1, point1, matrix);
            Vec3::transformMat4(point2, point2, matrix);
            *ptr++ = point1[0];
            *ptr++ = point1[1];
            *ptr++ = point1[2];
            if (idx >= 0) {
                *ptr++ = idx;
                *ptr++ = vidx;
                *ptr++ = fabs(radius * (angle2 - angle * kierunek)) + offset;
            }
            *ptr++ = point2[0];
            *ptr++ = point2[1];
            *ptr++ = point2[2];
            if (idx >= 0) {
                float d = ((angle2 - astep) - angle * kierunek);
                if (d > -angle * kierunek) d = -angle * kierunek;
                *ptr++ = idx;
                *ptr++ = vidx;
                *ptr++ = fabs(radius * d) + offset;
            }
            Mat4::translate(matrix, matrix, kierunek * a.x, 0, kierunek * a.y);
            Mat4::rotateY(matrix, matrix, -aa);
        }
    }
}

void TSection::getPoints(QVector<float> &ptr, float* matrix) {
    float kierunek;
    float step;
    float point1[3];
    if (type == 0) {
        step = 4;
        if(size == 0)
            return;
        if(step > size)
            step = size;
        for (float i = 0; i <= size; i += step) {
            point1[0] = 0;
            point1[1] = 0;
            point1[2] = i;
            Vec3::transformMat4(point1, point1, matrix);
            ptr.push_back(point1[0]);
            ptr.push_back(point1[1]);
            ptr.push_back(point1[2]);
        } 
    }
    else if (type == 1) {
        kierunek = 1;
        if (angle > 0) kierunek = -1;
        float point1[3];
        float dlugosc = getDlugosc() / 4;
        if(dlugosc < 1.0)
            dlugosc = 1.0;
        step = fabs(angle) / dlugosc;

        float aa = -step*kierunek;
        for (float angle2 = angle * kierunek; angle2 <= 0; angle2 += step) {
            Vector2f a(0, 0);
            a.rotate(aa, radius);

            point1[0] = 0;
            point1[1] = 0;
            point1[2] = 0;

            Vec3::transformMat4(point1, point1, matrix);
            ptr.push_back(point1[0]);
            ptr.push_back(point1[1]);
            ptr.push_back(point1[2]);
            Mat4::translate(matrix, matrix, kierunek * a.x, 0, kierunek * a.y);
            Mat4::rotateY(matrix, matrix, -aa);
        }
    }
}

void TSection::setDrawPosition(float metry) {
    //prosta
    /*     if(type==0){
             gl.glTranslatef(0, 0, metry);
         }
         //krzywa
         else if(type==1){
             float kierunek = 1;
             if(angle > 0) kierunek = -1;

             float aa = -metry/radius*kierunek;
                
             Vector2f a = new Vector2f(0.0f, 0.0f);
             a.rotate(aa, radius);

             float dlugosc = a.getDlugosc();

             gl.glTranslatef(kierunek*a.x,0,kierunek*a.y);
             //gl.glRotatef((float)(-aa*180f/Math.PI),0,1,0);
         }*/
}

void TSection::getDrawPosition(Vector3f *out, float metry) {

    if (metry > this->getDlugosc())
        metry = this->getDlugosc();
    //prosta
    if (type == 0) {
        out->x = 0;
        out->y = 0;
        out->z = metry;
        return;// (new Vector3f(0, 0, metry));
    }        //krzywa
    else if (type == 1) {
        float kierunek = 1;
        if (angle > 0) kierunek = -1;

        float aa = -metry / radius*kierunek;

        Vector2f a;
        a.rotate(aa, radius);

        out->x = kierunek * a.x;
        out->y = 0;
        out->z = kierunek * a.y;
        return;// (new Vector3f(kierunek * a.x, 0, kierunek * a.y));
    }
    return;
}

float TSection::getDrawAngle(float metry) {

    if (metry > this->getDlugosc())
        metry = this->getDlugosc();
    //prosta
    if (type == 0) {
        return 0;
    }        //krzywa
    else if (type == 1) {
        float kierunek = 1;
        if (angle > 0) kierunek = -1;
        return -metry / radius*kierunek;
    }
    return 0;
}

void TSection::setCamPosition(float metry, float ob) {
    /*   if(type==0){
           gl.glTranslatef(0, 0, metry*ob);
       }
       //krzywa
       else if(type==1){
           float kierunek = 1;
           if(angle > 0) 
               kierunek = -1;

           float aa = -metry*ob/radius*kierunek;
                
           Vector2f a = new Vector2f(0.0f, 0.0f);
           a.rotate(aa, radius);

           float dlugosc = a.getDlugosc();

           if(ob==-1){
               gl.glTranslatef(kierunek*a.x,0,kierunek*a.y);
               gl.glRotatef((float)(-aa*180f/Math.PI),0,1,0);
           } else {
               aa = -aa;
               gl.glRotatef((float)(-aa*180f/Math.PI),0,1,0);       
               gl.glTranslatef(kierunek*a.x,0,kierunek*a.y);
           }
       }*/
}

void TSection::setCamRotation(float metry, float ob) {
    /* if(type==1){
         float kierunek = 1;
         if(angle > 0) 
             kierunek = -1;

         float aa = -metry*ob/radius*kierunek;
                
         Vector2f a = new Vector2f(0.0f, 0.0f);
         a.rotate(aa, radius);

         if(ob==-1){
             gl.glRotatef((float)(-aa*180f/Math.PI),0,1,0);
         } else {
             aa = -aa;
             gl.glRotatef((float)(-aa*180f/Math.PI),0,1,0);       
         }
     }*/
}

void TSection::saveToStream(QTextStream &out){
            out << "	TrackSection ( \n";
            if (type == 0)
                out << "		SectionCurve ( " << type << " ) " << id << " " << size << " " << val1 << " \n";
            else
                out << "		SectionCurve ( " << type << " ) " << id << " " << angle << " " << radius << " \n";
            out << "	)\n";
}

void TSection::loadUtf16Data(FileBuffer *data){
                    type = (int) ParserX::GetNumber(data);
                    id = (int) ParserX::GetNumber(data);
                    if (type == 0) {
                        size = ParserX::GetNumber(data);
                        val1 = ParserX::GetNumber(data);
                    } else {
                        angle = ParserX::GetNumber(data);
                        radius = ParserX::GetNumber(data);
                    }
}