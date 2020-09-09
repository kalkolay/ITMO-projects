while [[ 1 ]]; do
	echo -e "\e[36m\e[1m
 ------------------- 
|       MENU:       |
|  1 - open vi      |
|  2 - open nano    |
|  3 - open links   |
|  4 - exit         |
 -------------------\e[0m"

	read menu_item

	case "$menu_item" in 
		1 ) vi ;;
		2 ) nano ;;
		3 ) links ;;
		4 ) exit 0 ;;
		* ) echo -e "\033[31mError:\e[0m Incorrect number typed"
	esac
done
