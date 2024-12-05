from functools import reduce
from re import Match
import re


def decode_matches(content: str) -> int:
    matches: list[str] = re.findall(r'mul\((\d+(?:,\d+)*)\)', content)
    multiplied = (mul(l) for l in matches)
    return reduce(lambda x, y: x + y, multiplied, 0)

def mul(numbers: str) -> int:
    parsed_numbers = (int(n) for n in numbers.split(','))
    return reduce(lambda a, b: a * b, parsed_numbers, 1)