//
//  SplashScene.h
//
//  Created by Mikael Deurell on 12/06/2012.
//
//

#pragma once

#include <iostream>
#include "DLScene.h"
#include "Quaternion.h"
#include "Square.h"
#include "Animation.h"
#include "Camera.h"

class SplashScene : public DLScene {
    
public:
    SplashScene();
    ~SplashScene() override;

protected:
    virtual void Initialize(int width, int height);
    virtual void Render() const;
    virtual void UpdateAnimation(float timeStep);

private:
    void DrawLogo() const;
    void DrawSquare(vec3 transform, vec4 color) const;
    vec4 GetColorForIndex(int index) const;

    GLfloat mDepthDegree;
    GLfloat mRotationAngle;
    GLfloat mCameraDegree;
    GLfloat mScale;
    GLfloat mDevice;

    GLuint mVertexBuffer;
    GLuint mIndexBuffer;

    float mCoolness;
    Square* mSquare;
    Camera * mCamera;
};
