//
//  Camera.h
//
//  Created by Mikael Deurell on 28/06/2012.
//
//

#pragma once

#include <iostream>
#include "Matrix.h"
#include "Vector.h"

class Camera
{
public:
    Camera();
    ~Camera() = default;

    Vector3<float> getPosition();
    void setPosition(Vector3<float> position);
    Vector3<float> getRotation();
    void setRotation(Vector3<float> rotation);
    Matrix4<float> toMatrix();
    
private:
    Vector3<float> mPosition;
    Vector3<float> mRotation;
};

