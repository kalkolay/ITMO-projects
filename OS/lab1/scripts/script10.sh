man bash | grep -io "[[:alnum:]]\{4,\}" | tr "[:upper:]" "[:lower:]" | sort | uniq -c | sort -nr | head -3
