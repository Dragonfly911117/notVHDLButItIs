import sys


def main(args: list) -> None:
    print("Average finder v.0.1")
    avg = find_average(args)
    print(f"The average is {avg}")
    return


def find_average(args: list) -> float:
    result = 0.0
    for s in args:
        result += to_float(s)
    return result


def to_float(s: str):
    return float(s)


if __name__ == '__main__':
    main(sys.argv[1:])