/*
File Name: myLRU.c
Developed by Jin1751 (github.com/Jin1751)
This code implements one of Page Replacement Algorithm in OS (LRU)
*/

#include <stdio.h>

int main(){
    int r_len, reference[50], f_len, frame[20], n_frequancy[20];
    int index = 1, pf = 0, max_index = 0, is_same = 0, hit = 0;
    int f0[20], f1[20], f2[20], h[20];// array f0, f1, f2 is to record each index of frame array, Need more arrays if frame is bigger than 3
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

    for (int i = 0; i < f_len; i++)
    {
        frame[i] = -1;
    }//Initialize frame array to -1 (To check frame is empty)
    printf("\n");

    for (int i = 0; i < r_len; i++)
    {
        is_same = 0;
        for (int j = 0; j < index; j++)
        {
            if (frame[j] != reference[i])//If frame[j] is not current process
            {
                n_frequancy[j]++;//Increase non-usage number of frame[j]
            }
            else//If frame[j] is current process
            {
                n_frequancy[j] = 0;//Reset non-usage number of frame[j]
                is_same = 1;
                hit++;//increase 1 hit
                f0[i] = frame[0];//array 'f0' is to print which processes were in frame 0, Initialize f0[i]  to frame[0]
                f1[i] = frame[1];//array 'f1' is to print which processes were in frame 1, Initialize f1[i]  to frame[1]
                f2[i] = frame[2];//array 'f2' is to print which processes were in frame 2, Initialize f2[i]  to frame[2]
                //if frame is bigger than 3, Initialize more record array(ex. f3, f4... etc)
                h[i] = 1;//array 'h' is to print when hit ocurred, initialize 1 to h[i]
            }
        }
        if (!is_same)//If current process is not in the frame array
        {
            if (index < f_len + 1)//If frame array has empty index
            {
                frame[index - 1] = reference[i];//put processe in frame array
                n_frequancy[index - 1] = 0;//set process non-usage number 0
                pf++;//increase page fault 
                index++;
                is_same = 0;
                f0[i] = frame[0];//array 'f0' is to print which processes were in frame 0, Initialize f0[i]  to frame[0]
                f1[i] = frame[1];//array 'f1' is to print which processes were in frame 1, Initialize f1[i]  to frame[1]
                f2[i] = frame[2];//array 'f2' is to print which processes were in frame 2, Initialize f2[i]  to frame[2]
                //if frame is bigger than 3, Initialize more record array(ex. f3, f4... etc)
            }
            else//If frame array has full
            {
                for (int l = 0; l < f_len; l++)//find index of most unused process in frame array
                {
                    for (int m = 0; m < f_len; m++)
                    {
                        if (n_frequancy[max_index] < n_frequancy[m])
                        {
                            max_index = m;
                        }
                    }
                }
                frame[max_index] = reference[i];//change most unused process to current process
                n_frequancy[max_index] = 0;//set process non-usage number 0
                pf++;
                is_same = 0;
                max_index = 0;
                f0[i] = frame[0];//array 'f0' is to print which processes were in frame 0, Initialize f0[i]  to frame[0]
                f1[i] = frame[1];//array 'f1' is to print which processes were in frame 1, Initialize f1[i]  to frame[1]
                f2[i] = frame[2];//array 'f2' is to print which processes were in frame 2, Initialize f2[i]  to frame[2]
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