import sys

from parser import decode_with_conditions

if __name__ == '__main__':
    if len(sys.argv) < 2:
        raise ValueError('Invalid input size!')

    filename = sys.argv[1]
    with open(filename) as f:
        content = ''.join(f.readlines())

    print(f'Decode matches: {decode_with_conditions(content)}')