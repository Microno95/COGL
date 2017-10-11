//
// Created by ekin4 on 29/04/2017.
//

#ifndef CUSTOMOGL_STATEBASE_H
#define CUSTOMOGL_STATEBASE_H

#include "../Constants.h"

namespace cogl {

    class StateBase {
    public:
        virtual void keycallback(
                GLFWwindow *window,
                int key,
                int scancode,
                int action,
                int mods) = 0; /* purely abstract function */

        static StateBase *event_handling_instance;

        // technically setEventHandling should be finalized so that it doesn't
        // get overwritten by a descendant class.
        virtual void setEventHandling() { event_handling_instance = this; }

        static void keycallback_dispatch(GLFWwindow *window,
                                         int key,
                                         int scancode,
                                         int action,
                                         int mods) {
            if (event_handling_instance)
                event_handling_instance->keycallback(window, key, scancode, action, mods);
        }

        virtual void
        scrollcallback(GLFWwindow *window, double xoffset, double yoffset) = 0; /* purely abstract function */

        static void scrollcallback_dispatch(GLFWwindow *window, double xoffset, double yoffset) {
            if (event_handling_instance)
                event_handling_instance->scrollcallback(window, xoffset, yoffset);
        }
    };

}

#endif //CUSTOMOGL_STATEBASE_H
