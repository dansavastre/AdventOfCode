import numpy as np

if __name__ == '__main__':
    file = open('day10.in', 'r')
    # file = open('day10_example.in', 'r')
    commands = file.readlines()
    file.close()

    X = 1
    cycle = 1
    register_values = []
    # crt = np.ndarray((15, 47), dtype=str)
    # print(crt.shape)
    for command in commands:
        if command[:4] == 'noop':
            # print('noop')
            register_values.append(X)
        elif command[:4] == 'addx':
            # print(f"addx {command[5:-1]}")
            register_values.append(X)
            register_values.append(X)
            # print(f"X: {X} -> {X + int(command[5:-1])}")
            X += int(command[5:-1])
            # register_values.append(X)
        cycle += 1

    if register_values[-1] != X:
        register_values.append(X)
    crt = ''
    for i in range(len(register_values) - 2):
        print(f"Drawing pixel: {i%40 + 1}, sprite: {register_values[i]}, {register_values[i] + 1}, {register_values[i] + 2}")
        j = i % 40 + 1
        if j == register_values[i] or j == register_values[i] + 1 or j == register_values[i] + 2:
            crt += '#'
            print("#")
        else:
            crt += ' '
            print(" ")
        if(i % 40 == 39):
            crt += '\n'
    print(crt)
    signal_strengths = [register_values[i] * (i+1) for i in range(len(register_values))]
    # print(f"Register values: {register_values}")
    # Print the 20th value in the register and every 40th value after that(20th, 60th, 100th, etc.)
    # print(f"Register values 20th, 60th, 10th, etc.: {signal_strengths[19::40]}")
    print(f"Part 1: {np.sum(signal_strengths[19::40])}")
