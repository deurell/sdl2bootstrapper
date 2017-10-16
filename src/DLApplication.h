#pragma once

#include "IRender.hpp"
#include "SceneRequest.h"
#include "glad/glad.h"

#define STRINGIFY(A)  #A
#include "../Shaders/Simple.vert"
#include "../Shaders/Simple.frag"

class DLScene;

using namespace std;

class DLApplication : public IRender {
public:
    DLApplication();
    ~DLApplication() override;

    void Initialize(int width, int height) override;
    void Render() const override;
    void UpdateAnimation(float timeStep) override;
    void OnRotate(DeviceOrientation newOrientation) override;
    void OnFingerUp(ivec2 location) override;
    void OnFingerDown(ivec2 location) override;
    void OnFingerMove(ivec2 oldLocation, ivec2 newLocation) override;

    bool SceneAvailable() const;

private:
    void SetupNextScene(SceneRequest sceneRequest);

    DLScene *mScene;
    GLuint BuildShader(const char* source, GLenum shaderType) const;
    GLuint BuildProgram(const char* vShader, const char* fShader) const;
    GLuint mSimpleProgram{};
    int mHeight{};
    int mWidth{};
    SceneRequest mCurrentScene;
};

