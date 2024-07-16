#/bin/bash
ps aux | grep  'systemd'
$pidof systemd
ps -ef | grep 2216
