//
// Created by ekin4 on 30/04/2017.
//

#include "StateBaseGLWindow.h"

// funny thing that you have to omit `static` here. Learn about global scope
// type qualifiers to understand why.
cogl::StateBaseGLWindow *cogl::StateBaseGLWindow::event_handling_instance;