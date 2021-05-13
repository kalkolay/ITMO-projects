touch temp
for pid in $(ps -eo pid)
do
if [[ -f /proc/$pid/status ]]
then
	sum_exec=$(grep -s se.sum_exec_runtime /proc/$pid/sched | awk '{print $3}')
	nr_switch=$(grep -s nr_switches /proc/$pid/sched | awk '{print $3}')
	echo 'ProcessID=' $pid' : Parent_ProcessID=' $(grep -s PPid /proc/$pid/status | grep -E -o '[0-9]+') ' : Average_Running_Time=' $(echo "scale=9; $sum_exec/$nr_switch" | bc -l) >> temp
fi
done
cat temp | sort -n -k5 > ans4
rm temp
