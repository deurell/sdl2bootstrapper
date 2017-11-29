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

    Vector3<float> GetPosition();
    void SetPosition(Vector3<float> position);
    Vector3<float> GetRotation();
    void SetRotation(Vector3<float> rotation);
    Matrix4<float> ToMatrix();
    
private:
    Vector3<float> mPosition;
    Vector3<float> mRotation;
};

