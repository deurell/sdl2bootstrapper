//
//  SplashScene.h
//
//  Created by Mikael Deurell on 12/06/2012.
//
//

#pragma once

#include <iostream>
#include "DLSceneObject.h"
#include "Quaternion.h"
#include "Square.h"
#include "Animation.h"
#include "Camera.h"

class SplashScene : public DLSceneObject {
    
public:
    SplashScene();
    virtual ~SplashScene();

protected:
    virtual void Initialize(int width, int height);
    virtual void Render() const;
    virtual void UpdateAnimation(float timeStep);

private:
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
    
    void DrawLogo() const;
    void DrawSquare(vec3 transform, vec4 color) const;
    vec4 GetColorForIndex(int index) const;
};
