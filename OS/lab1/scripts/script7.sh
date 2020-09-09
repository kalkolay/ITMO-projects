grep -roshE --binary-files=text "[[:alnum:]_.]+@[[:alnum:]_]+(\.[[:alpha:]]+)+" /etc/ | sort -u | tr -s '\n' ", " | sed '$ s/.$//' > $HOME/os_labs/lab1/files/emails.lst
