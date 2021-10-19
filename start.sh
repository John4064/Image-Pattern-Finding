#John Parkhurst
#Script Execution 
#bash start.sh prog02.c ./Data/Images/ ./Data/Patterns/

if test -e $1
then
    gcc $1 -o prog02

fi
#ERROR HANDLING CHECKING VALID DIRECTORY
if test ! -d $3
then
    echo "Error In Pattern Directory"
    exit 2
elif test ! -d $2
then
    echo "Error in Images Directory"
    exit 3
fi
#Pattern Directory
PAT=$3
IMG=$2
#Pattern Images importing
#Iterates through Files of .pat
count=0
#CREATING COPY DIRECTORY
mkdir ${PAT}copy
 for f in $PAT*.pat;
    do
        ((count++))
        echo -n "" > ${PAT}copy/patternC${count}.pat
        #This copies the original file to the copy directory
        #Where as echo -n creates an empty directory
        #cp $f ${PAT}copy/patternC${count}.pat
        
        
    done
count=0
#This loop goes through the patterns and writes line by line
#To the copy a unix version of the file!
for g in ${PAT}*.pat
    do
        #Iterates through each line of File
        ((count++))
        while read p; do
            #This here reads the line and replaces instances of \r with \n
            echo "$p" | tr -d '\r' >> ${PAT}copy/patternC${count}.pat
        done <$g
    done
count=0
#Replaces all the originals with the new files
for x in ${PAT}*.pat
    do
        ((count++))
        cp ${PAT}copy/patternC${count}.pat $x

    done

rm -r ${PAT}copy
#$2 Directory for Images $3 Directory of pattern files $4 output
if test -x prog02
    then
        #This executes the c script for every modified 
        #Pattern File
        #MAKE THIS RUN CONCURRENTLY
        for p in ${PAT}*.pat
        do
            for i in ${IMG}*.img
            do
                ./prog02 $p $i
            done
        done
    fi