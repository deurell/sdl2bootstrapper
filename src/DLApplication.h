#include "IRender.hpp"
#include <iostream>
#include "SplashScene.h"
#include "SceneRequest.h"

#define STRINGIFY(A)  #A
#include "../Shaders/Simple.vert"
#include "../Shaders/Simple.frag"

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
    DLScene *mSceneObject;

    GLuint BuildShader(const char* source, GLenum shaderType) const;
    GLuint BuildProgram(const char* vShader, const char* fShader) const;

    GLuint mSimpleProgram;
    GLuint mFramebuffer;
    GLuint mColorRenderbuffer;
    GLuint mDepthRenderbuffer;

    GLuint mVertexBuffer;
    GLuint mIndexBuffer;

    float mHeight;
    float mWidth;

    SceneRequest mCurrentScene;

    void SetupNextScene(SceneRequest sceneRequest);
};

IRender* CreateApplication() {
    return new DLApplication();
}

void DLApplication::UpdateAnimation(float timeStep) {
    if(!SceneAvailable()) return;
    mSceneObject->UpdateAnimation(timeStep);
    SceneRequest request = mSceneObject->getSceneRequest();
    if(request.Scene != 0) {
        SetupNextScene(request);
    }
}

void DLApplication::SetupNextScene(SceneRequest /*request*/) {
    if(mSceneObject != nullptr) {
        delete mSceneObject;
        mSceneObject = nullptr;
    }
    DLScene *scene = new SplashScene();
    scene->setGlParams(mSimpleProgram);
    scene->Initialize(mWidth, mHeight);
    mSceneObject = scene;
}

DLApplication::DLApplication() : mCurrentScene(SceneRequest(0)) {
    mSceneObject = new SplashScene();
}

DLApplication::~DLApplication() {
    delete mSceneObject;
}

void DLApplication::Initialize(int width, int height) {
    mHeight = height;
    mWidth = width;

    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);

    mSimpleProgram = BuildProgram(SimpleVertexShader, SimpleFragmentShader);
    glUseProgram(mSimpleProgram);

    // Set the projection matrix.
    GLint projectionUniform = glGetUniformLocation(mSimpleProgram, "Projection");
    mat4 projectionMatrix = mat4::Frustum(-1.6f, 1.6, -2.4, 2.4, 1, 100);
    glUniformMatrix4fv(projectionUniform, 1, 0, projectionMatrix.Pointer());

    mSceneObject->setGlParams(mSimpleProgram);
    mSceneObject->Initialize(width, height);
}

void DLApplication::Render() const {
    if(!SceneAvailable()) return;
    mSceneObject->Render();
}

void DLApplication::OnRotate(DeviceOrientation newOrientation) {
    if(!SceneAvailable()) { return; }
    mSceneObject->OnRotate(newOrientation);
}

void DLApplication::OnFingerUp(ivec2 location) {
    if (!SceneAvailable()) { return; }
    mSceneObject->OnFingerUp(location);
}

void DLApplication::OnFingerDown(ivec2 location) {
    if (!SceneAvailable()) { return; }
    mSceneObject->OnFingerUp(location);
}

void DLApplication::OnFingerMove(ivec2 previous, ivec2 location) {
    if (!SceneAvailable()) { return; }
}

GLuint DLApplication::BuildShader(const char* source, GLenum shaderType) const {
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, 0);
    glCompileShader(shaderHandle);

    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);

    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        exit(1);
    }

    return shaderHandle;
}

GLuint DLApplication::BuildProgram(const char* vertexShaderSource,
                                      const char* fragmentShaderSource) const {
    GLuint vertexShader = BuildShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = BuildShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);

    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), 0, &messages[0]);
        std::cout << messages;
        exit(1);
    }
    return programHandle;
}

bool DLApplication::SceneAvailable() const {
    return mSceneObject != nullptr;
}
