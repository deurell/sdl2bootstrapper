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
    void Initialize(int width, int height) override;
    void Render() const override;
    void Update(float timeStep) override;

private:
    void DrawLogo() const;
    void DrawSquare(vec3 transform, vec4 color) const;
    vec4 GetColorForIndex(int index) const;

    float mDepthDegree;
    float mRotationAngle;
    float mCameraDegree;
    GLfloat mScale;
    GLfloat mDevice;

    GLuint mVertexBuffer;
    GLuint mIndexBuffer;

    float mCoolness;
    Square* mSquare;
    Camera * mCamera;
};
