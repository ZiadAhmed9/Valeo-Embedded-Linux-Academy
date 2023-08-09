#!/bin/bash
#By Ziad Ahmed

############
# Method 1 #
############
#To list the wifi networks we use the iwlist command and also provide your wifi interface
#for example iwlist (wlan0 or wlan1) scan
#the above command lists everything about the networks but we only need name and strength
#we first store the networks in a variable
#like this output1=$(iwlist wlan0 scan)
#Then we can parse it by looping through the contents of the variable
#storing the contents of the $ESSID:Quality inside another variable
#and then increment the variable each time we input a new variable 
#incrementing acts like a /n 
#for example we can store the name like this
#if[[$line=~"ESSID:"]]; then
	#name=$(echo "$line" |cut -d '"') #since we know name will be inside ""
############
# Method 2 #################Better####################
############
#output=$(iwlist wlan0 scan | awk -F'[:=]' '/ESSID/{ssid=$2} /Quality/{print ssid ":" $2}')

#this method is intended to list all networks with their names in one line
#using more complex structures inside the command in which we don't even loop
#we extract names and strength using awk
#more information about awk can be found in my pdf
#we use piplining to acheive this
#So we the command above goes through the steps
#1)Get the list of the wifi networks nearby
#2)Use the characters ':' or '=' as a delimiter to differentiate between fields
#3)When you find the part "ESSID" take the field after delimiter using "$2" and store it in ssid
#4)Then when you find the part "Quality" append ":" and the second field after it 
#5)Doing this gives us Output= Network_name:Network_quality for all networks





output="W2:150
W3:75
W4:65
W5:55
:49
:30
WE2F1E55:27
we30:25"
#Now we need to parse this list into name and strength of signal

max_signal=0		#Variable to hold the maximum signal initalized with 0
best_network=""		#variable to hold the name of the network

#First we declare the internal field separator as the ":" in which 
#contents before the IFS are of another type from contents after it
#so we loop through the list by this while loop
while IFS=: read -r network signal; do 
#we loop and store the data before the : in network
#store the data after the : in signal
#We used -r as read command to treat the "/" as literal chars not a part of a path

    if [[ -n $network ]]; then	 			#Check if the signal name is empty or not for example like ""
        echo "Network: $network - Signal: $signal" 	#In this line we print the network names and strength

#in the following line we check if the signal of the network being examined is greater than the signal in the variable best_signal
        if [[ $signal -gt $max_signal ]]; then
            max_signal=$signal			 #if true store the signal here
            best_network=$network		 #and store the network name here
        fi
    fi
done <<< "$output" 	# In this line we tell the loop to use the list provided to us "OUTPUT"

if [[ -n $best_network ]]; then 	#If we obtained a working network
    echo "Recommended Network: $best_network"
else	#if no networks detected
    echo "Can't recommend any WIFI network"
fi

