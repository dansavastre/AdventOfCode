import ast
import numpy as np


def compare_packets(a, b):
    # both numeric
    if isinstance(a, int) and isinstance(b, int):
        if a == b:
            return None
        elif a < b:
            return True
        else:
            return False

    # Mixed types
    elif isinstance(a, int):
        return compare_packets([a], b)
    elif isinstance(b, int):
        return compare_packets(a, [b])

    # Both lists
    n = min(len(a), len(b))
    for i in range(n):
        res = compare_packets(a[i], b[i])
        if res is not None:
            return res
    if len(a) == len(b):
        return None
    elif len(a) < len(b):
        return True
    else:
        return False


if __name__ == '__main__':
    file = open('day13.in', 'r')
    # file = open('day13_example.in', 'r')
    lines = file.readlines()
    file.close()

    packets_part_1 = []
    packets_part_2 = []
    packets_part_2.append(ast.literal_eval('[[2]]'))
    packets_part_2.append(ast.literal_eval('[[6]]'))

    for i in range(0, len(lines), 3):
        # print(ast.literal_eval(lines[i]))
        packets_part_1.append((ast.literal_eval(lines[i]), ast.literal_eval(lines[i + 1])))
        packets_part_2.append(ast.literal_eval(lines[i]))
        packets_part_2.append(ast.literal_eval(lines[i + 1]))

    # Part 1
    res = 0
    for i in range(len(packets_part_1)):
        res += (i + 1) if compare_packets(packets_part_1[i][0], packets_part_1[i][1]) else 0
    print(f"Part 1: {res}")

    # Part 2
    # Compare packets two at a time until all packets are in the correct order
    correct_order = False
    while not correct_order:
        correct_order = True
        for i in range(len(packets_part_2) - 1):
            res = compare_packets(packets_part_2[i], packets_part_2[i + 1])
            if res is False:
                packets_part_2[i], packets_part_2[i + 1] = packets_part_2[i + 1], packets_part_2[i]
                correct_order = False

    # Print the ordered packets
    # for packet in packets_part_2:
    #     print(packet)

    print(f"Part 2: {(packets_part_2.index(ast.literal_eval('[[2]]')) + 1) * (packets_part_2.index(ast.literal_eval('[[6]]')) + 1)}")