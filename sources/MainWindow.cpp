#include "../headers/MainWindow.h"

void MainWindow::initElements() {
    art.setImage("art.png");
    art.setPosition({10, 10});
    art.setDraggable(true);
    addChild(&b, &art);

    b.setGeometry({40, 40, 250, 250});
    b.setColor({50, 37, 33, 255});
    b.setHoverColor({70, 57, 53, 255});
    b.setPressedColor({120, 107, 103, 255});
    b.setAutoColorizing(false);
    addElement(&b);
    b.bindPressedFunction(std::bind(&MainWindow::buttonPressed, this));
    b.bindHoverFunction(std::bind(&MainWindow::buttonHover, this));
    b.bindUnhoverFunction(std::bind(&MainWindow::buttonUnhover, this));
    b.bindUnpressedFunction(std::bind(&MainWindow::buttonUnpressed, this));

    c.setCentre(200, 300);
    c.setRadius(25);
    c.setHoverColor({50, 50, 50, 255});
    c.setPressedColor({150, 150, 150, 255});
    c.setDraggable(true);
    addElement(&c);

    e.setGeometry({300, 100, 100, 50});
    e.setColor({20, 100, 255, 155});
    e.setHoverColor({255, 255, 255, 255});
    addElement(&e);

    l.setText("hello world");
    l.setGeometry({0, 0, 220, 320});
    l.setFont("helvetic.ttf", 18);
    l.setColor({255,255,255,255});
    l.setHoverColor({200,200,200,255});
    l.setPressedColor({100,100,100,255});
    l.setDraggable(true);
    addElement(&l);

    bWidth.setDuration(400);
    bWidth.setValue(b.xReference());
    bWidth.setLooped(true);
    //bWidth.setStopFunc(std::bind(&MainWindow::reverseBColor, this));
    addAnimation(&bWidth);

    bColor.setDuration(300);
    bColor.setRange(b.getColor(), b.getPressedColor());
    bColor.setValue(b.colorReference());
    addAnimation(&bColor);
}

void MainWindow::buttonPressed() {
    bColor.setRange(bColor.getRangeFrom(), b.getPressedColor());
    bColor.play();

    bWidth.setRange(b.getGeometry().x, b.getGeometry().x + 50);
    bWidth.play();
}

void MainWindow::buttonHover() {
    bColor.setRange(bColor.getRangeFrom(), b.getHoverColor());
    bColor.play();

    if (!bWidth.isAnimating() || b.getGeometry().x > -150) {
        bWidth.setRange(b.getGeometry().x, b.getGeometry().x - 50);
        bWidth.play();
    }
}

void MainWindow::buttonUnhover() {
    if (!bColor.isAnimating() && bColor.getRangeTo().r != b.getColor().r) {
        bColor.setRange(bColor.getRangeFrom(), b.getColor());
        bColor.play();
    }
}

void MainWindow::buttonUnpressed() {
    if (!bColor.isAnimating() || bColor.getRangeTo().r != b.getColor().r) {
        bColor.setRange(bColor.getRangeFrom(), b.getColor());
        bColor.play();
    }
}

MainWindow::MainWindow() {
}

MainWindow::~MainWindow() {
}
