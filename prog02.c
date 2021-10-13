#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
//strcmp is main comparison tool
//John Parkhurst
//10/7/21
//Set to positive integer to print and flush counters(WIP)
#define DEBUG_OUTPUT	0
//Structures
typedef struct block
{
    //This structure are all the pattern size blocks 
    //That we check
	char* blocArr;
	int x;
    int y;
} block;


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
        exit(69);
    }else{
        return fptr;
    }
}
char *readF(FILE *fptr){
    //@Param is a ptr to a file
    //Just parses through a file charachters
    //Return: a char array of pattern/image
    char* rArr = (char*) calloc(100, sizeof(char));
    char c;
    printf("%c",c);
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
    fgets(list,60,fil);
    sscanf(list,"%d%c%d",&num[0],&trash,&num[1]);
    return num;
}
char *findBloc(char* img,int* dimenI,int xInd,int yInd){
    /*@Param: pointer to char array of img, pointer to int array, the xindex of block(add y index)
      @return: char array of "block"
    */
    char* ansArr;
    char tempA[10];
    int yPos=yInd*dimenI[0];
    int count =0;
    int size =3;
    //ypos is the 1,2,3 of the specific 3 block
    //xInd is the left most x index never xInd>width-3
    for(int i = 0; i<size;i++){
        for(int k = xInd; k<xInd+size;k++){
            //Assigns the variables in rows of size(patternsize)
            tempA[count] = img[yPos+k];
            count+=1;
        }
        yPos+=dimenI[0];
    }
    strcpy(ansArr,tempA);
    return ansArr;
}
void process(char* pat,char* img, int* dimenP, int* dimenI){
    //@param: pattern charachter array, image character array, integer array of pattern height/width, integer array of image height/width
    // Meat
    //Return: void
    //0 is width 1 is height
    int patS = dimenP[0]*dimenP[1];
    int imageS = dimenI[0]*dimenI[1];
    char *blockArr;
    //int tempY=0;
    //printf("%s\n",img);
    for(int tempY = 0; tempY<=dimenI[1]-3;tempY++){
        for(int tempX = 0; tempX<=dimenI[0]-3;tempX++){
            if(dimenI[0]==12){
                blockArr=findBloc(img,dimenI,tempX,tempY);
                //Compare blockArr and pat
                
                printf("%d",strcmp("abc","bcd"));
            }
        }
    }
    printf("The End of the Image\n");
    return;
}
int main(int argc, char const *argv[])
{
    //Pattern Dimensions
    int widthP=0;
    int heightP=0;
    //image path
    const char *imageP = argv[2];

    char* val = (char*) calloc(100, sizeof(char));
    //Importing image path from script
    //Argv1 is the pattern
    //argv2 is the image directories
    //argv3 is the output directory
    for(int k = 0;k<strlen(argv[1]);k++){
        val[k]=argv[1][k];
    }
    //Opening pattern Files, Reading File, Putting into array
    FILE *fil;
    fil=openF(val);
    //Reads Dimensions of Pattern
    int *dimenP;
    dimenP = calcDimen(fil);
    widthP= dimenP[0];
    heightP= dimenP[1];
    char* pArr = (char*) calloc((
        heightP*widthP),sizeof(char));

    //Reads the Pattern File!
    pArr=readF(fil);
    //Declaration of image Variables
    FILE *tempF;
    DIR *imagesD;
    struct dirent *entry;
    imagesD = opendir(argv[2]);
    char newdir[100];
    strcpy(newdir,imageP);
    while( (entry=readdir(imagesD))){
        if (entry->d_name[0] == '.'){
            //This just skips the parents and child directories!
            continue;
        }
        //Combines imagepath and file name then opens file
        //Then resets newdir to imagepath
        strcat(newdir,entry->d_name);
        tempF = openF(newdir);
        int* dimenI = (int*) calloc(3,sizeof(int));
        dimenI = calcDimen(tempF);
        char* imgArr = (char*) calloc((dimenI[0]*dimenI[1]),sizeof(char));
        //readF cause dimenI to have wonky values on 20-15
        //Keep lookout for next line issues if bug occurs
        imgArr= readF(tempF);        
        //HERE WE EXECUTE pattern vs image checks
        strcpy(newdir,imageP);
        //Create struct of image pass that
        process(pArr,imgArr,dimenP,dimenI);
        free(imgArr);
        free(dimenI);
    }
    //Cleanup
    fclose(tempF);
    closedir(imagesD);
    fclose(fil);
    free(dimenP);
    free(pArr);
    free(val);
    return 0;
}
