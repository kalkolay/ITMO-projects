cat /var/log/anaconda/syslog | awk '$2 = "INFO"' > $HOME/os_labs/lab1/files/info.log
