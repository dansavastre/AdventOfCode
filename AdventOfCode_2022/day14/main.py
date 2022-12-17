import numpy as np


def drop_sand(cave):
    sand_position = np.where(cave == '+')
    x_min, x_max = 0, np.where(cave_map == '#')[0].max()
    y_min, y_max = np.where(cave_map == '#')[1].min(), np.where(cave_map == '#')[1].max() + 2

    resting = False
    while not resting:
        resting = True
        if cave[sand_position[0] + 1, sand_position[1]] == '.':
            sand_position = (sand_position[0] + 1, sand_position[1])
            resting = False
        elif cave[sand_position[0] + 1, sand_position[1] - 1] == '.':
            sand_position = (sand_position[0] + 1, sand_position[1] - 1)
            resting = False
        elif cave[sand_position[0] + 1, sand_position[1] + 1] == '.':
            sand_position = (sand_position[0] + 1, sand_position[1] + 1)
            resting = False

        # Check if sand has left the area of interest
        if sand_position[0] > x_max or sand_position[0] < x_min or sand_position[1] > y_max or sand_position[1] < y_min:
            print('Sand has left the area of interest')
            return False
    cave[sand_position] = 'o'
    return True


if __name__ == '__main__':
    file = open('day14.in', 'r')
    # file = open('day14_example.in', 'r')
    lines = file.readlines()
    file.close()

    cave_map = np.zeros((1000, 1000), dtype=str)
    for line in lines:
        line = line.strip()
        rocks = line.split(' -> ')
        y, x = rocks[0].split(',')
        for i in range(1, len(rocks)):
            y1, x1 = rocks[i].split(',')
            # cave_map[int(x):int(x1) + 1, int(y):int(y1) + 1] = '#'
            if int(y) < int(y1):
                cave_map[int(x), int(y):int(y1) + 1] = '#'
            elif int(y) > int(y1):
                cave_map[int(x), int(y1):int(y) + 1] = '#'
            elif int(x) < int(x1):
                cave_map[int(x):int(x1) + 1, int(y)] = '#'
            elif int(x) > int(x1):
                cave_map[int(x1):int(x) + 1, int(y)] = '#'
            x = x1
            y = y1

    for i in range(1000):
        for j in range(1000):
            if cave_map[i, j] != '#':
                cave_map[i, j] = '.'

    # The position where sand falls from is 500, 0
    cave_map[0, 500] = '+'

    # Print the map around the area of interest
    x_min, x_max = np.where(cave_map == '#')[0].min(), np.where(cave_map == '#')[0].max()
    y_min, y_max = np.where(cave_map == '#')[1].min(), np.where(cave_map == '#')[1].max()
    cave_map[x_max + 2, :] = '#'

    # # Part 1
    # n_sand = 0
    # while drop_sand(cave_map):
    #     n_sand += 1
    # # print(cave_map[0:x_max + 1, y_min:y_max + 1])
    # print(f"Part 1: {n_sand}")

    # Part 2
    # print(len(np.where(cave_map == '-')[0]))
    n_sand = 0
    while len(np.where(cave_map == '+')[0]):
        # print(cave_map[0:x_max + 3, y_min:y_max + 1])
        if drop_sand(cave_map):
            n_sand += 1

    print(f"Part 2: {n_sand}")
