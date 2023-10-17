
import matplotlib.pyplot as plt
import csv
import os.path
import sys

if "-h" in sys.argv:
    print("plot.py <input-file-csv> <output-graph>")
    exit(0)

args = [arg for arg in sys.argv[1:] if not arg.startswith("-")]

if len(args) == 0:
    print("Missing input and output file path")
    exit(1)

if len(args) == 1:
    print("Missing output file path")
    exit(1)

file_path = args[0]
out_path = args[1]


if not os.path.isfile(file_path):
    print(f'File "{file_path}" doesn\'t exist or isn\'t a file')
    exit(1)

y1 = []
y2 = []
y3 = []

s = True
with open(file_path,'r') as csvfile:
    plots = csv.reader(csvfile, delimiter = ',')
    for row in plots:
        if s:
            s = False
            continue
        y1.append(int(row[0]))
        y2.append(float(row[1]))
        y3.append(int(row[2]))

fig, ax1 = plt.subplots()
fig.set_figwidth(8)
fig.set_figheight(6)

ax2 = ax1.twinx()
ax1.plot(y1, 'b-', label="Simulated Annealing f(s) (false clauses)")
ax2.plot(y2, 'r-', label="Simulated Annealing Temperature (Cº)")
ax1.plot(y3, 'c-', label="Random Search best result (false clauses)")

ax1.set_xlabel('Iteration')
ax1.set_ylabel('MAX-SAT Cost (false clauses)', color='b')
ax2.set_ylabel('Simulated Annealing Temperature (Cº)', color='r')

fig.legend()
plt.savefig(out_path, dpi=100)