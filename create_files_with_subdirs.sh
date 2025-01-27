#echo "Hello World"

#Step 1: Create directory with the current date and time
currentDate=$(date +"%Y-%m-%d-%H-%M-%S")

#create directory 
mkdir "$currentDate"

#array with programming langauges
proLang=("Java" "Python" "C#" "Fortan" "Ruby" "C++" "Javascript" "Rust" "Assembly" "C")

#Step 2: Create 10 subdirectories named file101-file110
echo -e "Create file directories and include the textfiles with text files with their own programming language."
for i in {101..110}; do

    mkdir "$currentDate"/"file$i"

    fileNum=$((i + 400))

    touch "tuser$fileNum.txt"

    #Variable access the elements in the array
    arrIndex=$((i - 101))

    #access the things in the array to write to file
    echo ${proLang[$arrIndex]} > "tuser$fileNum.txt"

    #Move the file to folder
    mv "tuser$fileNum.txt" "$currentDate"/"file$i"

    echo "tuser$fileNum.txt created within file$i"
done

#Step 3: Add executing permission
chmod +x create_files_with_subdirs.sh
