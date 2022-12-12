import re
import numpy as np


class Monkey:
    """
    A monkey class
    Attributes:
        - index: the index of the monkey
        - items: the items the monkey has
        - operation: the opperation the monkey is doing
        - operation_value: the value of the operation
    """
    def __init__(self, index, items, operation, operation_value, division_value, action_true, action_false):
        self.index = index
        self.items = items
        self.operation = operation
        self.operation_value = operation_value
        self.division_value = division_value
        self.action_true = action_true
        self.action_false = action_false
        self.items_inspected = 0

    def __str__(self):
        return f"Monkey {self.index} | Items: {self.items} | new = old {self.operation} {'old' if self.operation_value is None else self.operation_value} | division_value = {self.division_value} | action_true = {self.action_true} | action_false = {self.action_false}"

    def __repr__(self):
        return self.__str__()


def play_round(monkeys):
    """
    Play a round of the game
    """
    for monkey in monkeys:
        monkey.items.reverse()
        while monkey.items:
            item = monkey.items.pop()
            monkey.items_inspected += 1
            if monkey.operation == "+":
                worry_level = item + item if monkey.operation_value is None else item + monkey.operation_value
            elif monkey.operation == "*":
                worry_level = item * item if monkey.operation_value is None else item * monkey.operation_value
            worry_level //= 3
            if worry_level % monkey.division_value == 0:
                monkeys[monkey.action_true].items.append(worry_level)
                # print(f"Monkey {monkey.index} gives {worry_level} to Monkey {monkey.action_true}")
            else:
                monkeys[monkey.action_false].items.append(worry_level)
                # print(f"Monkey {monkey.index} gives {worry_level} to Monkey {monkey.action_false}")


def play_round_new(monkeys):
    """
    Play a round of the game
    """
    lcm = 1
    for monkey in monkeys:
        lcm *= monkey.division_value
    for monkey in monkeys:
        monkey.items.reverse()
        while monkey.items:
            worry_level = 0
            item = monkey.items.pop()
            monkey.items_inspected += 1
            if monkey.operation == "+":
                worry_level = item + item if monkey.operation_value is None else item + monkey.operation_value
            elif monkey.operation == "*":
                worry_level = item * item if monkey.operation_value is None else item * monkey.operation_value
            if worry_level % monkey.division_value == 0:
                monkeys[monkey.action_true].items.append(worry_level % lcm)
            else:
                monkeys[monkey.action_false].items.append(worry_level % lcm)


def simulate(n_rounds, monkeys, round_function):
    # Play the game
    for _ in range(n_rounds):
        round_function(monkeys)
    # Multiply the 2 most inspected items
    items_inspected = [monkey.items_inspected for monkey in monkeys]
    items_inspected.sort()
    return items_inspected[-1] * items_inspected[-2]


if __name__ == '__main__':
    file = open('day11.in', 'r')
    # file = open('day11_example.in', 'r')
    lines = file.readlines()
    file.close()

    monkeys_part_1 = []
    monkeys_part_2 = []
    for i in range(0, len(lines), 7):
        monkey_text = lines[i:i+6]
        numbers = re.findall(r'\d+', monkey_text[1])
        has_value = re.findall(r'\d+', monkey_text[2])
        if has_value:
            operation_value = int(has_value[0])
        else:
            operation_value = None
        monkeys_part_1.append(Monkey(i//6, [int(x) for x in numbers], monkey_text[2][23], operation_value, int(re.findall(r'\d+', monkey_text[3])[0]), int(re.findall(r'\d+', monkey_text[4])[0]), int(re.findall(r'\d+', monkey_text[5])[0])))
        monkeys_part_2.append(Monkey(i//6, [int(x) for x in numbers], monkey_text[2][23], operation_value, int(re.findall(r'\d+', monkey_text[3])[0]), int(re.findall(r'\d+', monkey_text[4])[0]), int(re.findall(r'\d+', monkey_text[5])[0])))

    # Part 1
    print(f"Part 1: {simulate(20, monkeys_part_1, play_round)}")

    # Part 2
    print(f"Part 2: {simulate(10000, monkeys_part_2, play_round_new)}")

