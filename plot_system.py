import sys
import numpy as np
import matplotlib.pyplot as plt

# filename = sys.argv[-1]
filename = "output_EarthSunSystem.txt"

input_file = open(filename, 'r')

i = -2
for line in input_file:
    column = line.split()
    if i == -2:
        objects = int(column[1])
        dimensions = int(column[3])
        time_step = float(column[6])
        end_time = float(column[9])

        steps = int(np.ceil(end_time/time_step))+1
        
        positions = np.zeros([objects, steps])
        velocity = np.zeros([

        i += 1



input_file.close()

print objects, dimensions, time_step, end_time, steps, i
