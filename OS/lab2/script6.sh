result=0
for pid in $(ps -eo pid)
do
	curSize=$(grep -s VmSize /proc/$pid/status | grep -E -o '[0-9]+')
	if [[ $curSize -ge $result ]]
	then
		result=$curSize
	fi
done
echo $result
