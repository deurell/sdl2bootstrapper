//
//  SplashScene.cpp
//  TouchCone
//
//  Created by Mikael Deurell on 12/06/2012.
//
//

#include "SplashScene.h"

static const int ColumnCount = 30;
static const int RowCount = 9;

static const int logo[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,
    0,1,1,0,0,1,1,1,0,1,0,1,0,1,1,0,0,1,0,0,0,1,0,1,1,1,0,1,1,1,
    0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,
    0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,
    0,1,0,1,0,1,1,0,0,1,0,1,0,1,1,0,0,1,0,0,1,1,0,1,1,1,0,1,1,1,
    0,1,0,1,0,1,0,0,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,
    0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,
    0,1,1,0,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,0,0,1,
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1
};

SplashScene::SplashScene() :
    mRotationAngle(0),
    mScale(1.2f)
{}

SplashScene::~SplashScene() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    delete mSquare;
    delete mCamera;
}

void SplashScene::Initialize(int width, int height) {
    DLScene::Initialize(width, height);
    mDepthDegree = 0;
    mCoolness = 1451.66f;
    mHeight = height;
    mWidth = width;

    mSquare = new Square();
    mCamera = new Camera();
    mCamera->SetPosition(Vector3<float>(0, 0, 20));
    mCamera->SetRotation(Vector3<float>(0, 0, 0));
    
    vector<Vertex> cubeVertices;
    vector<GLubyte> cubeIndices;
    mSquare->GenerateVertices(cubeVertices, cubeIndices, vec4(0,0,0,1));
    
    glGenBuffers(1, &mVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, cubeVertices.size() * sizeof(cubeVertices[0]),
                 &cubeVertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &mIndexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, cubeIndices.size() * sizeof(cubeIndices[0]),
                 &cubeIndices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SplashScene::Update(float timeStep) {
    DLScene::Update(timeStep);
    float cameraDegree = timeStep * (Pi/180 * 45.0f);
    float val = mCameraDegree + cameraDegree;
    mCameraDegree = fmod(val, TwoPi);

    float wobbleDegree = timeStep * (Pi / 180 * 25.0f);
    val = mDepthDegree + wobbleDegree;
    mDepthDegree = fmod(val, TwoPi);

    auto z = 30 * sin(mCameraDegree);
    auto y = 30 * cos(mCameraDegree);
    auto wobble = (Pi / 180 * 40) * sin(mDepthDegree);
    mCamera->SetPosition(Vector3<float>(0, y, z - 30));
    mCamera->SetRotation(Vector3<float>((Pi / 180 * 270) + mCameraDegree, wobble, -wobble));
}

void SplashScene::Render() const {
    DLScene::Render();
    glClearColor(0.6f, 0.6f, 0.6f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawLogo();
}

void SplashScene::DrawLogo() const {
    int index = 0;
    float zPos = -30;
    float rad = mDepthDegree;
    vec4 color(1,1,1,1);
    float const column_offset = 4;
    float const row_offset = 4;
    for (int row = 0; row < RowCount; row++) {
        for (int column = 0; column<ColumnCount; column++) {
            color = this->GetColorForIndex(index);
            float c = (column - (ColumnCount - 1)/ 2.0f) * column_offset;
            float r = (row - RowCount / 2.0f) * row_offset;
            float degAdd = index * mCoolness * (Pi / 180);
            float amp = 8 * cos(rad + degAdd);
            DrawSquare(vec3(c, -r, zPos + amp), color);
            index++;
        }
    }
}

void SplashScene::DrawSquare(vec3 translate, vec4 color) const {
    GLuint positionSlot = glGetAttribLocation(mProgram, "Position");
    GLuint colorSlot = glGetAttribLocation(mProgram, "SourceColor");
    
    GLuint deviceUniform = glGetUniformLocation(mProgram, "Device");
    mat4 deviceRotation = mat4::Rotate(mDevice);
    glUniformMatrix4fv(deviceUniform, 1, 0, deviceRotation.Pointer());
    
    mat4 rotation = mat4::Rotate(mRotationAngle);
    mat4 scale = mat4::Scale(mScale);
    mat4 translation = mat4::Translate(translate.x, translate.y, translate.z);
    
    GLint modelviewUniform = glGetUniformLocation(mProgram, "Modelview");
    mat4 modelviewMatrix = scale * rotation * translation;
    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());
    
    GLuint cameraUniform = glGetUniformLocation(mProgram, "Camera");
    glUniformMatrix4fv(cameraUniform, 1, 0, mCamera->ToMatrix().Pointer());

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mVertexBuffer);
    
    GLsizei stride = sizeof(Vertex);
    //auto offset = reinterpret_cast<void*>(sizeof(vec3));
    glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, stride, nullptr);
    //glVertexAttribPointer(colorSlot, 4, GL_FLOAT, GL_FALSE, stride, offset);
    glVertexAttrib4f(colorSlot, color.x, color.y, color.z, color.w);
    glEnableVertexAttribArray(positionSlot);
    //glEnableVertexAttribArray(colorSlot);
    glDrawElements(GL_TRIANGLES, mSquare->GetIndicesCount(), GL_UNSIGNED_BYTE, nullptr);
    //glDisableVertexAttribArray(colorSlot);
    glDisableVertexAttribArray(positionSlot);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

vec4 SplashScene::GetColorForIndex(int index) const {
    int col = logo[index];
    switch (col) {
        case 0:
            return {0,0,0,1};
        case 1:
            return {1,1,1,1};
        case 2:
            return {0.2f,0.2f,0.8f,1};
        case 3:
            return {1,1,0,1};
        default:
            return {0,0,0,1};
    }
}
