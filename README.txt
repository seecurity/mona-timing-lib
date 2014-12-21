README for building fau_timer python module

Preconditions
=======================================
- have at least python 2.7 installed (maybe older, but not tested. for other verisons please change line in makefile)
	get it here: http://python.org/download/releases/2.7.2/
- have swig installed (http://www.swig.org/exec.html)
	get swig here: http://www.swig.org/download.html
- python-dev is required to build a python module from fau_timer.c


How to build Python module of fau_timer.c
=======================================
On UNIX machines:
	$ make linux

On MAC OSX machines:
	$ make osx

How to use the Python module
=======================================
        $ python runme.py

Look at runme.py to learn about the usage of the library.

How to configure your measurement machine
=======================================
Disable Intel Speedstep in your machine's BIOS or using the cpufreq utilities.

Beside the frequency of your CPU, there are some "sleep-states" c-states[1] to save power. The clock
is stopped for a short time if the CPU is idle. Consequently, CPU ticks has different time
durations.

On Ubuntu Linux machines, you can disable this feature by adding "idle=poll" to my kernel parameters.
[1] http://www.hardwaresecrets.com/article/Everything-You-Need-to-Know-About-the-CPU-C-States-Power-Saving-Modes/611/1
