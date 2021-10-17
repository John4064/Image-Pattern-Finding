#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
//strcmp is main comparison tool
//John Parkhurst
//10/7/21

FILE *openF(char* arr){
    //@param: pointer to char array
    //Opens the file
    //return: none
    FILE *fptr;
    //REMEBER TO USE DOULBE QUOTES 
    fptr = fopen(arr,"r");
    if(fptr ==NULL){
        //Use put to not include null character
        puts("Error While Opening the File");
        fclose(fptr);
        exit(69);
    }else{
        return fptr;
    }
}
char *readF(FILE *fptr, int size){
    //@Param is a ptr to a file
    //Just parses through a file charachters
    //Return: a char array of pattern/image
    char* rArr = (char*) calloc(size, sizeof(char));
    char c;
    int count=0;
    //first line is already removed! calcdimen must come first
    while(1){
        c=fgetc(fptr);
        if(c==EOF){
            break;
        }else{
            if(c != '\n' && c!= ' '){
                rArr[count]= c;
                count++;
            }
        }
    }
    return rArr;
}
int *calcDimen(FILE *fil){
    // calculates dimension of file
    //@Param: Takes a ptr to a file(pattern of image)
    //return: integer array of height/width
    int* num = (int*) calloc(3, sizeof(int));
    char list[10];
    char trash;
    fgets(list,10,fil);
    sscanf(list,"%d%c%d",&num[0],&trash,&num[1]);
    return num;
}
char *findBloc(char* img,int width,int height,int xInd,int yInd){
    //@Param: pointer to char array of img, pointer to int array, the xindex of block(add y index)
    //xInd and yind reference the top left index of the "block"
    //this function gets the 3x3 
    //@return: char array of "block"
    char* ansArr = calloc(10, sizeof(char));;
    char tempA[10];
    int yPos=yInd*width;
    int count =0;
    int size =3;
    char* dance = "";
    //ypos is the 1,2,3 of the specific 3 block
    //xInd is the left most x index never xInd>width-3
    for(int i = 0; i<size;i++){
        for(int k = xInd; k<xInd+size;k++){
            //Assigns the variables in rows of size(patternsize)
            //printf("%c\n",img[yPos+k]);
            if(yPos+k>=strlen(img)){
                //The outter bounds exceds
                //printf("FAILURE: %d\n",xInd+size);
                return dance;
            }
            tempA[count] = img[yPos+k];
            //ypos+k is going longer the the img when I use calloc
            //and only when I calloc ansArr and blockArr
            //NO CLUE WHY math = ok otherwise
            count+=1;
        }
        yPos+=width;
    }
    //Copies the local array to our char array
    strcpy(ansArr,tempA);
    return ansArr;
}
int *process(char* pat,char* img,int width,int height){
    //@param: pattern charachter array, image character array, width and height of image
    //Return: void
    //Iterates through the image getting all
    //top left indexs of any possible 3x3 will never get too close 
    //boundaries
    int* cord = (int*) calloc(width*height, sizeof(int));
    int count = 0;
    for(int tempY = 0; tempY<=height-3;tempY++){
        for(int tempX = 0; tempX<=width-3;tempX++){
            //delete next line
            if(width!=20){
                char *blockArr;
                blockArr=findBloc(img,width,height,tempX,tempY);
                //Compare blockArr and pat
                int ans = strcmp(pat,blockArr);
                if(ans ==0){
                    //printf("%s\n%s\nThese match\n",blockArr,pat);
                    //printf("%d and %d\n",tempX,tempY);
                    cord[count]=tempY;
                    cord[count+1]=tempX;
                    printf("%d\n",cord[count]);
                    printf("%d\n",cord[count+1]);

                    count+=2;
                }
                free(blockArr);
            }
        }
    }
    //Checking if we found any results
    if(count>0){
        return cord;
    }else{
//        printf("No Matches\n");
        return NULL;
    }
    return cord;
}
int main(int argc, char const *argv[])
{
    //Pattern Dimensions
    int widthP,heightP,widthI,heightI=0;
    
    char* pVal = (char*) calloc(100, sizeof(char));
    char* iVal = (char*) calloc(100, sizeof(char));
    //Importing image path from script
    //Argv1 is the pattern file
    //argv2 is the image file
    //argv3 is the output directory
    for(int k = 0;k<strlen(argv[1]);k++){
        pVal[k]=argv[1][k];
    }
    for(int t = 0;t<strlen(argv[2]);t++){
        iVal[t]=argv[2][t];
    }
    //Opening pattern Files, Reading File, Putting into array
    FILE *pFil;
    FILE *iFil;
    pFil=openF(pVal);
    iFil=openF(iVal);
    if(pFil && iFil){
        //Gets the dimensions of the img/pat files
        int *dimenP;
        int *dimenI;
        dimenP = calcDimen(pFil);
        dimenI = calcDimen(iFil);
        widthP= dimenP[0];
        heightP= dimenP[1];
        widthI = dimenI[0];
        heightI = dimenI[1];
        free(dimenP);
        free(dimenI);
        //Creates Char Arrays for file contents
        char* pArr;
        char* iArr;
        //Reads the Pattern/Image File!
        pArr=readF(pFil,(heightP*widthP));
        iArr=readF(iFil,(500));
        //Process The Two Files
        int *ans;
        //Answers are here
        ans=process(pArr,iArr,widthI,heightI);

        if(ans != NULL){
            //for(int j = 0;j<(sizeof(ans)/sizeof(ans[0]));j++){
              //  printf("%d ",ans[j]);
            //}
            //If it exists
            //output
            //image Name
            char imageName[50];
            int subInd=14;
            while(subInd<strlen(argv[2])){
                imageName[subInd-14]=argv[2][subInd];
                subInd++;
            }
            printf("%s\n",imageName);
            int counter=0;
            while (ans[counter]!= NULL){
                //printf("%d ",ans[counter]);
                counter++;
            }
            free(ans);
        }

        fclose(pFil);
        fclose(iFil);
        //Cleanup
        free(iArr);
        free(iVal);
        free(pVal);
        free(pArr);
    }else{
        
        return 3;
    }

    //End
    return 0;
    }
    /*
            //Combines imagepath and file name then opens file
            //Then resets newdir to imagepath
            strcat(newdir,entry->d_name);
            FILE *tempF;
            if(tempF){
                tempF = openF(newdir);
                //int* dimenI = (int*) calloc(3,sizeof(int));
                //int* dimenI;
                //dimenI = calcDimen(tempF);
                //free(dimenI);
                //char* imgArr = (char*) calloc((dimenI[0]*dimenI[1]),sizeof(char));
                char* imgArr;
                //readF cause dimenI to have wonky values on 20-15
                //Keep lookout for next line issues if bug occurs
                imgArr= readF(tempF,100);
                if(imgArr){
                    //process(pArr,imgArr,dimenI);
                    printf("KACHIGGA\n");
                    free(imgArr);
                }  
                //HERE WE EXECUTE pattern vs image checks
                strcpy(newdir,imageP);
                fclose(tempF);
            }
            //Create struct of image pass that
            
            //dimenI        

        }
        */