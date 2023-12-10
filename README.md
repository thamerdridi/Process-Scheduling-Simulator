Process Scheduling Simulator

Introduction
Welcome to the Process Scheduling Simulator. This simulator is designed to allow users to experiment with various process scheduling algorithms in a controlled environment. It's an ideal tool for understanding the complexities and behaviors of different scheduling methods in operating system design.

Prerequisites
gcc: A C compiler to compile the source code.
make: A build automation tool to simplify the compilation process.

Getting Started

Step 1: Extract the Zip File
Download and extract the provided zip file into your chosen directory. This directory should contain the source code and the Makefile.

Step 2: Compile the Simulator
Navigate to the directory in your terminal and compile the simulator:
make
This command compiles the source code and generates an executable named main.

Step 3: Generate Processes
Execute the simulator to generate a configuration file:
./main
Follow the prompts to define the number of processes. The generated process details will be stored in file1.txt.

Step 4: Simulate Scheduling Algorithms
The simulator offers several scheduling algorithms to choose from:

FIFO (First-In-First-Out) [By Default]
SRT (Shortest Remaining Time)
RR (Round Robin)
Priority (Preemptive Priority)
Select an algorithm and, if required, provide additional parameters (e.g., quantum time for RR).

Step 5: Review Simulation Results
After running a simulation, the terminal will display the results, including a Gantt chart and the average wait/turnaround times. This will help you evaluate the efficiency of the chosen scheduling algorithm.

Step 6: Clean Up (Optional)
You can clean up the compiled objects and executable using:
make clean

Step 7: Modify and Experiment
Feel free to modify file1.txt to alter process parameters, or change the source code for deeper experimentation.

Contributing
Contributions to improve the simulator or extend its functionalities are welcome. Please feel free to fork the repository, make changes, and submit pull requests.

License
This project is licensed under MIT License.

Support
For support or further information, please contact Support Team.
