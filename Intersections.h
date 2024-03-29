/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef INTERSECTIONS_H
#define	INTERSECTIONS_H

class Intersections {
public:
    static float pointSegmentDistance(float* v, float* w, float* p, float* intersectionPoint = 0);
    static float pointSegmentSquaredDistanceXZ(float* p1, float* p2, float* p);
    static bool segmentIntersection(float &p0_x, float &p0_y, float &p1_x, float &p1_y, 
                float &p2_x, float &p2_y, float &p3_x, float &p3_y, float &i_x, float &i_y);
    static int segmentIntersectsTriangle(float *p, float *p2, float *v0, float *v1, float *v2);
    static int shapeIntersectsShape(float *shape1, float *shape2, int count1, int count2, int size1, int size2, float *pos);
private:
    static void vector(float *a, float *b, float *c);
    static float dot(float *b, float *c);
    static void cross(float *a, float *b, float *c);
};

#endif	/* INTERSECTIONS_H */

