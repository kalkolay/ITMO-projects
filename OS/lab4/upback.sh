#!/bin/bash

if [[ -d "/home/user/restore" ]]
then
	rmdir "/home/user/restore"
fi
mkdir "/home/user/restore"


backup_prev=$(ls /home/user | grep -E "^Backup-" | sort -n | tail -1)

if [[ -z "$backup_prev" ]]
then
	echo "There is no files to restore"
	exit 1
fi

for line in $( ls "/home/user/$backup_prev" | grep -Ev "\-[0-9]{4}-[0-9]{2}-[0-9]{2}$" )
do
	cp "/home/user/$backup_prev/$line" "/home/user/restore/$line"
done
