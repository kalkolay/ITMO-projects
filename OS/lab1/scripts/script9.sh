echo "$(wc -l /var/log/*.log | awk '{if ($2 == "total") print $1}')"
