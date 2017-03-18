## README

#### Description

**Key word: Reinforcement learning, C++**

This project uses reinforcement learning to detect the best path to get out of a maze. Specifically, the program sends agents into the maze. Each agent keeps making random decisions to go to one of the four directions: up, down, left and right and get the award of choosing such direction. For example, If the movement reduces the distance between agent and the exit of the maze, then the agent gets positive reward of doing that.

There are two ways to end the learning process of current agent: reaching the exit of the maze or falling into traps that will kill the agent. Once the agent reaches a trap, it get a negative number indicating that this direction is not good. 

![reinforcement_learning](C:\Users\Yichuan\Desktop\reinforcement_learning.png)

You can see for each block in the maze, there are four values indicating the cumulative reward of going each direction. The larger the value is, the more the agent is likely to go there. 

#### How to run

This is a C++ project and requires Opencv package to run. Please install relevant package before running the project. 

You can click the up, down, left, right buttons to control the agent, or you can click the play button to let the agent learn by itself. 

