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
    char* arr = (char*) calloc(100, sizeof(char));
    char c;
    printf("%c",c);
    int count=0;
    //first line is special
    char num[10];
    fgets(num,60,fptr);
    printf("%s",num);
    while(1){
        c=fgetc(fptr);
        if(c==EOF){
            break;
        }else{
            if(c != '\n' && c!= ' '){
                arr[count]= c;
                count++;
            }
        }
    }
    return arr;
}

int main(int argc, char const *argv[])
{
    int width,height;
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
    char* fArr = (char*) calloc((3*3),sizeof(char));
    //Reads pattern File
    fArr=readF(fil);
    char temp = fArr[0];
    printf("%s\n",fArr);


    //Declaration of image Variables
    FILE *tempF;
    DIR *imagesD;
    struct dirent *entry;
    imagesD = opendir(argv[2]);
    char newdir[100];
    strcpy(newdir,imageP);
    char* imgArr = (char*) calloc(250,sizeof(char));

    while( (entry=readdir(imagesD))){
        if (entry->d_name[0] == '.'){
            //This just skips the parents and child directories!
            continue;
        }
        //Combines imagepath and file name then opens file
        //Then resets newdir to imagepath
        strcat(newdir,entry->d_name);
        tempF = openF(newdir);
        imgArr= readF(tempF);
        //HERE WE EXECUTE pattern vs image checks


        strcpy(newdir,imageP);
    }


    //Cleanup
    fclose(tempF);
    closedir(imagesD);
    fclose(fil);
    free(fArr);
    free(val);
    return 0;
}
