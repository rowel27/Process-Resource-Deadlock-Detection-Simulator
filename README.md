# Process-Resource-Deadlock-Detection-Simulator
This C program simulates a simplified operating system environment where multiple processes interact with multiple resources. Each process can either request or hold (be allocated) a resource. The user can define the number of processes and resources, configure their relationships, and detect deadlocks in the system.

The system maintains a matrix that represents the relationship between processes and resources:

0: No relation
1: Process is requesting the resource
2: Process is allocated the resource
Key features include:

Displaying the current process-to-resource relations.
Allowing the user to modify these relations.
Detecting potential deadlocks using a recursive depth-first search approach.
This project demonstrates fundamental concepts of deadlock detection, resource allocation graphs, and graph cycle detection in the context of operating system principles.
