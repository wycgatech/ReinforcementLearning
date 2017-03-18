//
//  RLearning.cpp
//  AI_GridWorld
//
//  Created by cpsfaculty on 11/23/14.
//  Copyright (c) 2014 ___Ju Shen___. All rights reserved.
//

#include <stdio.h>
#include "RLearning.h"




/******************************************************   You need to implement the two functions below   ***********************************************/

void RLearning::updateLocation(int action)
{
	if(action == GO_EAST){
		if(cur_loc.x == 3 || (cur_loc.x == 0 && cur_loc.y == 1)){
			return;
		}
		else
			cur_loc.x ++;
	}
	if(action == GO_SOUTH){
		if(cur_loc.y == 2 || (cur_loc.x == 1 && cur_loc.y == 0)){
			return;
		}
		else
			cur_loc.y ++;
	}
	if(action == GO_NORTH){
		if(cur_loc.y == 0 || (cur_loc.x == 1 && cur_loc.y == 2)){
			return;
		}
		else
			cur_loc.y --;
	}
	if(action == GO_WEST){
		if(cur_loc.x == 0 || (cur_loc.x == 2 && cur_loc.y == 1)){
			return;
		}
		else
			cur_loc.x --;
	}
}

//This function is to calculate the f function. Since it is too long so I write it here in order to make it clear. 
float RLearning::cal_f(int x, int y, int action){
	return states[y][x].q_values[action] + K / states[y][x].n_value[action];
}


/* This function should return one of the four actions from "GO_EAST", "GO_WEST", "GO_NORTH", and "GO_SOURTH". The action should be generated based on the "COUNT" and "Q-values" for each of the four actions at the current state. Then choose the one with the maximum f() value: f(Q, N) = Q + K/N, where Q represents the current q value for action a; N is the count recorded for taking action a from current state. K is just a constant value. You can create any variables (or data members) as you need in this class (either in the "RLearning.h" file or "RLearning.cpp" file */
int RLearning::getAction()
{
    int action = 0; //this is just an example, you need to change the action value based on the exploration function
    float tem_f;
	float max_f = -10000;
	for(int i = 0; i <= 3; i ++){
		tem_f = cal_f(cur_loc.x, cur_loc.y, i);
		if(tem_f > max_f){
			max_f = tem_f;
			action = i;
		}
	}
    return action;
}


/*Actually this function is suggested to implemented first. This function is similar to the function you implemented as last assignment for MDP. According to the input action and the current location "cur_loc", determine the next location of the variable. To make it easier, this time we assume if you take action north, you have 100% to land to the north as long as there is another square available in the north. Only if you are already on the North bounary or the square in the north is a wall, which is at the location (1, 1), you will bounce back to current location. After the next location is determined, you need to update the corresponding q value. Finally update the variable "cur_loc" by the new location coordinate. There are three steps involved in this function:*/
void RLearning::move(int action)
{
    //Step 1 - determine the next location from the input action and the current location "cur_loc"
    Point old_loc;
	float tem_f;
	float max_f = -10000;
	old_loc.x = cur_loc.x;
	old_loc.y = cur_loc.y;
	updateLocation(action);
	//update n value
	states[old_loc.y][old_loc.x].n_value[action] ++;
	//find the max f value for next state
	for(int i = 0; i <= 3; i ++){
		tem_f = cal_f(cur_loc.x, cur_loc.y, i);
		if(tem_f > max_f)
			max_f = tem_f;
	}
    //Step 2 - update the q values from the variables states[y][x], where (x, y) represents the current location of the circle
	if(cur_loc.x == 3 && cur_loc.y == 0){
		states[old_loc.y][old_loc.x].q_values[action] = (1 - ALPHA) * states[old_loc.y][old_loc.x].q_values[action] + ALPHA * 1;
	}
	else if(cur_loc.x == 3 && cur_loc.y == 1){
		states[old_loc.y][old_loc.x].q_values[action] = (1 - ALPHA) * states[old_loc.y][old_loc.x].q_values[action] + ALPHA * (-1);
	}
	else 
		states[old_loc.y][old_loc.x].q_values[action] = (1 - ALPHA) * states[old_loc.y][old_loc.x].q_values[action] + ALPHA * (ACTION_REWARD + GAMMA * max_f);
}

/********************************************************   End of your assignment for this file    *************************************************************/



RLearning::RLearning()
{
    /*Initialize all the state with 0.0 state_value and 0.0 Q_values*/
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            states[y][x].location.x = x; //specify the location for this state
            states[y][x].location.y = y;
            
            states[y][x].state_value = 0.0; //define the state value
            states[y][x].q_values[0] = 0.0; //define the Q value
            states[y][x].q_values[1] = 0.0;
            states[y][x].q_values[2] = 0.0;
            states[y][x].q_values[3] = 0.0;
            
        }
    }
    
    /* Set the special Q value for (0, 3) and (1, 3) */
    states[0][3].q_values[0] = 1.0; //define the Q values for (0, 3)
    states[0][3].q_values[1] = 1.0;
    states[0][3].q_values[2] = 1.0;
    states[0][3].q_values[3] = 1.0;
    states[1][3].q_values[0] = -1.0; //define the Q value for (1, 3)
    states[1][3].q_values[1] = -1.0;
    states[1][3].q_values[2] = -1.0;
    states[1][3].q_values[3] = -1.0;
    
    
    /* Reset the values for the two special states: diamonds (0, 3), pitfall (1, 3). Actually there are no Q-values for these two states as these two states represents the final state of the game. Similarly, for the wall (1, 1), it does not have any state value or Q values. So make sure not to update these three states during your program*/
    states[0][3].state_value = 1.0;
    states[1][3].state_value = -1.0;
    
    
    cur_loc.x = 0;
    cur_loc.y = 2;
    
}


RLearning::~RLearning()
{


}
