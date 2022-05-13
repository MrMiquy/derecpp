class Animation {
public:
    Animation();
    ~Animation();

    void setDuration(unsigned int duration);
    void setAcceleration(int beginAcceleration, int endAcceleration);
    void setRange(int from, int to);
    void setValue(int* valueToAnimate);
    void setCycled(bool value);

    bool isCycled();
    unsigned int getDuration();
    bool isAnimating();

    void stop();
    void play();
    bool animate();

private:
    void reset();

    unsigned int counter = 1;
    unsigned int duration = 0;      // frames  |  33 frames - 1 sec
    int beginAcceleration = 1;
    int endAcceleration = 1;
    int from;
    int to;
    int* value;                 // value to animate

    bool cycled = false;
    bool reversed = false;
    bool animating = false;


};
