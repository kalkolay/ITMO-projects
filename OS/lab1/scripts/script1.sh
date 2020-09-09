for (( i=0; i < 2; ++i )) do
	if [[ $1 -lt $2 ]]; then
		shift
	else
		set $1 $3
	fi
done

echo $1
