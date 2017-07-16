//
// Created by mikae on 2017-07-16.
//

#ifndef SDL2_GLAD_DLAPPLICATION_H
#define SDL2_GLAD_DLAPPLICATION_H


class DLApplication {

public:
    void run();

private:
    void sdlDie(const char *message);
    void initScreen(const char* title);
    void render();
};


#endif //SDL2_GLAD_DLAPPLICATION_H
