nice -n 9 ./loop.sh & pid1=$!
nice -n 5 ./loop.sh & pid2=$!
nice -n 0 ./loop.sh & pid3=$!

at now + 2 minute <<< "kill ${pid1} ; kill ${pid2} ; kill ${pid3}"
