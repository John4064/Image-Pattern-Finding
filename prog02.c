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
void process(char* pat,char* img, int* dimenP, int* dimenI){
    //@param: pattern charachter array, image character array, integer array of pattern height/width, integer array of image height/width
    // Meat
    //Return: void
    //0 is width 1 is height
    int patS = dimenP[0]*dimenP[1];
    int imageS = dimenI[0]*dimenI[1];
    int tempX=0;
    int tempY=0;
    //printf("%s\n",img);
    //char* tempStr = (char*) calloc(100, sizeof(char));
    //Math on this is so fucked
    int a=0;
    //We can get the top third corner
    //now need to increment every single 3
    for(int i = 0; i<3+a;i++){
        for(int k = 0; k<3;k++){
            printf("%c",img[tempX+k]);
        }
        printf("\n");
        tempX+=dimenI[0];
    }
    printf("The End\n");
    
    /*
    if(a!=0){
            if(i==a+3 && a <=dimenI[1]){
            a+=3;
            }
        }else{
            if(i==a+2 && a <=dimenI[1]){
            a+=3;
            }
        }
    */

    //printf("%d and %d\n",dimenP[0],dimenP[1]);
    //free(tempStr);
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
