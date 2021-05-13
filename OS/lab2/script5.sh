avr=0
count=0
lastId=0
while read line
do
parent=$(echo $line | grep -E -o 'Parent_ProcessID= [0-9]+' | grep -E -o '[0-9]+')
if [[ $parent -gt $lastId ]]
then
	result=$(echo "scale=9; $avr/$count" | bc -l)
	echo "Average_Sleeping_Childer_of_ParentID=" $lastId " is " $result >> ans5
	count=0
	avr=0
	lastId=$parent
fi
avr=$(echo "$avr+$(echo $line | grep -E -o 'Average_Running_Time= [0-9.]+' | grep -E -o '[0-9.]+')" | bc -l) 
let count=$count+1
echo $line >> ans5
done < ans4
result=$(echo "scale=9; $avr/$count" | bc -l)
echo "Average_Sleeping_Childer_of_ParentID=" $lastId " is " $result >> ans5
