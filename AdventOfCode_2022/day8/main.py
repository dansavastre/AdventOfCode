import numpy as np


if __name__ == '__main__':
    file = open('day8.in', 'r')
    # file = open('day8_example.in', 'r')
    lines = file.readlines()
    n = len(lines)
    m = len(lines[0]) - 1
    height_map = np.zeros((n, m))
    visibility_map = np.zeros((n, m))
    for i in range(len(lines)):
        lines[i] = lines[i].strip()
        for j in range(len(lines[i])):
            height_map[i][j] = int(lines[i][j])

    # print(height_map)

    for i in range(n):
        for j in range(m):
            # Check if the current position is on the edge
            if i == 0 or i == n - 1 or j == 0 or j == m - 1:
                visibility_map[i][j] = 1
                continue
            # Check if the current position is visible
            # Loop over the directions up, down, left, right
            # For each direction, check if there is a higher position
            # If there is, then the current position is not visible in that direction
            # If there is not, then the current position is visible in that direction
            # If the current position is visible in at least one direction, then it is visible
            for direction in range(4):
                if direction == 0:
                    # Check up
                    for k in range(i - 1, -1, -1):
                        if height_map[k][j] >= height_map[i][j]:
                            break
                        if k == 0:
                            # print(f"Position ({i}, {j} -> {height_map[i][j]}) is visible from up")
                            visibility_map[i][j] = 1
                elif direction == 1:
                    # Check down
                    for k in range(i + 1, n):
                        if height_map[k][j] >= height_map[i][j]:
                            break
                        if k == n - 1:
                            # print(f"Position ({i}, {j} -> {height_map[i][j]}) is visible from down")
                            visibility_map[i][j] = 1
                elif direction == 2:
                    # Check left
                    for k in range(j - 1, -1, -1):
                        if height_map[i][k] >= height_map[i][j]:
                            break
                        if k == 0:
                            # print(f"Position ({i}, {j} -> {height_map[i][j]}) is visible from left")
                            visibility_map[i][j] = 1
                else:
                    # Check right
                    for k in range(j + 1, m):
                        if height_map[i][k] >= height_map[i][j]:
                            break
                        if k == m - 1:
                            # print(f"Position ({i}, {j} -> {height_map[i][j]}) is visible from right")
                            visibility_map[i][j] = 1

    # print(visibility_map)
    print(f"Number of visible trees: {np.sum(visibility_map)}")

    # Part 2
    score_map = np.zeros((n, m))
    for i in range(n):
        for j in range(m):
            # print(f"Position ({i}, {j} -> {height_map[i][j]})")
            scores = np.zeros(4)
            for direction in range(4):
                # print(f"Direction {direction}")
                if direction == 0:
                    # Check up
                    for k in range(i - 1, -1, -1):
                        # print(f"Checking ({k}, {j}) -> {height_map[k][j]}")
                        if height_map[k][j] < height_map[i][j]:
                            scores[direction] += 1
                        else:
                            if k != 0:
                                scores[direction] += 1
                            # print(f"Position ({i}, {j} -> {height_map[i][j]}) has score {scores[direction]} from up")
                            break
                elif direction == 1:
                    # Check down
                    for k in range(i + 1, n):
                        # print(f"Checking ({k}, {j}) -> {height_map[k][j]}")
                        if height_map[k][j] < height_map[i][j]:
                            scores[direction] += 1
                        else:
                            if k != n:
                                scores[direction] += 1
                            # print(f"Position ({i}, {j} -> {height_map[i][j]}) has score {scores[direction]} from down")
                            break
                elif direction == 2:
                    # Check left
                    for k in range(j - 1, -1, -1):
                        # print(f"Checking ({i}, {k}) -> {height_map[i][k]}")
                        if height_map[i][k] < height_map[i][j]:
                            scores[direction] += 1
                        else:
                            if k != 0:
                                scores[direction] += 1
                            # print(f"Position ({i}, {j} -> {height_map[i][j]}) has score {scores[direction]} from left")
                            break
                else:
                    # Check right
                    for k in range(j + 1, m):
                        # print(f"Checking ({i}, {k}) -> {height_map[i][k]}")
                        if height_map[i][k] < height_map[i][j]:
                            scores[direction] += 1
                        else:
                            if k != m:
                                scores[direction] += 1
                            # print(f"Position ({i}, {j} -> {height_map[i][j]}) has score {scores[direction]} from right")
                            break
            # print(f"Position ({i}, {j} -> {height_map[i][j]}) has scores {scores}")
            score_map[i][j] = scores[0] * scores[1] * scores[2] * scores[3]

    print(f"Max score: {np.max(score_map)}")
