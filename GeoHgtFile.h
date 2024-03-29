/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef HGTFILE_H
#define	HGTFILE_H

#include "GeoTerrainFile.h"

class GeoHgtFile : public GeoTerrainFile {
public:
    GeoHgtFile();
    virtual ~GeoHgtFile();
    bool load(int lat, int lon);
    void draw(QImage* &image);
    bool isLoaded();
    float getHeight(float lat, float lon);
private:
    short int** terrainData;
    int rowSize;
    bool loaded = false;
};

#endif	/* HGTFILE_H */

