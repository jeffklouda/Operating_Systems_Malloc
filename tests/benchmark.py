import subprocess
import sys
import time

if len(sys.argv) < 1:
    print "Please include test program as argument"
    sys.exit

args = sys.argv[1:len(sys.argv)]
commands = []
fitTypes = []
commands.append("env LD_PRELOAD=lib/libmalloc-ff.so")
commands.append("env LD_PRELOAD=lib/libmalloc-nf.so")
commands.append("env LD_PRELOAD=lib/libmalloc-bf.so")
commands.append("env LD_PRELOAD=lib/libmalloc-wf.so")
fitTypes.append("First fit");
fitTypes.append("Next fit");
fitTypes.append("Best fit");
fitTypes.append("Worst fit");

for arg in args:
    commands[:] = [command + " " + arg for command in commands]

for command, fitType in zip(commands, fitTypes): 
    millis = float(time.time() * 1000)
    process = subprocess.Popen(command.split(), stdout=subprocess.PIPE)
    output, error = process.communicate()
    print fitType + ':'
    print output
    print str(float(time.time() * 1000) - millis) + " :Milliseconds"

