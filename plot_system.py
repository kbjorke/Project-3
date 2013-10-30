import sys
import numpy as np
import matplotlib.pyplot as plt

# filename = sys.argv[-1]
filename = "../Project3-build/output_EarthJupiterSunSystem.txt"

input_file = open(filename, 'r')

i = -2
for line in input_file:
    column = line.split()
    
    if i == -2:
        object_nr = int(column[1])
        dimensions = int(column[3])
        time_step = float(column[6])
        end_time = float(column[9])

        steps = int(np.ceil(end_time/time_step))+1
        
        positions = np.zeros([object_nr, dimensions, steps])
        time = np.zeros(steps)
        total_energy = np.zeros(steps)
        total_momentum = np.zeros([dimensions,steps])
        objects = []

    if i == -1:
        for j in range(object_nr):
            objects.append(column[j+1])

    if i >= 0:
        time[i] = float(column[0])
        
        for j in range(object_nr):
            coordinate = column[j+1][1:-1].split(",")
            for k in range(dimensions):
                positions[j][k][i] = float(coordinate[k])
            
        total_energy[i] = float(column[object_nr+1])

        momentum = column[object_nr+2][1:-1].split(",")
        for k in range(dimensions):
            total_momentum[k][i] = float(momentum[k])


    i += 1



input_file.close()

if dimensions == 2:

    plt.figure(1)
    for j in range(object_nr):
        if objects[j] == "Sun":
            plt.plot(positions[j][0], positions[j][1], 'or')
        else:
            plt.plot(positions[j][0], positions[j][1])
        plt.hold('on')

    plt.axis("equal")
    plt.hold('off')

plt.figure(2)
for j in range(dimensions):
    plt.plot(time, total_momentum[j]/max(total_momentum[j]))
    plt.hold('on')
plt.hold('off')
plt.axis([0,end_time, -1.3, 1.3])

plt.figure(3)
plt.plot(time,total_energy/total_energy[0])

plt.show()
