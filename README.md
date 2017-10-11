# COGL
Custom OpenGL API

Got annoyed with trying to code opengl stuff as a lot of the APIs are low level. 
In an attempt to have a fast, but capable library that simply takes mesh data and renders it I wrote the code found within.

The simplest way to describe how it works is that it takes vertex and fragment shaders (with a single postprocessing shader) and renders it very quickly.

(Frame rate is around 800FPS for rendering 100 cubes, or 10 Stanford dragons.)

The reason for writing this library is to enable me to visualise the results of 3d simulation data such as from gravitational simulations with a Barnes-Hut tree.
