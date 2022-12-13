import numpy as np


def find_shortest_path(coords, height_map):
    q = []
    for coord in coords:
        q.append((coord, 0))
    visited = np.zeros((len(lines), len(lines[0].strip())))
    path_length = 0
    while len(q) > 0:
        (x, y), path_length = q.pop(0)
        if height_map[x, y] == 26:
            # print(f"Found the exit at ({x}, {y}) with path length {path_length}")
            break
        if visited[x, y] == 1:
            continue
        visited[x, y] = 1
        if x > 0 and visited[x - 1, y] == 0 and height_map[x - 1, y] - height_map[x, y] <= 1:
            q.append(((x - 1, y), path_length + 1))
        if x < len(lines) - 1 and visited[x + 1, y] == 0 and height_map[x + 1, y] - height_map[x, y] <= 1:
            q.append(((x + 1, y), path_length + 1))
        if y > 0 and visited[x, y - 1] == 0 and height_map[x, y - 1] - height_map[x, y] <= 1:
            q.append(((x, y - 1), path_length + 1))
        if y < len(lines[0]) - 2 and visited[x, y + 1] == 0 and height_map[x, y + 1] - height_map[x, y] <= 1:
            q.append(((x, y + 1), path_length + 1))
    return path_length


if __name__ == '__main__':
    file = open('day12.in', 'r')
    # file = open('day12_example.in', 'r')
    lines = file.readlines()
    file.close()
    coords = []
    height_map = np.zeros((len(lines), len(lines[0].strip())))
    for i in range(len(lines)):
        for j in range(len(lines[i])):
            if lines[i][j].islower():
                height_map[i][j] = ord(lines[i][j]) - ord('a')
            elif lines[i][j] == 'S':
                height_map[i][j] = 0
                coords = [(i, j)]
            elif lines[i][j] == 'E':
                height_map[i][j] = 26

    # Part 1
    print(f"Part 1: {find_shortest_path(coords, height_map)}")
    # Part 2
    coords = np.where(height_map == 0)
    coords = list(zip(coords[0], coords[1]))
    print(f"Part 2: {find_shortest_path(coords, height_map)}")
