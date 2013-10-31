import sys
import numpy as np
import matplotlib.pyplot as plt

# filename = sys.argv[-1]
filename = "../Project3-build/output_EarthSunSystem.txt"

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

    fig = plt.figure(1)
    ax = fig.add_subplot(111, 
            xlabel=r'x-position [$AU$]',
            ylabel=r'y-position [$AU$]');
    for j in range(object_nr):
        if objects[j] == "Sun":
            ax.plot(positions[j][0], positions[j][1], 'or',
                    label=objects[j])
        else:
            ax.plot(positions[j][0], positions[j][1],
                    label=objects[j])
    
    box = ax.get_position()
    ax.set_position([box.x0, box.y0, box.width*0.8, box.height])
    ax.axis("equal")
    ax.grid('on')
    ax.legend(loc='center left', bbox_to_anchor=(1, 0.5),
            fancybox=True, shadow=True)


fig2 = plt.figure(2)
for j in range(dimensions):
    plt.plot(time, total_momentum[j])
    plt.hold('on')
plt.hold('off')
plt.grid('on')
plt.xlabel(r'Time [$yr$]')
plt.ylabel(r'Total Momentum [$M_{sun}\frac{AU}{yr}$]')
plt.legend(['x-direction', 'y-direction'])

plt.figure(3)
plt.plot(time,total_energy)
plt.grid('on')
plt.xlabel(r'Time [$yr$]')
plt.ylabel(r'Total Energy 

plt.show()
