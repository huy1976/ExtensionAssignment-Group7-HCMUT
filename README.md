# 🧮 Handheld Calculator Project - ATmega324P
**Course: Microcontroller Practice (Extended) - Group 7 - HCMUT**

This project focuses on the design and implementation of a multi-functional handheld calculator based on the **ATmega324P** microcontroller. The project was developed and simulated using Proteus, evolving from basic laboratory exercises into a comprehensive system with advanced mathematical capabilities.

---

## 👥 Group 7 Members

Below is the list of team members who developed the project:

| No. | Full Name | Primary Role |
| :--- | :--- | :--- |
| 1 | **Duong Minh Nhan** | Team Leader - Logic & Algorithm Programming |
| 2 | **Nguyen Phuc Huy** | GitHub Management & System Analysis |
| 3 | **Duc Quan** | Proteus Simulation & Hardware Design |

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

1.  **Mode Selection:** At the Main Menu, press keys `1` to `4` to select the corresponding mode.
2.  **Function Keys:**
    *   **H Key (Shift)**: Activates secondary functions (sin, cos, log, etc.) in Mode 1 and Mode 2.
    *   **i Key (SW6)**: Inputs the imaginary unit `i` in Complex Number mode.
    *   **DEL Key (SW7)**: Backspace function to quickly correct input errors.
    *   **AC Key (C Button)**: Clears all data and forces the system back to the Main Menu.
3.  **Execution:** Press the **'='** key to obtain calculation results or proceed to the next coefficient input step.

---
*This project was completed for the Extended Microcontroller course at Ho Chi Minh City University of Technology (HCMUT).*
