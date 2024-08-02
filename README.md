# Maze-Generator-Path-Finder

## Overview

Maze-Generator-Path-Finder is a powerful tool for generating and solving mazes using depth-first search and random wall-breaking techniques. This C++ project allows users to create multiple mazes and find paths through them, utilizing advanced data structures and algorithms. Additionally, it includes a visualization tool, `mazeDrawer`, to help you visualize the generated mazes.

## Features

- **Maze Generation**: Create mazes with customizable dimensions and wall configurations.
- **Path Finding**: Use depth-first search to find paths through the maze.
- **File Output**: Save generated mazes and paths to text files.
- **Visualization Tool**: Visualize the mazes using the `mazeDrawer` program.

## Project Structure

- `MazeGenPathFinder.cpp`: The main program file for maze generation and solving.
- `dStack.h`: Custom stack implementation.
- `randgen.h`: Random number generator.
- 
## Usage

### Maze Generation

To generate mazes, you will be prompted to enter the number of mazes, the number of rows, and the number of columns for each maze. The program will create the specified number of mazes and store them in text files.

Example:
```plaintext
Enter the number of mazes: 3
Enter the number of rows and columns (M and N): 10 10
```

### Path Finding

To find a path through a maze, you will be prompted to enter the maze ID, entry coordinates, and exit coordinates. The program will find a path and store it in a text file.

Example: 
```plaintext
Enter a maze ID between 1 to 3 inclusive to find a path: 1
Enter x and y coordinates of the entry points (x,y) or (column,row): 0 0
Enter x and y coordinates of the exit points (x,y) or (column,row): 9 9
```
## Visualization

We provide a `mazeDrawer` program (`mazeDrawer.exe` for Windows, `mazeDrawer.linux` for Linux, and `mazeDrawer.mac` for macOS machines) to visualize any given maze. To draw the maze for a given input file (e.g., `maze_1.txt`), follow the instructions below:

**For Windows:**

1. Place `mazeDrawer.exe` and `libpwinthread-1.dll` along with the input files into the same folder.
2. Run `mazeDrawer.exe`.
3. Follow the on-screen instructions to visualize your maze.

**For macOS:**

1. Place `mazeDrawer.mac` and the input files into the same folder.
2. Open Terminal.
3. Navigate to the folder containing `mazeDrawer.mac` using the following commands:
   ```bash
   cd /path/to/your/folder
   ```
4. Make the mazeDrawer.mac file executable if it isn't already:
    ```bash
   chmod +x mazeDrawer.mac
     ```
5. Execute the following command:    
 ```bash
    ./mazeDrawer.mac
  ```
6.Follow the on-screen instructions to visualize your maze

**For Linux**

1. Place mazeDrawer.linux and the input files into the same folder.
2. Open a terminal in the folder.
3. Make the mazeDrawer.linux file executable if it isn't already:
  ```bash
    chmod +x mazeDrawer.linux
  ```
4. Execute the following command:
   ```bash
    ./mazeDrawer.linux
    ```
5. Follow the on-screen instructions to visualize your maze.

## Example

Here is an example of how to use the `mazeDrawer` program:

```plaintext
Enter the number of mazes: 3
Enter the number of rows and columns (M and N): 10 10
```

In this example:

1. The user is prompted to enter the number of mazes they want to draw.
2. Then, they specify the dimensions of the maze (number of rows and columns).
   
Follow the prompts to input your data and visualize the maze as described.
   







