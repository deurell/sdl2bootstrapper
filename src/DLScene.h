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
    ~DLScene() = default;
    SceneRequest getSceneRequest();

    void setGlParams(GLuint program);

protected:
    // IRender
    virtual void Initialize(int width, int height);
    virtual void Render() const {}
    virtual void UpdateAnimation(float timeStep) {}
    virtual void OnRotate(DeviceOrientation newOrientation) {}
    virtual void OnFingerUp(ivec2 location) {}
    virtual void OnFingerDown(ivec2 location) {}
    virtual void OnFingerMove(ivec2 oldLocation, ivec2 newLocation) {}

    int getSceneIdentifier();
    void requestScene(SceneRequest scene);

    GLuint mSimpleProgram;
    GLuint mFramebuffer;
    GLuint mColorRenderbuffer;
    GLuint mDepthRenderbuffer;
    float mHeight;
    float mWidth;

private:
    int mSceneIdentifier;
    SceneRequest mSceneRequest;

    friend class DLApplication;
};
