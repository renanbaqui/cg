# Computer Graphics University Project - 2D Penguin Game [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0) [![Terminal](https://badgen.net/badge/icon/terminal?icon=terminal&label)](https://www.microsoft.com/en-us/windows)

## Project Requirements

- The project should be implemented using the OpenGL API, and the libraries gl, glu, glut are the only ones that can be used.

### Objective

Build a 2d game that a character represented by a penguin is controlled by the user. The penguin's goal is to capture the largest quantity of fish and feed the baby penguin while avoiding being hit by his predator, the giant petrel.
This bird flies horizontally in random altitudes, and each flight the bird dives, trying to capture the penguin.

### Penguin Movement

The penguin is controlled by the user through the keyboard arrow keys and can walk left or right, while it is on land. In the water, the penguin can move up or down.
While on land the penguin must walk upright, with the front part of his body turned to where the movement is. When in the water, the penguin must be laid horizontally, with his nose facing down and head turned to where it is moving to.
