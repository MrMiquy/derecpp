#include "../headers/MainWindow.h"

void MainWindow::initElements() {
    grid.setTable(4, 3);
    grid.setCellSize({128, 128});
    grid.setColor({50, 37, 33, 255});
    grid.setPadding({3, 3, 3, 3});
    grid.setDock(TopRightDock);
    grid.bindScrollUpFunction(std::bind(&MainWindow::gridScrollUp, this));
    grid.bindScrollDownFunction(std::bind(&MainWindow::gridScrollDown, this));
    grid.bindWinResizeFunction(std::bind(&MainWindow::gridWinResize, this));
    addElement(&grid);

    gridOffset.setDuration(75);
    gridOffset.setValue(grid.yOffsetReference());
    addAnimation(&gridOffset);

    art1.setImage("art1.png");
    art2.setImage("art2.png");
    art3.setImage("art3.png");
    art4.setImage("art4.png");
    art5.setImage("art5.png");
    art6.setImage("art6.png");
    art7.setImage("art7.png");
    art8.setImage("art8.png");
    art9.setImage("art9.png");
    addChild(&grid, &art1);
    addChild(&grid, &art2);
    addChild(&grid, &art3);
    addChild(&grid, &art4);
    addChild(&grid, &art5);
    addChild(&grid, &art6);
    addChild(&grid, &art7);
    addChild(&grid, &art8);
    addChild(&grid, &art9);
}

void MainWindow::gridWinResize() {
    grid.setDockGeometry({0, 0, winSize.x, winSize.y});
}

void MainWindow::gridScrollUp() {
    if (!gridOffset.isAnimating() && grid.getOffset().y < 0) {
        gridOffset.setRange(grid.getOffset().y, grid.getOffset().y + grid.getCellSize().y);
        gridOffset.play();
    }
}

void MainWindow::gridScrollDown() {
    if (!gridOffset.isAnimating() && grid.getOffset().y > -(grid.getCol() * grid.getCellSize().y / 2)) {
        gridOffset.setRange(grid.getOffset().y, grid.getOffset().y - grid.getCellSize().y);
        gridOffset.play();
    }
}

MainWindow::MainWindow() {
}

MainWindow::~MainWindow() {
}
