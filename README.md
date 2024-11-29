# BSP Trees

Binaray Space Partotioning Trees

## Graphic Usage

For use the implementation of the pseudo-Doom/Quake Map using BSP Trees, you need to have the following libraries installed:

for cpp:

- `pybind11`

for python:

- `pygame`

First you need to compile the cpp code using the following command:

```bash
c++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) module.cpp -o bsp_tree_module$(python3-config --extension-suffix)
```

Then you can run the python code.
