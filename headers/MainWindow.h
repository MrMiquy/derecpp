#include "UI.h"

class MainWindow : public UI {
protected:
    Grid grid;
    intAnimation gridOffset;

    Image art;
    Image art1;
    Image art2;
    Image art3;
    Image art4;
    Image art5;
    Image art6;
    Image art7;
    Image art8;
    Image art9;

public:
    MainWindow();
    ~MainWindow();

private:
    void initElements();

    // Custom member-functions
    void gridScrollUp();
    void gridScrollDown();
    void gridWinResize();
};
