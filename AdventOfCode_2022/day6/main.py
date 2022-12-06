
def start_of_packet_marker(string):
    """
    Checks if a string is a marker. A string is a marker if none of the characters repeat
    The string should contain 4 characters
    """
    if len(string) != 4:
        return False
    for char in string:
        if string.count(char) > 1:
            return False
    return True


def start_of_message_marker(string):
    """
    Checks if a string is a marker. A string is a marker if none of the characters repeat
    The string should contain 14 characters
    """
    if len(string) != 14:
        return False
    for char in string:
        if string.count(char) > 1:
            return False
    return True


if __name__ == '__main__':
    file = open('day6.in', 'r')
    # file = open('day6_example.in', 'r')
    datastream = file.read()
    file.close()

    # Part 1
    # Look for the first packet marker in the datastream
    for i in range(len(datastream)):
        if start_of_packet_marker(datastream[i:i+4]):
            print('First marker after character', i + 4, 'is', datastream[i:i+4])
            break

    # Part 2
    # Look for the first message marker in the datastream
    for i in range(len(datastream)):
        if start_of_message_marker(datastream[i:i+14]):
            print('First marker after character', i + 14, 'is', datastream[i:i+14])
            break
