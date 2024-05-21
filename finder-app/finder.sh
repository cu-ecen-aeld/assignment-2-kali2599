#! /bin/bash
check_string_iterative() {
    local filename="$1"
    local string_search="$2"
    if [ -f "$filename" ] ; then
        if grep -q "$string_search" "$filename" ; then
            ((x++))
            y=$((y + "$(grep  $searchstr $filename | wc -l )"))
        fi
    elif [ -d "$filename" ] ; then
        echo "Checking in dir: $filename "
        for subdir in "$filename"/*
        do
            check_string_iterative "$subdir" "$string_search"
        done
    else 
        echo "File $filename is no a file or a directory"
    fi
}


if [ $# -ne 2 ] ; then 
    echo "Bad usage!"
    echo "Usage: ./finder.sh <DIRECTORY_PATH> <STRING_TO_SEARCH>"
    exit 1
else
    filesdir="$1"
    searchstr="$2"
    if [ ! -d "$filesdir" ] ; then 
        echo "The path $filesdir is not an existing directory."
        exit 1
    fi
fi
x=0
y=0
echo "Checking in dir: $filesdir "
for filename in "$filesdir"/*
do
    if [ -d "$filename" ] ; then
        check_string_iterative "$filename" "$searchstr"
    else
        if grep -q "$searchstr" "$filename" ; then
            ((x++))
            y=$((y + "$(grep  $searchstr $filename | wc -l )"))
        fi
    fi
done
echo "--------------------------"
echo "RESULTS:"
echo "The number of files are $x and the number of matching lines are $y"