//
//  Camera.cpp
//
//  Created by Mikael Deurell on 28/06/2012.
//
//

#include "Camera.h"
#include "Quaternion.h"

Camera::Camera():
    mPosition(Vector3<float>(0,0,0)),
    mRotation(Vector3<float>(0,0,0))
{}

Vector3<float> Camera::GetPosition() {
    return mPosition;
}

void Camera::SetPosition(Vector3<float> position) {
    mPosition = position;
}

Vector3<float> Camera::GetRotation() {
    return mRotation;
}

void Camera::SetRotation(Vector3<float> rotation) {
    mRotation = rotation;
}

Matrix4<float> Camera::ToMatrix() {
    float xw = mRotation.x;
    float yw = mRotation.y;
    float zw = mRotation.z;
    Quaternion zrq = Quaternion::CreateFromAxisAngle(vec3(0,0,1), -zw);
    Quaternion xrq = Quaternion::CreateFromAxisAngle(vec3(1,0,0), -xw);
    Quaternion yrq = Quaternion::CreateFromAxisAngle(vec3(0,1,0), -yw);
    mat4 rotatedCamera = zrq.Rotated(xrq).Rotated(yrq).ToMatrix();
    mat4 translatedCamera = mat4::Translate(-mPosition.x, -mPosition.y, -mPosition.z);
    mat4 camera = translatedCamera * rotatedCamera;
    return camera;
}
