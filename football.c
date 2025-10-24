//football.c

/*
Name of Program: football.c
Author: Logan Whitt
KUID: 3152587

Description: asks for a given score int
Outputs: all of the different scoring combinations that could happen in a football game to reach that score

Collaborators: ChatGPT for general bug fixing


Creation Date: 10/17/25 - 10/23/25
*/

#include <stdio.h> 
#include <stdbool.h>
//have checking array and see if it's in it
//if it is, then don't print.

int previously_done_arrays[1000][5] = {{0,0,0,0,0}}; //initalize 1000, 5 length arrays of ints all set to 0


void add_score_to_previously_done_array(int scoreArray[5], int index){
    for (int j = 0; j < 5; j++){    //for each num in the array
        previously_done_arrays[index][j] = scoreArray[j]; // add it to the previously done arrays
    }
    return;
}
bool is_array_zeros(int givenArray[5]){  
    //check if a given array[5] is all 0's
    for (int i = 0; i < 5; i++){ //while i is less than 5
        if (givenArray[i] != 0){    //check if any of the nums doesn't equal 0
            return false;    //it's not all 0's
        }
    }
    return true;    //it's all 0's
}

bool do_arrays_match(int arrayOne[5], int arrayTwo[5]){
    //check if the given arrays match
    for (int i = 0; i < 5; i++){    //iterate through all 5 array spots
        if (arrayOne[i] != arrayTwo[i]){    //if each item doesn't match the other
            return false;    //they do NOT match
        }
    }
    return true;    //they match
}

bool has_score_already_been_reached(int scoreArray[]){
    //check if a score has already been reached via a given score array and a global count of all previously reached scores
    for (int i = 0; i < 1000; i++){ //iterate through the previously done arrays
        bool is_scoreArray_at_end = is_array_zeros(previously_done_arrays[i]); //check if we are at the end of arrays to check
        if (is_scoreArray_at_end == true){  //if we are at the end (we have reached the all 0's portion of the global array)
            add_score_to_previously_done_array(scoreArray, i); //add the current scoreArray to the previously done arrays
            return false;    //this score has NOT been reached, return false
        }
        else{    //we still can continue to iterate
            bool is_matching_arrays = do_arrays_match(previously_done_arrays[i], scoreArray);   //get the bool value of if they match
            if (is_matching_arrays == true){    //if the arrays match
                return true; //return that they MATCH
            }else{   //they don't match
                continue;   //go to next array
            }
        }
    }
    return false;    //just say score hasn't been reached
}


int rec_football(int targetScore, int curScore, int scoreArray[]){
    //recursively search through a target score and a current score
    if (targetScore == curScore){
        bool is_score_a_repeat = has_score_already_been_reached(scoreArray);
        if (is_score_a_repeat == false){
            printf("\n%d TD's 2pt, ",scoreArray[0]);
            printf("%d TD + PAT, ", scoreArray[1]);
            printf("%d TD, ", scoreArray[2]);
            printf("%d 3pt FG, ", scoreArray[3]);
            printf("%d Safety", scoreArray[4]);
            return 0;
        }
    }
    
    if (curScore > targetScore){    //if we overshot
        return 0;    //end this iteration
    }

    int scores_to_add[5] = {8,7,6,3,2};    //add to our score via a nifty array
    
    for (int i = 4; i >= 0; i--){    //for adding each score
        scoreArray[i]++;    //increment the score array depending on which score we added
        rec_football(targetScore, curScore + scores_to_add[i], scoreArray);    //continue rec search while adding whatever score we added to curScore
        scoreArray[i]--;    //reset for next loop iteration
    }


    return 0;    //end of recursive function

}

int football(int targetScore){
    if (targetScore <= 0){    //make sure a valid score was given
        printf("Invalid input: %d given", targetScore);    //tell the user that an invalid score was given
        return 0;    //exit function
    }
    int scores[5] = {0};    //initalize scoreArray
    // ARRAY PATTERN:
    //<TD + 2pt, TD + FG, TD (no PAT), FG, Safety>
    rec_football(targetScore, 0, scores);    //start recurrsive search
    
    return 0;    //exit function
}


int main(){
    /*
    int test_array[5] = {1,2,3,4,5};
    int test = rec_football(25, 25, test_array);
    */
    
    int usrNum; //get user score

    printf("Input a number: \n");    //ask the user to input a number
    scanf("%d", &usrNum);    //get int from user
    football(usrNum);    //start football program with that num

    return 0;    //return out of function
}
