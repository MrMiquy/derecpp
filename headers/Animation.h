#include <SDL2/SDL.h>

class Animation {
public:
    virtual bool isAnimating() { return animating; }
    virtual void stop() { counter = 1; animating = false; }
    virtual void play() { animating = true; }
    virtual bool animate() { return false; }

protected:
    bool animating = false;
    int counter = 1;
};

template <typename T>
class AnimationWrapper : public Animation {
public:
    virtual void setDuration(unsigned int milliseconds) { duration = milliseconds / 500; }
    virtual void setRange(T _from, T _to) { from = _from; to = _to; }
    virtual void setValue(T* valueToAnimate) { value = valueToAnimate; }
    virtual T getRangeFrom() { return from; }
    virtual T getRangeTo() { return to; }

protected:
    float duration;
    T from;
    T to;
    T* value;      // value to animate
};

class intAnimation : public AnimationWrapper<int> {
public:
    bool animate();
};

class uInt8Animation : public AnimationWrapper<Uint8> {
public:
    bool animate();
};

class ColorAnimation : public AnimationWrapper<SDL_Color> {
public:
    bool animate() override;
    void play() override;
    void stop() override;

    void setRange(SDL_Color _from, SDL_Color _to) override;
    void setDuration(unsigned int milliseconds) override;
    void setValue(SDL_Color* valueToAnimate) override;

protected:
    uInt8Animation r;
    uInt8Animation g;
    uInt8Animation b;
    uInt8Animation a;
};
