//
// Created by ekin4 on 29/04/2017.
//

#include "StateBase.h"

// funny thing that you have to omit `static` here. Learn about global scope
// type qualifiers to understand why.
cogl::StateBase *cogl::StateBase::event_handling_instance;