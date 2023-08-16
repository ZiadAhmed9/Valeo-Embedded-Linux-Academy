by: Ziad Ahmed Ibrahim

In this task I was required to create a service that runs daily at 2 AM and backup a directory into another directory with all info about it. it should start on boot

### 2 Methods I found:
1) Using the cronjob to automate a script without systemd
2) Using service and a timer for the service using systemd

### Why systemd is better
1) they are services with timer events and are carefully logged in systemd journal
2) easier debugging
3) Can be enabled and disabled easily
4) Status can be checked easily
5) Delays can be set between execution

### How I used it
#### 1) The backup.service file
```bash
[Unit]
Description=Daily Backup Service

[Service]
Type=oneshot
ExecStart=/home/msi/data_backup.sh

[Install]
WantedBy=multi-user.target
```
Description: 
- This .service file is created in etc/systemd/system directory 
- We pass to the service the path of the .sh file to be executed when the service is starts(trigger happens)
- `Type=oneshot` part is not mandatory and can be removed, this line ensures that other services depending on this service will start after this one is finished
- ExecStart part is where the path of the script is provided

#### The backup.timer file
```bash
[Unit]
Description= timer for backup

[Timer]
OnCalendar=*-*-* 02:00:00
Unit=backup.service
Persistent=True

[Install]
WantedBy=multi-user.target
```
Description
- the OnCalendar part is the part where we tell the timer to trigger event for the service everyday at 2 Am
- Unit is the unit to run after the trigger
- Persistent part means that in case of reboot or restart the process will continue after booting process 

#### Script made
```bash
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
```
- Ensured timestamps, permissions are all passed to the backup
- rsync installed 
- using minutes and hours won't be mandatory in our script as we know it will execute everyday at 2 AM but to make sure the service runs correctly I added it

### How I tested my service
#### 1) Testing the timer
- Instead of triggering everyday at 2 AM, the service is to be triggered every 5 seconds
- To activate a service every 5 Seconds add this instead of  the OnCalendar
```bash
[Timer]
	OnActiveSec=5 
	OnUnitActiveSec=5
```
- every 5 seconds a script is called that will echo anything to another file and we check it every 5 seconds
#### 2) Testing the script
- After I made sure the timer works and the service is called correctly
- I made wrote a script that will backup a directory in another directory and tested it by executing it manually with terminal
- another approach is given to allow the timestamp signature in the name of the folder of the backed up folder
- an algorithm is implemented to only keep the latest 5 and delete the oldest one from the 6
- My script was tested by executing the back up service every 5 seconds 
- after I changed the timer back to trigger every day at 2 AM
![[Pasted image 20230805183628.png]]
*This screenshot was taken during testing the script before fully completing it*
### Conclusion:
In essence, we conclude that linux offers a really helpful environment to create scripts that helps developers do tasks they want and test them effectively. Linux also offers a very easy to use scripting tools, and above all Linux is an open source in which many developers posting on forums tutorials and guides on how to use Linux terminal and how to write good scripts. 
![[Pasted image 20230805183614.png]]
*Final result*

### Sources
*press on the hyper link*
[rsync Guide](https://linux.die.net/man/1/rsync)
[Cron guide](https://www.looklinux.com/run-cron-every-5-seconds/#How_do_I_run_a_cron_job_every_second)
[Creating new systemd service](https://www.makeuseof.com/create-systemd-service-on-linux/)
[Cron vs systemd](https://unix.stackexchange.com/questions/278564/cron-vs-systemd-timers)
[Services commands guide](https://phoenixnap.com/kb/start-stop-restart-linux-services)

