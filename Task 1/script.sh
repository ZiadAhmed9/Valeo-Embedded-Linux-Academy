#In this script I will be using the bash scripting to copy multiple files to a destination
#Files must be in my current directory where I'm at in the terminal else won't work
#example of command to use this script: ./script.sh text1.txt text2.txt /path/to/destination
########################################################################################

if [ "$#" -lt 2 ]; then	# I used this condition to check the number of arguments is at least 2
    echo "Arguments are less than 2"
    exit 1
fi

# Now we made sure the arguments are 2 or more
des="${@: -1}" #Knowing the last arguments is the destination I will store it here
if [ ! -d "$des" ]; then #if this destination doesn't exist we create it
    mkdir -p "$des" 	#line where we create the directory needed
fi

for ((i=1;i<$#;i++)); do 	#loop through the arguments where $# means number of arguments
    file="${!i}" 		#variable to store file name for each iteration through arguments
    if [ -f "$file" ]; then	# if file is a type file lue .txt or .sh tgeb proceed
        cp "$file" "$des" 	#copy the file to the destination
    else
        echo "This file "$file" is not valid "
    fi
done
echo "Operation successful"

