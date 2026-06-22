
# ArenaX - Gaming Matchmaking and Player Management System

## Overview

ArenaX is a C++ console-based simulation of an online gaming matchmaking system that demonstrates the practical application of multiple data structures and algorithms. The project manages player information, rankings, matchmaking fairness, server selection, and player lookup operations efficiently.

## Problem Statement

Online multiplayer games require efficient player management, fair matchmaking, quick player search, ranking systems, and optimal server allocation. ArenaX addresses these challenges using a combination of advanced data structures and algorithms.

## Features

* Player registration and management
* Skill-based ranking using AVL Tree
* Fast player lookup using Hash Map
* Matchmaking queue management using Queue
* Undo functionality using Stack
* Fairness balancing using Priority Queue (Max Heap)
* Server network optimization using Dijkstra's Algorithm
* Player sorting based on skill levels

## Data Structures and Algorithms Used

| Component                  | Purpose                                       |
| -------------------------- | --------------------------------------------- |
| Queue                      | Maintains player waiting order (FIFO)         |
| Stack                      | Supports undo operations (LIFO)               |
| Hash Map (`unordered_map`) | Fast player lookup by ID                      |
| AVL Tree                   | Stores players sorted by skill level          |
| Priority Queue (Max Heap)  | Prioritizes players with longer waiting times |
| Graph                      | Represents game server network                |
| Dijkstra Algorithm         | Finds minimum-latency server paths            |

## System Architecture

```text
Player Data
     |
------------------------------------------------
|              |            |                 |
Queue       AVL Tree     Hash Map          Stack
(Waiting)   (Ranking)    (Lookup)         (Undo)
     |
Priority Queue
(Fairness Balancer)
     |
Graph Network
     |
Dijkstra Algorithm
(Fastest Server Path)
```

## Project Workflow

1. Add players to the system.
2. Store players in multiple data structures.
3. Display matchmaking queue.
4. Perform undo operations.
5. Search players by ID.
6. Sort players by skill.
7. Display AVL-based rankings.
8. Calculate shortest server latency paths.
9. Prioritize players based on waiting time.

## Time Complexity Analysis

| Operation                    | Complexity       |
| ---------------------------- | ---------------- |
| Queue Push/Pop               | O(1)             |
| Stack Push/Pop               | O(1)             |
| Hash Map Lookup              | O(1) Average     |
| AVL Tree Insert              | O(log n)         |
| Sorting Players              | O(n log n)       |
| Priority Queue Insert/Delete | O(log n)         |
| Dijkstra Algorithm           | O((V + E) log V) |

## Sample Players

```cpp
Player(1, "Alice", 85, 30);
Player(2, "Bob", 42, 60);
Player(3, "Charlie", 73, 15);
Player(4, "Diana", 91, 45);
Player(5, "Eve", 58, 20);
Player(6, "Frank", 66, 50);
```

## Compilation and Execution

```bash
g++ ArenaX.cpp -o ArenaX
./ArenaX
```

## Sample Output

```text
Added -> ID:1 Name:Alice Skill:85 WaitTime:30
Added -> ID:2 Name:Bob Skill:42 WaitTime:60
Added -> ID:3 Name:Charlie Skill:73 WaitTime:15

Found ID 2 -> Bob Skill:42
Found ID 4 -> Diana Skill:91

Priority Order:
#1 Bob     WaitTime:60
#2 Frank   WaitTime:50
#3 Diana   WaitTime:45
```

## Learning Outcomes

This project demonstrates:

* AVL Tree balancing and rotations
* Queue and Stack operations
* Hash-based searching
* Heap-based prioritization
* Graph representation and shortest path algorithms
* Practical integration of multiple data structures in a real-world gaming scenario

## Conclusion

ArenaX showcases how multiple data structures and algorithms can work together to build an efficient matchmaking and player management system. The project emphasizes performance, scalability, fairness, and real-world applications of Data Structures and Algorithms.
