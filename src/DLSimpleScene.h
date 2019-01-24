//
// Created by Mikael Deurell on 2017-11-28.
//
#pragma once
#include "DLScene.h"

class DLSimpleScene : public DLScene {
public:
    DLSimpleScene() = default;
    ~DLSimpleScene() override = default;

protected:
    void Initialize(int width, int height) override;
    void Render() const override;
    void Update(float timeStep) override;
};
