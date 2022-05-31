#include <SDL2/SDL.h>
#include <functional>

#ifndef __ANIMATION
#define __ANIMATION

class Animation {
public:
    virtual bool isAnimating() { return animating; }
    virtual bool animate() { return false; safeCallAnimateFunc(); }
    void setLooped(bool value) { looped = value; }
    bool isLooped() { return looped; }
    void setStopFunc(std::function<void()> function)    { stopFunc = function;    }
    void setPlayFunc(std::function<void()> function)    { playFunc = function;    }
    void setAnimateFunc(std::function<void()> function) { animateFunc = function; }

protected:
    bool looped = false;
    bool animating = false;
    int counter = 1;
    std::function<void()> stopFunc;
    std::function<void()> playFunc;
    std::function<void()> animateFunc;

    void safeCallStopFunc()    { if (stopFunc != nullptr) stopFunc();       }
    void safeCallPlayFunc()    { if (playFunc != nullptr) playFunc();       }
    void safeCallAnimateFunc() { if (animateFunc != nullptr) animateFunc(); }
};

template <typename T>
class AnimationWrapper : public Animation {
public:
    virtual void reverseRange() { setRange(to, from); }
    virtual void setDuration(unsigned int milliseconds) { duration = milliseconds; }
    virtual void setRange(T _from, T _to) { from = _from; to = _to; }
    virtual void setValue(T* valueToAnimate) { value = valueToAnimate; }
    virtual T getRangeFrom() { return from; }
    virtual T getRangeTo() { return to; }

    virtual void play() { animating = true; safeCallPlayFunc(); }
    virtual void stop() {
                            counter = 1;
                            animating = false;
                            safeCallStopFunc();
                        }

protected:
    float duration;
    T from;
    T to;
    T* value;      // value to animate
};

class intAnimation : public AnimationWrapper<int> {
public:
    bool animate();
    void addRange(int from, int to);
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

#endif // __ANIMATION
