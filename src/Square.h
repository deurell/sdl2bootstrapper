//
//  Square.h
//
//  Created by Mikael Deurell on 12/05/2012.
//
//

#pragma once

#include "Vector.h"
#include <vector>
#include <glad/glad.h>

using namespace std;

struct Vertex {
    vec3 Position;
    vec4 Color;
};


class Square
{
public:
    Square();
    void GenerateVertices(vector<Vertex>& vertices, vector<GLubyte>& indices, vec4 color);
    void setOffset(vec3 offset);
    void setScale(vec3 scale);
    int getVerticesCount() const;
    int getIndicesCount() const;
    
private:
    vec3 m_offset;
    vec3 m_scale;
};
