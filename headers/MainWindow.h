#include "UI.h"

class MainWindow : public UI {
protected:
    Border b;
    intAnimation bWidth;
    ColorAnimation bColor;

    Circle c;

    Ellipse e;

    Image art;

    Label l;

public:
    MainWindow();
    ~MainWindow();

private:
    void initElements();

    void buttonPressed();
    void buttonHover();
    void buttonUnpressed();
    void buttonUnhover();
};
