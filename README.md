# Three Jugs Problem
This problem was given to me in my AI methods coursework in my second year of university.
## The Question

Consider the following water-jug problem. There are 3 jugs that have capacities
of A gallons, B gallons, and C gallons. A pump with an unlimited supply of water is
available which can be used to fill the jugs. Water may be poured from one jug to
another or to the ground. None of the jugs has any measuring marks on it. In the start
state, all the three jugs are empty. This is denoted (0, 0, 0); the first number is the
amount of water in the A-gallon jug, the middle number is the amount of water in the
B-gallon jug, and the last number is the amount of water in the C-gallon jug. For
example, if A=8, B=5, and C=3, a possible next state is (8, 0, 0) which is reached by
pouring water into the 8-gallon jug. From the state (8, 0, 0) a possible next state is (5,
0, 3) which is reached by pouring water from the 8-gallon jug to the 3-gallon jug. From
the state (5, 0, 3) a possible next state is (0, 0, 3) which is reached by pouring water
from the 8-gallon jug to the ground. 

Create a Java or C++ program that uses a depth-first search algorithm that takes A, B and C as input and generates the set of all possible states that can be reached from the start state (0,0,0) by one or more moves.

## Why I chose C++

I am much better at Java than I am at C++ but I saw this as a good opportunity to learn C++. If you see anything that is poorly done in this repository, please create a pull request to show me how I could improve.