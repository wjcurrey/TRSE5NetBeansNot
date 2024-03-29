/*  This file is part of TSRE5.
 *
 *  TSRE5 - train sim game engine and MSTS/OR Editors. 
 *  Copyright (C) 2016 Piotr Gadecki <pgadecki@gmail.com>
 *
 *  Licensed under GNU General Public License 3.0 or later. 
 *
 *  See LICENSE.md or https://www.gnu.org/licenses/gpl.html
 */

#ifndef SHADER_H
#define	SHADER_H

#include <QOpenGLShaderProgram>

class Shader : public QOpenGLShaderProgram {
public:
    Shader();
    virtual ~Shader();
    unsigned int shaderProgram;
    unsigned int vertexPositionAttribute;
    unsigned int textureCoordAttribute;
    unsigned int pShadowMatrixUniform;
    unsigned int pShadow2MatrixUniform;
    unsigned int pMatrixUniform;
    unsigned int fMatrixUniform;
    unsigned int mvMatrixUniform;
    unsigned int msMatrixUniform;
    unsigned int samplerUniform;
    unsigned int lod;
    unsigned int sun;
    unsigned int brightness;
    unsigned int skyColor;
    unsigned int skyLight;
    unsigned int shaderAlpha;
    unsigned int shaderAlphaTest;
    unsigned int shaderTextureEnabled;
    unsigned int shaderShapeColor;
    unsigned int shaderEnableNormals;
    unsigned int shaderDiffuseColor;
    unsigned int shaderAmbientColor;
    unsigned int shaderSpecularColor;
    unsigned int shaderLightDirection;
    unsigned int shaderSecondTexEnabled;
    unsigned int shaderShadowsEnabled;
    unsigned int shaderBrightness;
    unsigned int shaderFogDensity;
    unsigned int shadow1Res;
    unsigned int shadow1Bias;
    unsigned int shadow2Res;
    unsigned int shadow2Bias;
private:

};

#endif	/* SHADER_H */

