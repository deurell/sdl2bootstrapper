//
//  DLSceneObject.cpp
//
//  Created by Mikael Deurell on 12/06/2012.
//
//

#include "DLSceneObject.h"

DLSceneObject::DLSceneObject() :
        mSceneRequest(SceneRequest(0)),
        mSceneIdentifier(0) {}

int DLSceneObject::getSceneIdentifier() {
    return mSceneIdentifier;
}

void DLSceneObject::requestScene(SceneRequest scene) {
    mSceneRequest = scene;
}

void DLSceneObject::setGlParams(GLuint program) {
    mSimpleProgram = program;
}

void DLSceneObject::Initialize(int width, int height) {
    mWidth = width;
    mHeight = height;
}

SceneRequest DLSceneObject::getSceneRequest() {
    return mSceneRequest;
}
