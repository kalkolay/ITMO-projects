cur="$(date | tr " " "_")"
mkdir ~/test && {
	echo "catalog test was created successfully" > ~/report
	echo "" > ~/test/"$cur"
}
ping www.net_nikogo.ru || echo "$(date) [ERROR] : www.net_nikogo.ru is not responding" >> ~/report
