def day2_part1():
    file1 = open('day2.in', 'r')
    Lines = file1.readlines()
    score = 0
    for line in Lines:
        if line[0] == 'A' and line[2] == 'X':
            score += (1 + 3)
        elif line[0] == 'A' and line[2] == 'Y':
            score += (2 + 6)
        elif line[0] == 'A' and line[2] == 'Z':
            score += (3 + 0)
        elif line[0] == 'B' and line[2] == 'X':
            score += (1 + 0)
        elif line[0] == 'B' and line[2] == 'Y':
            score += (2 + 3)
        elif line[0] == 'B' and line[2] == 'Z':
            score += (3 + 6)
        elif line[0] == 'C' and line[2] == 'X':
            score += (1 + 6)
        elif line[0] == 'C' and line[2] == 'Y':
            score += (2 + 0)
        elif line[0] == 'C' and line[2] == 'Z':
            score += (3 + 3)
        # print('Opponent: ', line[0], '| Me: ', line[2], '| Score: ', score)
    print('Part 1 score: ', score)


def day2_part2():
    file1 = open('day2.in', 'r')
    Lines = file1.readlines()
    score = 0
    for line in Lines:
        if line[0] == 'A' and line[2] == 'X':
            score += (3 + 0)
        elif line[0] == 'A' and line[2] == 'Y':
            score += (1 + 3)
        elif line[0] == 'A' and line[2] == 'Z':
            score += (2 + 6)
        elif line[0] == 'B' and line[2] == 'X':
            score += (1 + 0)
        elif line[0] == 'B' and line[2] == 'Y':
            score += (2 + 3)
        elif line[0] == 'B' and line[2] == 'Z':
            score += (3 + 6)
        elif line[0] == 'C' and line[2] == 'X':
            score += (2 + 0)
        elif line[0] == 'C' and line[2] == 'Y':
            score += (3 + 3)
        elif line[0] == 'C' and line[2] == 'Z':
            score += (1 + 6)
        # print('Opponent: ', line[0], '| Me: ', line[2], '| Score: ', score)
    print('Part 2 score: ', score)


if __name__ == '__main__':
    day2_part1()
    day2_part2()