# CS253_Car_Rental

This project is a car rental system implemented entirely in C++.

## Project Structure

The project consists of a single file:

```CS253_Car_Rental/
│
└── car_rental.cpp   # Main source file for the program
```


## Assumptions

1. **User Interface**: This program does not have a graphical user interface (GUI). Instead, it operates through the command line.
  
2. **Car Attributes**: Each car in the system is assumed to have attributes such as name, model, rental cost, availability status, etc.

3. **User Input Validation**: Minimal input validation is implemented. Users are expected to provide valid input when prompted.

4. **Database Management**: The database management is done explicitly within the code, and no other external sources are used for storing cars and users information.

5. **Single Location**: The rental system assumes a single physical location for managing the cars.

6. **No Authentication**: The system does not include authentication mechanisms.

## Instructions

To run the car rental system, follow these steps:

1. **Clone the Repository**: If you haven't already, clone this repository to your local machine.

    ```
    git clone https://github.com/nrithika/CS253_Car_Rental.git
    ```

2. **Navigate to the Directory**: Change your current directory to the cloned `CS253_Car_Rental` directory.

    ```
    cd CS253_Car_Rental
    ```

3. **Compile the Program**: Compile the `car_rental.cpp` file using a C++ compiler (e.g., g++).

    ```
    g++ -o car_rental car_rental.cpp
    ```

4. **Run the Program**: Execute the compiled program.

    ```
    ./car_rental
    ```

5. **Follow On-screen Instructions**: The program will provide instructions through the command line. Follow them to navigate and interact with the car rental system.

## Usage

Upon running the program, users can perform the following actions:

- **View Available Cars**: Display a list of available cars for rental.
  
- **Rent a Car**: Rent a car from the available options.
  
- **Return a Car**: Return a rented car back to the system.
  
- **Exit the Program**: Terminate the program.

## Dependencies

This project does not have any external dependencies beyond the standard C++ library.

## Contributors

- [Rithika](https://github.com/nrithika)

