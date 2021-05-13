ps -eu $USER | wc -l > pid.log
ps -eu $USER --format pid,cmd | awk '{print $1 ":" $2}' >> pid.log
