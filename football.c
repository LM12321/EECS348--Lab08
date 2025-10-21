//football.c
#include <stdio.h> 
#include <stdbool.h>
//have checking array and see if it's in it
//if it is, then don't print.

int previously_done_arrays[1000][5] = {{0,0,0,0,0}};


void add_score_to_previously_done_array(int scoreArray[5], int index){
    for (int j = 0; j < 5; j++){
        previously_done_arrays[index][j] = scoreArray[j];
    }
    return;
}
bool is_array_zeros(int givenArray[5]){
    for (int i = 0; i < 5; i++){
        if (givenArray[i] != 0){
            return false;
        }
    }
    return true;
}

bool do_arrays_match(int arrayOne[5], int arrayTwo[5]){
    for (int i = 0; i < 5; i++){
        if (arrayOne[i] != arrayTwo[i]){
            return false;
        }
    }
    return true;
}

bool has_score_already_been_reached(int scoreArray[]){
    for (int i = 0; i < 1000; i++){ //iterate through the previously done arrays
        bool is_scoreArray_at_end = is_array_zeros(previously_done_arrays[i]); //check if we are at the end of arrays to check
        if (is_scoreArray_at_end == true){  //if we are at the end
            add_score_to_previously_done_array(scoreArray, i); //add the current scoreArray to the previously done arrays
            return false;    //this score has NOT been reached, return false
        }
        else{
            bool is_matching_arrays = do_arrays_match(previously_done_arrays[i], scoreArray);   //get the bool value of if they match
            if (is_matching_arrays == true){    //if the arrays match
                return true; //return that they MATCH
            }else{
                continue;   //go to next array
            }
        }
    }
    return false;
}


int rec_football(int targetScore, int curScore, int scoreArray[]){
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
    
    if (curScore > targetScore){
        return 0;
    }

    int scores_to_add[5] = {8,7,6,3,2};
    
    for (int i = 4; i >= 0; i--){
        scoreArray[i]++;
        rec_football(targetScore, curScore + scores_to_add[i], scoreArray);
        scoreArray[i]--;
    }


    return 0;

}

int football(int targetScore){
    if (targetScore <= 0){
        printf("Invalid input: %d given", targetScore);
        return 0;
    }
    int scores[5] = {0};
    // ARRAY PATTERN:
    //<TD + 2pt, TD + FG, TD (no PAT), FG, Safety>
    rec_football(targetScore, 0, scores);

    return 0;
}


int main(){
    /*
    int test_array[5] = {1,2,3,4,5};
    int test = rec_football(25, 25, test_array);
    */
    
    int usrNum;

    printf("Input a number: \n");
    scanf("%d", &usrNum);
    football(usrNum);

    return 0;
}