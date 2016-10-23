import sys
import argparse
import random


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("file", help="path to the csv file")
    parser.add_argument("key", help="path to the csv file")
    parser.add_argument("-p", "--percent",
                        type=float,
                        default=0.8,
                        help="How many samples are used to train")
    args = parser.parse_args()

    with open(args.file) as fin:
        head = fin.readline()
        sys.stdout.write(head)
        sys.stderr.write(head)

        key_index = head.split(",").index(args.key)
        d = {}
        for line in fin:
            key = line.split(",")[key_index]
            if key not in d:
                d[key] = []
            d[key].append(line)

    for k in sorted(d.keys()):
        dataset = d[k]
        random.shuffle(dataset)
        n_training = int(len(dataset) * args.percent)

        training = dataset[:n_training]
        testset = dataset[n_training:]

        for l in training:
            sys.stdout.write(l)

        for l in testset:
            sys.stderr.write(l)

if __name__ == "__main__":
    main()
