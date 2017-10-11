//
// Created by ekin4 on 30/04/2017.
//

#ifndef CUSTOMOGL_STATEBASEGLWINDOW_H
#define CUSTOMOGL_STATEBASEGLWINDOW_H

#include "../Constants.h"

namespace cogl {
    class StateBaseGLWindow {
    public:
        virtual void windowsizecallback(
                GLFWwindow *window, int width, int height) = 0; /* purely abstract function */

        static StateBaseGLWindow *event_handling_instance;

        // technically setEventHandling should be finalized so that it doesn't
        // get overwritten by a descendant class.
        virtual void setEventHandling() { event_handling_instance = this; }

        static void windowsizecallback_dispatch(GLFWwindow *window, int width, int height) {
            if (event_handling_instance)
                event_handling_instance->windowsizecallback(window, width, height);
        }
    };
}


#endif //CUSTOMOGL_STATEBASEGLWINDOW_H
