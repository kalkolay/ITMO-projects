while [[ $str != "q" ]]; do
	str_sum=$str_sum$str
	read str
done

echo $str_sum

