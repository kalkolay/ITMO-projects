pid=$$
num=1
mode="+"

(tail -f coolpipe) |
while true;
do
	read line;
	case $line in 
		"+")
			mode="+"
			echo "Switching to adding mode"
			;;
		"*")
			mode="*"
			echo "Switching to multiplying mode"
			;;
		[0-9]*)
			case $mode in
				"+")
					num=$(($num + $line))
					;;
				"*")
					num=$(($num * $line))
					;;
			esac
			echo $num
			;;
		"QUIT")
			echo "Quitting..."
			kill -9 $pid
			exit 0
			;;
		*)
			echo "Incorrect input"
			kill -p $pid
			exit 1
			;;
	esac
done
