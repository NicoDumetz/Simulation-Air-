# My_Radar ✈️

My_Radar aims to simulate air traffic, managing aircraft movements and collisions while avoiding collisions under control towers.

## Installation CSFML

### Linux Ubuntu/Debian

To install CSFML on Linux Ubuntu/Debian distributions, you can use the apt package manager:

```sh
sudo apt-get install libcsfml-dev
```
### Fedora

To install CSFML on Fedora, you can use the DNF package manager:

```sh
sudo dnf install csfml-devel
```
## How to write own script

  To create your own script for My_Radar, follow these guidelines:

- Each line in the script describes either an aircraft or a control tower.
- For aircraft:
  - Use the format: A x y velocity_x velocity_y radius is_landed
    - x and y represent the initial position of the aircraft.
    - velocity_x and velocity_y represent the velocity of the aircraft along the x and y axes, respectively.
    - radius denotes the radius of the aircraft.
    - is_landed indicates whether the aircraft has landed (0 for no, 1 for yes).
- For control towers:
  - Use the format: T x y range
    - x and y represent the position of the control tower.
    - range denotes the range of the control tower.

Here's an example of a script file:
```
A 815 321 1484 166 5 0
A 1589 836 811 936 2 0
A 202 894 103 34 3 0
T 93 47 19
T 49 56 25
```

# How to run
```
make
./my_radar script
```

## Grade

I got the highest mark of the epitech class of 2028 for this project.

## Authors
Thank you for checking out this project! If you have any questions or would like to collaborate, feel free to contact me.

[Nicolas Dumetz](mailto:nicolasdumetzpro@gmail.com)
