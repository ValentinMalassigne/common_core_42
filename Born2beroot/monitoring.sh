#!/bin/bash

# Linux kernel version, distribution, and architecture
arch=$(uname -a)

# physical processor core
cpup=$(grep "physical id" /proc/cpuinfo | wc -l)

# virtual processor
cpuv=$(grep "processor" /proc/cpuinfo | wc -l)

#ram usage, total, percentage
ram=$(free --mega | awk 'NR==2{printf "%s/%sMB (%.2f%%)", $3, $2, $3/$2*100 }')

#Disk usage, total, percentage
# DISK
disk_total=$(df -m | grep "/dev/" | grep -v "/boot" | awk '{disk_t += $2} END {printf ("%.1fGb\n"), disk_t/1024}')
disk_use=$(df -m | grep "/dev/" | grep -v "/boot" | awk '{disk_u += $3} END {print disk_u}')
disk_percent=$(df -m | grep "/dev/" | grep -v "/boot" | awk '{disk_u += $3} {disk_t+= $2} END {printf("%d"), disk_u/disk_t*100}')

#CPU usage
cpu=$(top -b -n1 | grep "Cpu(s)" | awk '{printf "%.2f%%\n", 100 - $8}')

# LAST BOOT
lb=$(who -b | awk '{print $3, $4}')

# LVM USE
lvmu=$(if [ $(lsblk | grep "lvm" | wc -l) -gt 0 ]; then echo yes; else echo no; fi)

#TCP Connections
tcpc=$(ss -ta | grep ESTAB | wc -l)

# USER LOG
ulog=$(who | wc -l)

# NETWORK
ip=$(hostname -I)
mac=$(ip link | awk '/link\/ether/ {print $2}')

# SUDO
cmnd=$(journalctl _COMM=sudo | grep COMMAND | wc -l)

wall "	Architecture: $arch
	CPU physical: $cpup
	vCPU: $cpuv
	Memory Usage: $ram
	Disk Usage: $disk_use/${disk_total} ($disk_percent%)
	CPU load: $cpu%
	Last boot: $lb
	LVM use: $lvmu
	Connections TCP: $tcpc ESTABLISHED
	User log: $ulog
	Network: IP $ip ($mac)
	Sudo: $cmnd cmd"