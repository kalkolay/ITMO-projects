ps ax | grep "/sbin/" | awk '{print $1}' > pid.log
