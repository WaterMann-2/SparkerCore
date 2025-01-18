# Welcome to Sparker Engine

Sparker Engine is a custom built, Vulkan API engine.

## About Me
I am a standalone dev working on this engine as a learning experience. 
I've only looked at one tutorial and that would be [vulkan-tutorial.com](https://vulkan-tutorial.com/Introduction) and not even all the way through.

Enough about me though, onto the project.

## Project overview

Sparker Engine uses vcpkg on VS-2022 with C++(20)

### Dependencies
* Vulkan
* GLFW
* GLM
* Dear ImGui

There will be more as the project continues as it will need sound handling and networking.

## WIP
I am currently working on moving away from the Tutorial's vulkan implementation and into my own.
While the tutorial is fantastic and I reccomend it to anybody wanting to learn Vulkan, it is as such, a tutorial. 
Besides what's the point on learning an API if you only know how to follow others?

Currently I am moving the renderer over to a static library to decouple the editor and runtime.
After which there will be a GUI that can add and remove objects (Cubes, for now.)
Up next will be model importing and lighting experiments.
