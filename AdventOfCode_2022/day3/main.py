
def find_common(list_of_sets):
    common = set.intersection(*list_of_sets)
    return common


def calculate_priorities(letters):
    # a -> 1 to z -> 26
    # A -> 27 to Z -> 52
    priority = 0
    for letter in letters:
        # If letter is lowercase
        if 97 <= ord(letter) <= 122:
            priority += (ord(letter) - 96)
        # If letter is uppercase
        elif 65 <= ord(letter) <= 90:
            priority += (ord(letter) - 38)
    return priority


def part_1(rucksacks):
    letters = []
    for rucksack in rucksacks:
        rucksack = rucksack.strip()
        sets = [set(rucksack[:len(rucksack) // 2]), set(rucksack[len(rucksack) // 2:])]
        letters.append(list(find_common(sets))[0])
    print('Part 1 priorities:', calculate_priorities(letters))


def part_2(rucksacks):
    letters = []
    for i in range(0,len(rucksacks),3):
        sets = [set(rucksacks[i].strip()), set(rucksacks[i + 1].strip()), set(rucksacks[i + 2].strip())]
        # print('sets: ', sets, 'Common: ', find_common(sets))
        letters.append(list(find_common(sets))[0])
    print('Part 2 priorities:', calculate_priorities(letters))


if __name__ == '__main__':
    file = open('day3.in', 'r')
    rucksacks = file.readlines()
    part_1(rucksacks)
    part_2(rucksacks)
