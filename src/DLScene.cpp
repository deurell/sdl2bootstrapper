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

int DLScene::GetSceneIdentifier() const {
    return mSceneIdentifier;
}

void DLScene::RequestScene(SceneRequest scene) {
    mSceneRequest = scene;
}

void DLScene::SetShaders(GLuint program) {
    mProgram = program;
}

void DLScene::Initialize(int width, int height) {
    mWidth = width;
    mHeight = height;
}

void DLScene::Render() const {}

SceneRequest DLScene::GetSceneRequest() {
    return mSceneRequest;
}
