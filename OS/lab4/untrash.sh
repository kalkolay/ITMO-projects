#!/bin/bash


dir="$HOME/.trash"
dir_log="$HOME/.trash.log"
if [[ $# -ne 1 ]]
then
	echo "Incorrect number of arguments. Had to be 1."
	exit 1
fi

if [[ ! -d $dir ]]
then
	echo "$dir: No such directory exists"
	exit 1
fi

if [[ ! -e $dir_log ]]
then
	echo "File trash.log doesn't exist"
	exit 1
fi

if [[ $(grep -E "$1 " "$dir_log") == "" ]]
then
	echo "Can't find $1 in trash.log"
	exit 1
fi

if [[ $(grep -E "/$1 " "$dir_log") == "" ]]
then
	echo "Type only name of the file, not full path"
	exit 1
fi

###########################
echo "$(grep -E "/$1" $dir_log)"|
while read line;
do
	file_path=$(echo "$line" | awk '{print $1}')
	file_reference=$(echo "$line" | awk '{print $2}')
	read -p "Restore $file_path (y/n)?" answer <&1
    
	case $answer in
		"" | "Y" | "y")
			way=$(echo "$file_path" | awk -F"/$1" '{print $1}')
			if [[ ! -d $way ]]
			then
				echo "Directory $way doesn't exist anymore, file will be restored in $HOME"
				if [[ -f $file_path ]]
				then
					read -p "File $file_path exists in directory, choose different name: " new_name <&1
					ln -s "$file_reference" "$HOME/$new_name"
					rm "$file_reference"
				else
					ln -s "$file_reference" "$HOME/$1"
					rm "$file_reference"
				fi
			else
				if [[ -f $file_path ]]
				then
					read -p "File $file_path exists in directory, choose different name: " new_name <&1
					ln -s "$file_reference" "$way/$new_name"
					rm "$file_reference"
				else
					ln -s "$file_reference" "$way/$1"
					rm "$file_reference"
				fi
			fi
				grep -Ev  "$file_reference$" "$dir_log" > .untrash_tmp.log
				cat .untrash_tmp.log > "$dir_log"
				rm .untrash_tmp.log
			;;
		*)
			continue
			;;
	esac
done
