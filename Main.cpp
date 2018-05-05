//
// Created by Tomáš Vopat on 05.05.18.
//

#include "tests/AllTests.h"
#include "ui/CModel.h"
#include "ui/CController.h"
#include "ui/CView.h"

int main() {

    test();

    CModel model;
    CController controller;
    CView view;

    controller.setModel(&model);
    controller.setView(&view);
    view.setModel(&model);
    view.setController(&controller);

    view.start();

    return 0;
}
