/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "geometryengine.h"

#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector3D position;
    QVector2D texCoord;
};

//! [0]
GeometryEngine::GeometryEngine()
    : indexBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    // Generate 2 VBOs
    arrayBuf.create();
    indexBuf.create();

    // Initializes cube geometry and transfers it to VBOs
    Hmap.load(":/Hmap220.png");
    Hmap=Hmap.mirrored();
    initPlaneGeometry(128,15.0f,15.0f);
}

GeometryEngine::~GeometryEngine()
{
    arrayBuf.destroy();
    indexBuf.destroy();
}
//! [0]

void GeometryEngine::initCubeGeometry()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.0f)}, // v1
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.0f, 0.5f)},  // v2
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D( 0.0f, 0.5f)}, // v4
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.5f)}, // v5
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.0f, 1.0f)},  // v6
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v8
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(1.0f, 0.5f)},  // v9
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}, // v10
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(1.0f, 1.0f)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v12
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(1.0f, 0.0f)},  // v13
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.66f, 0.5f)}, // v14
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(1.0f, 0.5f)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0f, -1.0f, -1.0f), QVector2D(0.33f, 0.0f)}, // v16
        {QVector3D( 1.0f, -1.0f, -1.0f), QVector2D(0.66f, 0.0f)}, // v17
        {QVector3D(-1.0f, -1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v18
        {QVector3D( 1.0f, -1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0f,  1.0f,  1.0f), QVector2D(0.33f, 0.5f)}, // v20
        {QVector3D( 1.0f,  1.0f,  1.0f), QVector2D(0.66f, 0.5f)}, // v21
        {QVector3D(-1.0f,  1.0f, -1.0f), QVector2D(0.33f, 1.0f)}, // v22
        {QVector3D( 1.0f,  1.0f, -1.0f), QVector2D(0.66f, 1.0f)}  // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };


//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, 24 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, 34 * sizeof(GLushort));
//! [1]
}

void GeometryEngine::initPlaneGeometry(int size,float W, float H)
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.

    float x = -W/2.0f, y = -H/2.0f;
    int i_indices = 0;
    float i_img, j_img;
    float H_min = 0.0f, H_max = 2.0f;
    float z;

    VertexData *vertices = new VertexData[size*size];
    GLushort *indices = new GLushort[(size-1)*(size-1)*6];

    for(int i=0; i<(size*size); i++){

        i_img = ((float) ( (i) % size ) );
        j_img = ((float) ( (i) / size ) );

        // random formula : ( (float) rand()/RAND_MAX)*(H_max-H_min) + H_min

        //cube_texture formula : QVector2D( (i_img/(size-1))/3, (j_img/(size-1))/2 )

        z = ( (float) qRed(Hmap.pixel(i_img*( ( (float)Hmap.width()-1)/(size-1) ),j_img*(( (float)Hmap.height()-1)/(size-1) ) )) )/256.0;
        if(z<1.0/255.0) z = 1.0/255.0;

        vertices[i] = {QVector3D( x + (i_img /(size-1) )*W , y + (j_img /(size-1))*H , z*5.0 ), QVector2D( z, 0.0f )};  // v0

        if(i_img != 0 && j_img != 0){

            int v0 = i - size - 1, v1 = i - 1, v2 = i - size;

            indices[i_indices] = v0;
            indices[i_indices+1] = v2;
            indices[i_indices+2] = v1;

            indices[i_indices+3] = v2;
            indices[i_indices+4] = i;
            indices[i_indices+5] = v1;

            i_indices+=6;
        }
    }
    /*
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0f, -1.0f,  0.0f), QVector2D(0.0f, 0.0f)},  // v0
        {QVector3D(-1.0f,  1.0f,  0.0f), QVector2D(0.0f, 0.5f)},  // v1
        {QVector3D( 1.0f, -1.0f,  0.0f), QVector2D(0.33f, 0.0f)}, // v2
        {QVector3D( 1.0f,  1.0f,  0.0f), QVector2D(0.33f, 0.5f)}, // v3

        {QVector3D( 3.0f, -1.0f,  0.0f), QVector2D(0.66f, 0.0f)}, // v4
        {QVector3D( 3.0f,  1.0f,  0.0f), QVector2D(0.66f, 0.5f)}, // v5

        //{QVector3D( 5.0f, -1.0f,  0.0f), QVector2D(1.0f, 0.0f)}, // v6
        //{QVector3D( 5.0f,  1.0f,  0.0f), QVector2D(1.0f, 0.5f)}, // v7

        //{QVector3D( 7.0f, -1.0f,  0.0f), QVector2D(1.0f, 0.0f)}, // v8
        //{QVector3D( 7.0f,  1.0f,  0.0f), QVector2D(1.0f, 0.5f)}, // v9
    };

    GLushort indices[] = {
        0,  2,  1,
        2,  3,  1,

        2,  4,  3,
        4,  5,  3,



    };*/

//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, size*size * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, (size-1)*(size-1)*6 * sizeof(GLushort));
//! [1]
}

void GeometryEngine::initPlaneSingleGeometry(int size, float W, float H)
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.

    float x = 0.0f, y = 0.0f;
    int i_indices = 0;
    float i_img, j_img, z;
    float H_min = 0.0f, H_max = 1.0f;

    VertexData *vertices = new VertexData[size*size*4];
    GLushort *indices = new GLushort[size*size*6];

    for(int i=0; i<size*size*4; i+=4){

        i_img = ((float) ( (i/4) % size ) );
        j_img = ((float) ( (i/4) / size ) );

        //random formula : ( (float) rand()/RAND_MAX)*(H_max-H_min) + H_min

        z = ( (float) qRed(Hmap.pixel(i_img*( ( (float)Hmap.width()-1)/(size-1) ),j_img*(( (float)Hmap.height()-1)/(size-1) ) )) )/256.0;
        if(z<1.0/255.0) z = 1.0/255.0;

        vertices[i] =   {QVector3D( x+(i_img/(size-1))*W                             , y+(j_img/(size-1))*H                             ,  z*5.0 ),
                                        QVector2D(z, 0.0f)};  // v0

        z = ( (float) qRed(Hmap.pixel(i_img*( ( (float)Hmap.width()-1)/(size-1) ) + ( (float) 1/(size-1) ) ,j_img*(( (float)Hmap.height()-1)/(size-1) ) )) )/256.0;
        if(z<1.0/255.0) z = 1.0/255.0;

        vertices[i+1] = {QVector3D( (x+(i_img/(size-1)) + ( (float) 1/(size-1) ) )*W , y+(j_img/(size-1))*H                             ,  z*5.0 ),
                                        QVector2D(z, 0.0f)}; // v1

        z = ( (float) qRed(Hmap.pixel(i_img*( ( (float)Hmap.width()-1)/(size-1) ),j_img*(( (float)Hmap.height()-1)/(size-1) ) + ( (float) 1/(size-1) ) )) )/256.0;
        if(z<1.0/255.0) z = 1.0/255.0;

        vertices[i+2] = {QVector3D( x+(i_img/(size-1))*W                             , (y+(j_img/(size-1))  + ( (float) 1/(size-1) ))*H ,  z*5.0 ),
                                        QVector2D(z, 0.5f)};  // v2

        z = ( (float) qRed(Hmap.pixel(i_img*( ( (float)Hmap.width()-1)/(size-1) ) + ( (float) 1/(size-1) ),j_img*(( (float)Hmap.height()-1)/(size-1) ) + ( (float) 1/(size-1) ) )) )/256.0;
        if(z<1.0/255.0) z = 1.0/255.0;

        vertices[i+3] = {QVector3D( (x+(i_img/(size-1)) + ( (float) 1/(size-1) ))*W  , (y+(j_img/(size-1))  + ( (float) 1/(size-1) ))*H ,  z*5.0 ),
                                        QVector2D(z, 0.5f)}; // v3


        indices[i_indices] = i;
        indices[i_indices+1] = i+1;
        indices[i_indices+2] = i+2;

        indices[i_indices+3] = i+1;
        indices[i_indices+4] = i+3;
        indices[i_indices+5] = i+2;

        i_indices+=6;
    }


//! [1]
    // Transfer vertex data to VBO 0
    arrayBuf.bind();
    arrayBuf.allocate(vertices, size*size*4 * sizeof(VertexData));

    // Transfer index data to VBO 1
    indexBuf.bind();
    indexBuf.allocate(indices, size*size*6 * sizeof(GLushort));
//! [1]
}

//! [2]
void GeometryEngine::drawCubeGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
}

void GeometryEngine::drawPlaneGeometry(QOpenGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    arrayBuf.bind();
    indexBuf.bind();

    // Offset for position
    quintptr offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, offset, 3, sizeof(VertexData));

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    // Tell OpenGL programmable pipeline how to locate vertex texture coordinate data
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, offset, 2, sizeof(VertexData));

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLES, 10000000, GL_UNSIGNED_SHORT, 0);
}
//! [2]
