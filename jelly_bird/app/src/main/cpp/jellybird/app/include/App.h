#ifndef APP_H
#define APP_H

class App {
public:
    App();
    virtual ~App();

    virtual void init() = 0;
    virtual void resume() = 0;
    virtual void loop() = 0;
    virtual void pause() = 0;
    virtual void destroy() = 0;

    virtual void exit() = 0;
};

#endif