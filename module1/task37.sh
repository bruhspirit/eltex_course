#!/bin/bash

# Чтение параметров из конфигурационного файла
source ./config.sh

logfile="/var/log/$process_name.log"

{ cat "${logfile}" | sed -r 's/^(..)\.(..)\.(....)/\3.\2.\1/'; \
echo "${start_time}"; echo "${end_time}"; } | sort | \
sed "1,/^${start_time}\$/d;/^${end_time}\$/,\$d"