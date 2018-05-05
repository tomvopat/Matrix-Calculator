//
// Created by Tomáš Vopat on 05.05.18.
//


#include "ui/CModel.h"
#include "ui/CController.h"
#include "ui/CView.h"

int main() {

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
