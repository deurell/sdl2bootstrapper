//
//  DLScene.cpp
//
//  Created by Mikael Deurell on 12/06/2012.
//
//

#include "DLScene.h"

DLScene::DLScene() :
        mSceneRequest(SceneRequest(0)),
        mSceneIdentifier(0),
        mWidth(0),
        mHeight(0)
{}

int DLScene::getSceneIdentifier() {
    return mSceneIdentifier;
}

void DLScene::requestScene(SceneRequest scene) {
    mSceneRequest = scene;
}

void DLScene::setGlParams(GLuint program) {
    mSimpleProgram = program;
}

void DLScene::Initialize(int width, int height) {
    mWidth = width;
    mHeight = height;
}

SceneRequest DLScene::getSceneRequest() {
    return mSceneRequest;
}
