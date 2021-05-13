info_msg="$(cat /var/log/anaconda/X.log | awk '$3 = "(II)"{print $0}')"
warn_msg="$(cat /var/log/anaconda/X.log | awk '$3 = "(WW)"{print $0}')"

echo "${warn_msg//"(WW)"/"Warning: "}" > $HOME/os_labs/lab1/files/full.log
echo "${info_msg//"(II)"/"Information: "}" >> $HOME/os_labs/lab1/files/full.log

cat $HOME/os_labs/lab1/files/full.log
