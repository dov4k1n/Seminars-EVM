# About

## `Brief`: theaters database console app in c++

Version **`1.0.0`**

This project is my implementation of a task from a computer science course at university.

> ## *Problem:*
>
> Develop a class for storing information about **Theaters**:
> `name`, `director`, `address`, `rating`
> 
> and implement an algorithm for working with an array of object data, which requires:
> 
> - identifying the theater with the highest rating
> - sorting the array by names in reverse order
> - organizing a search by the director's last name, correcting one of the fields and outputting full information about the theater after editing
> - outputting information about theaters with a higher rating than the rating of the theater with the name specified by the user

## To launch the program follow this steps:

0. **Download this project on your local computer**
   
   You can download specific directory of GitHub repository with this tool
   https://download-directory.github.io/

1. **Open `Terminal`**

    if you use Windows, open `WSL` (Windows Subsystem for Linux)

2. **Go to the root folder of this project**

    for example on WSL:

    ```
    cd "/mnt/c/Users/username/my_programs/theater_cpp"
    ```

3. **Create `build` folder**

    by typing

    ```
    mkdir build
    ```

4. **Go to the `build` folder**

    by typing

    ```
    cd build
    ```

5. Type
   
   ```
   cmake ../
   ```

   to automatically create `Make`'s build files

6. If no errors, type
   
   ```
   make
   ```
   
   to build the project

7. If no errors, type
   
   ```
   ./theater
   ```

8. Program is launched!