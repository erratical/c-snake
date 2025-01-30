# Snake Game in C

This project is a simple implementation of the classic Snake game written in the C programming language. The game involves controlling a snake to eat food, grow longer, and avoid obstacles or its own tail.

## Features

- Classic Snake game mechanics.
- Simple text-based interface.
- Keyboard controls to navigate the snake.

## Requirements

To compile and run this project, you need:

- GCC (GNU Compiler Collection)

## Installation

Follow these instructions to compile and run the Snake game:

1. **Clone the repository:**

    ```sh
    git clone <repository_url>
    cd <repository_directory>
    ```

2. **Compile the project:**

    Use the provided `Makefile` to compile the project. Open a terminal in the project directory and run:

    ```sh
    make
    ```

    This will create an executable file named `snake`.

3. **Run the game:**

    After compiling, you can run the game with:

    ```sh
    make run
    ```

## Makefile Overview

The `Makefile` provided in this project includes several useful commands:

- `make`: Compiles the source files and generates the `snake` executable.
- `make clean`: Removes the `snake` executable and object files.
- `make cleanr`: Cleans the project and clears the terminal screen.
- `make run`: Runs the compiled `snake` executable.

## Controls

- Use the arrow keys to navigate the snake.
- Eat the food to grow longer.
- Avoid hitting the walls or the snake's own tail.

## License

This project is licensed under the MIT License. Feel free to use, modify, and distribute this game.
