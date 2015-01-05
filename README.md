register
========

Kernel 3.2 register.c sample code for [The Linux USB Input Subsystem, Part I]


Compile:
   make 
Insert module:
  sudo insmod register.ko
Check device:  
  cat /proc/bus/input/devices
Remove module:
 sudo rmmod register.ko        
