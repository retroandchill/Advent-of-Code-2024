import sys

from parser import decode_matches

if __name__ == '__main__':
    if len(sys.argv) < 2:
        raise ValueError('Invalid input size!')

    filename = sys.argv[1]
    with open(filename) as f:
        content = ''.join(f.readlines())

    print(f'Decode matches: {decode_matches(content)}')