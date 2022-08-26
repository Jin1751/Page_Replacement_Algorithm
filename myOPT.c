/*
File Name: myOPT.c
Developed by Jin1751 (github.com/Jin1751)
This code implements one of Page Replacement Algorithm in OS (OPT)
*/

#include <stdio.h>

int main(){
    int r_len, reference[50], f_len, frame[25], frequancy[25], index = 1, pf = 0, max_index = 0, is_same = 0, hit = 0;
    int f0[25], f1[25], f2[25], h[25], future[25];// array f0, f1, f2 is to record each index of frame array, Need more arrays if frame is bigger than 3
    int *arr, isHit = 0;

    printf("Enter number of frames\n");
    scanf("%d", &f_len);//Get Number of Frames for pages (MAX:20)

    printf("Enter number of processes\n");
    scanf("%d", &r_len);//Get Number of processes (MAX: 50)

    printf("Enter processes\n");
    for (int i = 0; i < r_len; i++){
        scanf("%d", &reference[i]);
    } //Get all processes

    printf("Process ");
    for (int i = 0; i < r_len; i++)
    {
        printf("%d ", reference[i]);
        h[i] = -1;
    }//Print processes in one line
    for (int i = 0; i < f_len; i++)//Get all processes
    {
        frame[i] = -1;
    }//Initialize frame array to -1 (To check frame is empty)
    printf("\n");
    
    for (int i = 0; i < r_len; i++)
    {
        is_same = 0;
        for (int j = 0; j < f_len; j++)
        {
            if (frame[j] == reference[i])//If current process is in the frame array
            {
                hit++;//increase 1 hit
                h[i] = 1;//array 'h' is to print when hit ocurred, initialize 1 to h[i]
                is_same = 1;
                f0[i] = frame[0];//array 'f0' is to print which processes were in frame 0, Initialize f0[i]  to frame[0] 
                f1[i] = frame[1];//array 'f1' is to print which processes were in frame 0, Initialize f1[i]  to frame[1] 
                f2[i] = frame[2];//array 'f2' is to print which processes were in frame 0, Initialize f2[i]  to frame[2]
                //if frame is bigger than 3, Initialize more record array(ex. f3, f4... etc) 
            }

        }
        if (!is_same)//If current process is not in the frame array
        {
            if (index < f_len + 1)//If frame array has empty index
            {
                frame[index - 1] = reference[i];//Put process to frame array 
                pf++;//Increase 1 Page Fault
                index++;
                is_same = 0;
                f0[i] = frame[0];//array 'f0' is to print which processes were in frame[0], Initialize f0[i]  to frame[0] 
                f1[i] = frame[1];//array 'f1' is to print which processes were in frame[1], Initialize f1[i]  to frame[1] 
                f2[i] = frame[2];//array 'f2' is to print which processes were in frame[2], Initialize f2[i]  to frame[2] 
                //if frame is bigger than 3, Initialize more record array(ex. f3, f4... etc)
            }
            else
            {
                for(int k = 0; k < f_len; k++){
                    future[k] = 0;
                }//initialize future process non-usage array
                for (int l = i; l < r_len; l++)
                {
                    for (int m = 0; m < f_len; m++)
                    {
                        if (frame[m] != reference[l])//If future process is not in the frame array
                        {
                            if(future[m] == (l - i)){//increase future non usage number
                                future[m] ++;
                            } 
                        }
                    }
                }
                for(int o = 0; o < f_len; o++){//find index of process in frame, which will most unuse in future
                    if(future[max_index] < future[o]){
                        max_index = o;
                    }
                }
                frame[max_index] = reference[i];//change most unuse process in future to current process
                pf++;//increase page fault
                is_same = 0;
                max_index = 0;//reset index
                f0[i] = frame[0];//array 'f0' is to print which processes were in frame[0], Initialize f0[i]  to frame[0] 
                f1[i] = frame[1];//array 'f1' is to print which processes were in frame[1], Initialize f1[i]  to frame[1] 
                f2[i] = frame[2];//array 'f2' is to print which processes were in frame[2], Initialize f2[i]  to frame[2] 
                //if frame is bigger than 3, Initialize more record array(ex. f3, f4... etc)
            }
        }
    }
    for (int o = 0; o < 4; o++)//number of frame + hit = 4, if frame is bigger than 3, for-loop number has to be changed 
    {
        switch (o)//Change record array to be print
        {
        case 0://f0 array
            printf("Frame %d ", o);
            arr = f0;
            break;
        case 1://f1 array
            printf("Frame %d ", o);
            arr = f1;
            break;
        case 2://f2 array
            printf("Frame %d ", o);
            arr = f2;
            break;
        //if frame is bigger then 3, case for more record array comes here
        default://hit array
            printf("        ");
            arr = h;
            isHit = 1;
            break;
        }
        for (int p = 0; p < r_len; p++)//Print frame & hit record arrays
        {
            if (*(arr + p) == -1)//if array[p] is empty
            {
                if(isHit){//if array is hit record array
                    printf("  ");//print blank space
                }
                else{//if array is frame record array
                    printf("E ");//print 'E'
                }
            }
            else//print values in array
            {
                printf("%d ", *(arr + p));
            }
        }
        printf("\n");
    }
    printf("\nHit %d", hit);//print number of hit
    printf("\nPage Fault %d", pf);//print number of page fault
    return 0;
}