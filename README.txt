=========
.First, change Makfile_xxxx_xxxx_x to suitable .c file , then execute belw command to compile and install module
------
Compile method:
   make 
Insert module:
  sudo insmod register.ko
Check device:  
  cat /proc/bus/input/devices
Remove module:
 sudo rmmod register.ko        
-----

After insert aaaabbbb.ko module, your linux host command mode will show aaaabbbb every 4 seconds.
After insert sequares.ko module, your linux mouse cursor will automatic move seqares. 
