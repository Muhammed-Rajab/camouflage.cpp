# camouflage.cpp

A fun and visual🦎 way to see natural selection in action!


## Description

`camouflage.cpp` is a C++ application that simulates the process of camouflage through a genetic algorithm. It uses the Raylib library for visualization and provides an interactive experience where users can observe how a genetic algorithm evolves to create better camouflage patterns over time.
## Features

- **Genetic Algorithm**: The simulation uses a genetic algorithm to evolve a population of patterns to minimize visibility against a background.
- **Customizable Parameters**: You can tweak parameters such as mutation rate, simulation speed, elite ratio etc.
- **Graphical Interface**: The application utilizes Raylib to provide a real-time graphical representation of the camouflage patterns.
## Installation

```bash
git clone https://github.com/Muhammed-Rajab/camouflage.cpp

cd camouflage.cpp/

g++ main.cpp algos.cpp ga.cpp hsl.cpp -I raylib/include -L raylib/lib/ -lraylib -o camouflage

./camouflage
```
## Dependencies

- `Raylib`: For rendering and GUI functionality.

- `C++17`: The project requires C++17 features for some of the standard library functions.
## Genetic Algorithm Parameters

- **Population Size**: 40x40 grid of individuals
- **Mutation Rate**: 0.05%.
- **Fitness Calculation**: Based on the difference between the hue of the pattern and the background (360 - hue difference).