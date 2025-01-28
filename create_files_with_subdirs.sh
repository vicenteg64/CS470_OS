#Step 1: Create directory with the current date and time
currentDate=$(date +"%Y-%m-%d-%H:%M:%S")

#Create main directory 
mkdir "$currentDate"

#Array with programming langauges
proLang=("Java" "Python" "C#" "Fortan" "Ruby" "C++" "Javascript" "Rust" "Assembly" "C")

#Step 2: Create 10 subdirectories named file101-file110
echo -e "Create file directories and include the textfiles with text files with their own programming language..."
for i in {101..110}; do

    mkdir "$currentDate"/"file$i"

    #Variable to give the text files the correct number
    fileNum=$((i + 400))

    touch "tuser$fileNum.txt"

    #Variable access the elements in the array
    arrIndex=$((i - 101))

    #Access the text file created and add the elements in the proLang array
    echo ${proLang[$arrIndex]} > "tuser$fileNum.txt"

    #Move the file to folder
    mv "tuser$fileNum.txt" "$currentDate"/"file$i"
done
echo "Subdirectories and text files created."

#Step 3: Add executing permission
echo "Giving executing premission..."
chmod +x create_files_with_subdirs.sh
