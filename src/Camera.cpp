//
//  Camera.cpp
//
//  Created by Mikael Deurell on 28/06/2012.
//
//

#include "Camera.h"
#include "Quaternion.h"
#define M_PI 3.1415926535
#define DEGREES_TO_RADIANS(degrees) ((degrees) * (M_PI / 180))

Camera::Camera() :
    mPosition(Vector3<float>(0,0,0)),
    mRotation(Vector3<float>(0,0,0))
{}

Vector3<float> Camera::getPosition() {
    return mPosition;
}

void Camera::setPosition(Vector3<float> position) {
    mPosition = position;
}

Vector3<float> Camera::getRotation() {
    return mRotation;
}

void Camera::setRotation(Vector3<float> rotation) {
    mRotation = rotation;
}

Matrix4<float> Camera::toMatrix() {
    float xw = DEGREES_TO_RADIANS(mRotation.x);
    float yw = DEGREES_TO_RADIANS(mRotation.y);
    float zw = DEGREES_TO_RADIANS(mRotation.z);
    Quaternion zrq = Quaternion::CreateFromAxisAngle(vec3(0,0,1), -zw);
    Quaternion xrq = Quaternion::CreateFromAxisAngle(vec3(1,0,0), -xw);
    Quaternion yrq = Quaternion::CreateFromAxisAngle(vec3(0,1,0), -yw);
    mat4 rotatedCamera = zrq.Rotated(xrq).Rotated(yrq).ToMatrix();
    mat4 translatedCamera = mat4::Translate(-mPosition.x, -mPosition.y, -mPosition.z);
    mat4 camera = translatedCamera * rotatedCamera;
    return camera;
}
