/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#include "SoundSourceObj.h"
#include "PoleObj.h"
#include "GLMatrix.h"
#include "TS.h"
#include "ParserX.h"
#include "FileBuffer.h"
#include "SoundList.h"
#include "Game.h"
#include "SoundSource.h"
#include "SoundManager.h"
#include "MstsSoundDefinition.h"

SoundSourceObj::SoundSourceObj() {
}

SoundSourceObj::SoundSourceObj(const SoundSourceObj& o) : WorldObj(o) {

}

WorldObj* SoundSourceObj::clone(){
    return new SoundSourceObj(*this);
}

SoundSourceObj::~SoundSourceObj() {
}

bool SoundSourceObj::allowNew(){
    return true;
}

bool SoundSourceObj::isSoundItem(){
    return true;
}

void SoundSourceObj::load(int x, int y) {
    this->x = x;
    this->y = y;
    this->position[2] = -this->position[2];
    Quat::fill(this->qDirection);
    this->loaded = true;
    
    if(Game::soundEnabled){
        QString path = Game::root+"/routes/"+Game::route+"/sound";
        int sid = MstsSoundDefinition::AddDefinition(path, fileName);
        if(sid != -1){
            if(MstsSoundDefinition::Definitions[sid]->group.size() > 0){
                //soundSourceId = SoundManager::AddSoundSource(MstsSoundDefinition::Definitions[sid]->group.first());
                //SoundManager::Sources[soundSourceId]->setPosition(x, y, position);
            }
        }
    }

    setMartix();
}

void SoundSourceObj::set(QString sh, long long int val){
    if (sh == ("ref_value")) {
        this->fileName = "";
        foreach (SoundListItem* it, Game::soundList->sources){
        //for (auto it = Game::soundList->sources.begin(); it != Game::soundList->sources.end(); ++it ){
            if(it->id == val){
                this->fileName = it->file1;
            }
        }
        return;
    }
    WorldObj::set(sh, val);
    return;
}

void SoundSourceObj::set(QString sh, QString val){
    if (sh == ("filename")) {
        fileName = val;
        return;
    }
    if (sh == ("ref_filename")) {
        fileName = val;
        return;
    }
    WorldObj::set(sh, val);
    return;
}

void SoundSourceObj::set(int sh, FileBuffer* data) {
    if (sh == TS::FileName) {
        data->off++;
        int slen = data->getShort()*2;
        fileName = *data->getString(data->off, data->off + slen);
        data->off += slen;
        return;
    }
    WorldObj::set(sh, data);
    return;
}

void SoundSourceObj::set(QString sh, FileBuffer* data) {
    if (sh == ("filename")) {
        fileName = ParserX::GetString(data);
        return;
    }
    WorldObj::set(sh, data);
    return;
}

void SoundSourceObj::render(GLUU* gluu, float lod, float posx, float posz, float* pos, float* target, float fov, int selectionColor, int renderMode) {
    if (!loaded) return;
    if(!Game::viewInteractives || renderMode == gluu->RENDER_SHADOWMAP) 
        return;
        
    Mat4::multiply(gluu->mvMatrix, gluu->mvMatrix, matrix);
    gluu->currentShader->setUniformValue(gluu->currentShader->mvMatrixUniform, *reinterpret_cast<float(*)[4][4]> (gluu->mvMatrix));
    
    if(selectionColor != 0){
        gluu->disableTextures(selectionColor);
    } else {
        gluu->enableTextures();
    }
    
    if(pointer3d == NULL)
        pointer3d = new PoleObj();
    if(pointer3dSelected == NULL){
        pointer3dSelected = new PoleObj();
        pointer3dSelected->setMaterial(1.0,1.0,0.5);
    }
    
    if(this->selected) 
        pointer3dSelected->render(selectionColor);
    else
        pointer3d->render(selectionColor);
};

int SoundSourceObj::getDefaultDetailLevel(){
    return -4;
}

void SoundSourceObj::save(QTextStream* out){
    if (!loaded) return;
    if(Game::useOnlyPositiveQuaternions)
        Quat::makePositive(this->qDirection);
    
*(out) << "	Soundsource (\n";
*(out) << "		Position ( "<<this->position[0]<<" "<<this->position[1]<<" "<<-this->position[2]<<" )\n";
*(out) << "		FileName ( "<<ParserX::AddComIfReq(this->fileName)<<" )\n";
*(out) << "		UiD ( "<<this->UiD<<" )\n";
*(out) << "	)\n";
}