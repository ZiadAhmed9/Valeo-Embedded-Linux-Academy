#!/bin/bash
timestamp=$(date +%Y-%m-%d_%H-%M-%S)	#this line takes the time stamp at the running time of this script and stores it in this variable
source="/home/msi/Important"	#a variable that holds the source file that we need to backup
backup_dir="/home/msi/backup_folder" # a variable that hold the directory of the back up destination
backup_dest="$backup_dir/backup_$timestamp" #in this line i combine both the directory and the file of the back up with timestamp in it
mkdir -p "$backup_dest"	#create a directory with the name and destination in the variable above
rsync -a "$source" "$backup_dest"  #using rsync we take copy of the directory stored in the variable "Source" in to "backup_dest"

#in next line we List the files then sort them in descending order, then get the last 6 elements with tail command, loop through them until you reach the last one, after the loop ends you delete the last file and keep the other 5 which will be the latest versions
ls -1 "$backup_dir" | sort -r | tail -n +6 | while read -r file; do 
	rm -r "$backup_dir/$file" 
done



