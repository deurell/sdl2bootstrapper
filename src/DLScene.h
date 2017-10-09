//
//  DLScene.h
//  TouchCone
//
//  Created by Mikael Deurell on 12/06/2012.
//
//

#pragma once

#include "SceneRequest.h"
#include <glad/glad.h>
#include "IRender.hpp"

class DLScene : public IRender {

public:
    DLScene();
    ~DLScene() override = default;
    SceneRequest getSceneRequest();

    void setGlParams(GLuint program);

protected:
    // IRender
    void Initialize(int width, int height) override;
    void Render() const override;
    void UpdateAnimation(float timeStep) override {}
    void OnRotate(DeviceOrientation newOrientation) override {}
    void OnFingerUp(ivec2 location) override {}
    void OnFingerDown(ivec2 location) override {}
    void OnFingerMove(ivec2 oldLocation, ivec2 newLocation) override {}

    int getSceneIdentifier();
    void requestScene(SceneRequest scene);

    GLuint mSimpleProgram;
    float mHeight;
    float mWidth;

private:
    int mSceneIdentifier;
    SceneRequest mSceneRequest;

    friend class DLApplication;
};
