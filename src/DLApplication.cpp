
#include "DLApplication.h"
#include "SplashScene.h"

void DLApplication::UpdateAnimation(float timeStep) {
    if(!SceneAvailable()) return;
    mScene->UpdateAnimation(timeStep);
    SceneRequest request = mScene->getSceneRequest();
    if(request.Scene != 0) {
        SetupNextScene(request);
    }
}

void DLApplication::SetupNextScene(SceneRequest /*request*/) {
    if(mScene != nullptr) {
        delete mScene;
        mScene = nullptr;
    }
    DLScene *scene = new SplashScene();
    scene->setGlParams(mSimpleProgram);
    scene->Initialize(mWidth, mHeight);
    mScene = scene;
}

DLApplication::DLApplication() : mCurrentScene(SceneRequest(0)) {
    mScene = new SplashScene();
}

DLApplication::~DLApplication() {
    delete mScene;
}

void DLApplication::Initialize(int width, int height) {
    mHeight = height;
    mWidth = width;

    mSimpleProgram = BuildProgram(SimpleVertexShader, SimpleFragmentShader);
    glUseProgram(mSimpleProgram);

    // Set the projection matrix.
    GLint projectionUniform = glGetUniformLocation(mSimpleProgram, "Projection");
    mat4 projectionMatrix = mat4::Frustum(-1.6f, 1.6, -2.4, 2.4, 1, 100);
    glUniformMatrix4fv(projectionUniform, 1, 0, projectionMatrix.Pointer());

    mScene->setGlParams(mSimpleProgram);
    mScene->Initialize(width, height);
}

void DLApplication::Render() const {
    if(!SceneAvailable()) return;
    mScene->Render();
}

void DLApplication::OnRotate(DeviceOrientation newOrientation) {
    if(!SceneAvailable()) { return; }
    mScene->OnRotate(newOrientation);
}

void DLApplication::OnFingerUp(ivec2 location) {
    if (!SceneAvailable()) { return; }
    mScene->OnFingerUp(location);
}

void DLApplication::OnFingerDown(ivec2 location) {
    if (!SceneAvailable()) { return; }
    mScene->OnFingerUp(location);
}

void DLApplication::OnFingerMove(ivec2 oldLocation, ivec2 newLocation) {
    if (!SceneAvailable()) { return; }
}

GLuint DLApplication::BuildShader(const char* source, GLenum shaderType) const {
    GLuint shaderHandle = glCreateShader(shaderType);
    glShaderSource(shaderHandle, 1, &source, nullptr);
    glCompileShader(shaderHandle);

    GLint compileSuccess;
    glGetShaderiv(shaderHandle, GL_COMPILE_STATUS, &compileSuccess);

    if (compileSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetShaderInfoLog(shaderHandle, sizeof(messages), nullptr, &messages[0]);
        std::cout << messages;
        exit(1);
    }

    return shaderHandle;
}

GLuint DLApplication::BuildProgram(const char* vShader,
                                   const char* fShader) const {
    GLuint vertexShader = BuildShader(vShader, GL_VERTEX_SHADER);
    GLuint fragmentShader = BuildShader(fShader, GL_FRAGMENT_SHADER);

    GLuint programHandle = glCreateProgram();
    glAttachShader(programHandle, vertexShader);
    glAttachShader(programHandle, fragmentShader);
    glLinkProgram(programHandle);

    GLint linkSuccess;
    glGetProgramiv(programHandle, GL_LINK_STATUS, &linkSuccess);
    if (linkSuccess == GL_FALSE) {
        GLchar messages[256];
        glGetProgramInfoLog(programHandle, sizeof(messages), nullptr, &messages[0]);
        std::cout << messages;
        exit(1);
    }
    return programHandle;
}

bool DLApplication::SceneAvailable() const {
    return mScene != nullptr;
}
