# mona-timing-lib

Tools for timing attacks.

## Preconditions

- Have at least [Python 2.7](http://python.org/download/releases/2.7.2/)
  installed (older versions might work, but haven't been tested). For other
  Python versions, please change the `Makefile`.
- Have [SWIG](http://www.swig.org/download.html) installed. Read more about
  *SWIG* [here](http://www.swig.org/exec.html).
- The `python-dev` package is required to build the Python module from
  `fau_timer.c`.

## Installation

Clone this repository and open a terminal.

Unix:

```bash
$ make linux
```

Mac OS X:

```bash
$ make osx
```

## Usage

```bash
$ python runme.py
```

Look at `runme.py` to learn about the usage of the library.

## Configuration

Disable Intel Speedstep in your machine's BIOS or use the `cpufreq` utilities.

Beside the frequency of your CPU, there are some "sleep-states" [c-states][1] to
save power. The clock is stopped for a short period of time if the CPU is idle.
Consequently, CPU ticks have different time durations.

On Ubuntu Linux machines, you can disable this feature by adding `idle=poll` to
the kernel parameters.

[1]: http://www.hardwaresecrets.com/article/Everything-You-Need-to-Know-About-the-CPU-C-States-Power-Saving-Modes/611/1

## Bugs
The ```get_response()``` function is not binary safe so it will return the content of the response up to the first NULL byte. This is related to SWIG. If you want to receive binary responses from Python, you can just read the file ```response.dat```, which always contains the most recent response.
If you are a SWIG wizard who knows how to pass binary data from C land to Python land, please get in touch.
