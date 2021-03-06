//
//  Square.cpp
//  cube v 0.5
//
//  Created by Mikael Deurell on 12/05/2012.
//
//

#include "Square.h"

const Vertex Vertices[] = {
    vec3(-1,1,-1),vec4(1,1,1,1),
    vec3(1,1,-1),vec4(1,1,1,1),
    vec3(-1,-1,-1),vec4(1,1,1,1),
    vec3(1,-1,-1),vec4(1,1,1,1),
    vec3(-1,1,1),vec4(1,1,1,1),
    vec3(1,1,1),vec4(1,1,1,1),
    vec3(-1,-1,1),vec4(1,1,1,1),
    vec3(1,-1,1),vec4(1,1,1,1)
};

const GLubyte Indices[] = {
    0,1,2,
    1,2,3,
    4,5,6,
    5,6,7,
    0,4,6,
    0,2,6,
    0,1,4,
    1,4,5,
    1,3,5,
    3,5,7,
    2,6,3,
    3,6,7
};

void Square::setOffset(vec3 offset) {
    mOffset = offset;
}

void Square::setScale(vec3 scale) {
    mScale = scale;
}

int Square::getVerticesCount() const {
    return sizeof(Vertices) / sizeof(Vertex);
}

int Square::getIndicesCount() const {
    return sizeof(Indices) / sizeof(GLubyte);
}

Square::Square() {
    mScale = vec3(1,1,1);
    mOffset = vec3(0,0,0);
}

void Square::GenerateVertices(vector<Vertex>& vertices, vector<GLubyte>& indices, vec4 color) {
    for (int currentVertice = 0; currentVertice < this->getVerticesCount(); currentVertice++)
    {
        Vertex current = Vertices[currentVertice];
        current.Position.x = current.Position.x * mScale.x;
        current.Position.y = current.Position.y * mScale.y;
        current.Position.z = current.Position.z * mScale.z;
        current.Position += mOffset;
        current.Color = current.Color;
        vertices.push_back(current);
    }

    for (int currentIndex=0; currentIndex < this->getIndicesCount(); currentIndex++) {
        indices.push_back(Indices[currentIndex]);
    }
}