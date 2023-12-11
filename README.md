# Traffic Lights Simulation

This project is a C based traffic simulation that utilises C to simulate a junction with traffic on either side of a road. The result is a realistic simulation where cars are let out to pass in 
varied increments, when the traffic light is open on that side. This project was written fully in the vim editor in a shell terminal.
## Features

- C based backend implementation of traffic lights system.
- Linked list implementation for dynamic sorting of traffic.
- Intakes multiple parameters for light probability and traffic amount.
- Contains writeup with tests and reasons for design choices.
- Fully written in Vim editor in a linux terminal.




## Documentation
For the write-up of design choices and experiments:

[Documentation](https://github.com/oliciep/Traffic_Light_Simulation/blob/main/Report.pdf)


## Deployment

To deploy this project, run this script within the directory:

```bash
  gcc -ansi -o runSimulations main.c runSimulations.c runOneSimulation.c
```


## Authors

- [@oliciep](https://www.github.com/oliciep)