//
// Created by Mikael Deurell on 2017-11-28.
//

#include "DLSimpleScene.h"
#include "Matrix.h"
#include "Camera.h"

DLSimpleScene::DLSimpleScene() {
}

DLSimpleScene::~DLSimpleScene() {
}

void DLSimpleScene::Initialize(int width, int height) {
    DLScene::Initialize(width, height);
}

void DLSimpleScene::Render() const {
    DLScene::Render();

    GLfloat vertices[] = {0.0f, 0.5f, 0.0f,
                          -0.5f, -0.5f, 0.0f,
                          0.5f, -0.5f, 0.0f};

    glClearColor(0.6f, 0.6f, 0.6f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLint deviceUniform = glGetUniformLocation(mSimpleProgram, "Device");
    mat4 deviceRotation = mat4::Rotate(0);
    glUniformMatrix4fv(deviceUniform, 1, 0, deviceRotation.Pointer());

    mat4 rotation = mat4::Rotate(0);
    mat4 scale = mat4::Scale(8);
    mat4 translation = mat4::Translate(0, 0, 0);

    GLint modelviewUniform = glGetUniformLocation(mSimpleProgram, "Modelview");
    mat4 modelviewMatrix = scale * rotation * translation;
    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());

    GLint cameraUniform = glGetUniformLocation(mSimpleProgram, "Camera");

    Camera camera;
    camera.setPosition(Vector3<float>(0, 0, 10));

    glUniformMatrix4fv(cameraUniform, 1, 0, camera.toMatrix().Pointer());

    GLint positionSlot = glGetAttribLocation(mSimpleProgram, "Position");
    glVertexAttribPointer(positionSlot, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(positionSlot);

    GLint colorSlot = glGetAttribLocation(mSimpleProgram, "SourceColor");
    glVertexAttrib4f(colorSlot, 0, 0, 1, 1);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glDisableVertexAttribArray(positionSlot);

}

void DLSimpleScene::UpdateAnimation(float timeStep) {
    DLScene::UpdateAnimation(timeStep);
}
