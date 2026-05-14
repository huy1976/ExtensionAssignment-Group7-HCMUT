# 🧮 Handheld Calculator Project - ATmega324P
**Course: Microcontroller Practice (Extended) - Group 7 - HCMUT**

This project focuses on the design and implementation of a multi-functional handheld calculator based on the **ATmega324P** microcontroller. The project was developed and simulated using Proteus, evolving from basic laboratory exercises into a comprehensive system with advanced mathematical capabilities.

---

## 👥 Group 7 Members

Below is the list of team members who developed the project:

| No. | Full Name | Primary Role |
| :--- | :--- | :--- |
| 1 | **Nguyen Phuc Huy** | Team Leader - Logic & Algorithm Programming |
| 2 | **Phan Nguyen Nguyen Khoi ** | GitHub Management & System Analysis |
| 3 | **Nguyen Tuan Khanh** | Proteus Simulation & Hardware Design |

---

## 🚀 Project Features

### 📟 Phase 1: LCD 16x2 Display Implementation
In the initial phase, the team implemented fundamental features to master peripheral interfacing:
*   Displaying numerical characters and basic mathematical operations on two lines of the LCD.
*   Performing arithmetic operations: Addition (+), Subtraction (-), Multiplication (*), and Division (/).
*   Processing a 4x4 Keypad Matrix for direct user input.
*   Clear screen functionality to prepare for new calculations.

### 📺 Phase 2: OLED 128x64 Upgrade (I2C Communication)
The team expanded the calculator's capabilities to solve advanced engineering problems:
*   **SCI CALC (Scientific Calculator):** 
    *   Full support for trigonometric and calculus functions: `sin`, `cos`, `tan`, `cot`, and `log`.
    *   Computations involving parentheses `( )`, square roots `sqrt`, and exponents.
*   **PT BAC 2 (Quadratic Equation Solver):**
    *   Solving the equation $Ax^2 + Bx + C = 0$.
    *   Supporting complex expression inputs for coefficients A, B, and C (e.g., $A = \sin(30) + 1$).
    *   Comprehensive case handling: No real roots, double roots, and two distinct roots.
*   **HPT 2 AN (System of 2 Linear Equations):**
    *   Solving systems of two linear equations using Cramer's rule.
*   **CMPLX (Complex Numbers):**
    *   Performing basic operations on complex numbers: Addition, Subtraction, Multiplication, and Division in $A + Bi$ form.

---

## 🛠️ User Guide

### 1. Build and Flash Instructions
To run this project on a real ATmega324P or in a simulation:
*   **Software Requirements**: Install **Microchip Studio** (formerly Atmel Studio) and **Proteus Design Suite**.
*   **Compiling**:
    1. Open the project solution file (`.atsln`) in Microchip Studio.
    2. Select **Release** or **Debug** mode from the configuration toolbar.
    3. Press `F7` or go to `Build > Build Solution` to compile the source code.
    4. Ensure the output window shows `Build: 1 succeeded`, which generates the `.hex` file in the `Debug/` or `Release/` folder.
*   **Loading to Proteus**:
    1. Open the `.pdsprj` file located in the `/simulation` folder.
    2. Double-click on the **ATmega324P** component in the schematic.
    3. In the **Program File** field, browse and select the generated `.hex` file.
    4. Ensure the **CKSEL Fuses** are set to "Internal RC 8.0MHz" (or as configured in your code).
    5. Click the **Play** button at the bottom left to start the simulation.

### 2. Operating the Calculator
Once the simulation is running, follow these steps to use the 4 modes:
*   **Mode Selection**: At the Main Menu, press keys `1` to `4` on the Keypad to enter the desired mode.
*   **Input Handling**:
    *   **Numerical Keys**: Standard input for numbers and decimal points.
    *   **H Key (Shift)**: Activates secondary mathematical functions like `sin`, `cos`, `tan`, `log`, etc.
    *   **i Key (SW6)**: Inputs the imaginary unit `i` for Complex Number calculations.
    *   **DEL Key (SW7)**: Performs a backspace operation to correct the most recent character.
    *   **AC Key (C Button)**: Instantly clears all current data and returns the user to the Main Menu.
*   **Execution**: Press the **'='** key to calculate the result of an expression or to confirm the current coefficient input (A, B, or C).
---
*This project was completed for the Extended Microcontroller course at Ho Chi Minh City University of Technology (HCMUT).*
