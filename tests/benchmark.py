import subprocess
import sys

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
    process = subprocess.Popen(command.split(), stdout=subprocess.PIPE)
    output, error = process.communicate()
    print fitType + ':'
    print output

