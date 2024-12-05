from functools import reduce
from re import Match
import re
from typing import Iterable


def decode_matches(content: str) -> int:
    matches: list[str] = re.findall(r'mul\((\d+(?:,\d+)*)\)', content)
    return multiply_matches(matches)

def decode_with_conditions(content: str) -> int:
    matches: list[str] = re.findall(r'(do\(\)|don\'t\(\)|mul\(\d+(?:,\d+)*\))', content)
    valid_commands = process_commands(matches)
    return multiply_matches(valid_commands)


def process_commands(matches: list[str]):
    enabled = True
    for command in matches:
        if command == 'do()':
            enabled = True
        elif command == 'don\'t()':
            enabled = False
        elif enabled:
            match = re.match(r'mul\((\d+(?:,\d+)*)\)', command)
            yield match.group(1)


def multiply_matches(matches: Iterable[str]) -> int:
    multiplied = (mul(l) for l in matches)
    return reduce(lambda x, y: x + y, multiplied, 0)

def mul(numbers: str) -> int:
    parsed_numbers = (int(n) for n in numbers.split(','))
    return reduce(lambda a, b: a * b, parsed_numbers, 1)