import numpy as np


def day1():
    file1 = open('day1.in', 'r')
    Lines = file1.readlines()
    calories = []
    current_sum = 0
    for line in Lines:
        line = line.strip()
        # check if line is a number
        # print("Line: ", line, line.isnumeric())
        if line.isnumeric():
            # print("Int: ", int(line))
            current_sum += int(line)
        else:
            calories.append(current_sum)
            current_sum = 0
    # Print the top 3 values
    # print(np.sum(sorted(calories, reverse=True)[:3]))
    print(f"Part 1: {np.max(calories)}")
    print(f"Part 2: {np.sum(sorted(calories, reverse=True)[:3])}")


if __name__ == '__main__':
    day1()
