if [[ $PWD == "$HOME" ]]; then
	echo $HOME
	exit 0
else
	echo -e "\033[31mError:\e[0m Current path isn't the home directory"
	exit 1
fi
