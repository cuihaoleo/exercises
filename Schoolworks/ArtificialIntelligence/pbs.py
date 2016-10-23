#!/usr/bin/env python3

try:
    from types import SimpleNamespace
except ImportError:
    SimpleNamespace = type("SimpleNamespace", (), {})

from collections import Counter
import numpy as np
import pandas as pd
from pandas.tools.plotting import andrews_curves, radviz, parallel_coordinates
import argparse
from sklearn import svm
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
from scipy.spatial.distance import pdist, squareform
from scipy.cluster.vq import kmeans2
import matplotlib.pyplot as plt


def read_data(csv, config):
    with open(config) as fin:
        use = fin.readline().strip().split(',')
        ref = fin.readline().strip()

    with open(csv) as fin:
        header = fin.readline().strip().split(',')
        use.sort(key = lambda i: header.index(i))
    
        data_matrix = np.array([], dtype=np.float).reshape(0, len(use))
        ref_array = []
    
        ref_data = None
        for line in fin:
            entry = line.strip().split(',')
            use_data = []
            del ref_data
    
            for i, val in enumerate(entry):
                label = header[i]
                if label in use:
                    use_data.append(np.log10(float(val)))
                elif label == ref:
                    ref_data = int(val)
    
            data_matrix = np.vstack((data_matrix, use_data))
            ref_array.append(ref_data)
    
    ret = SimpleNamespace()
    ret.data_header = use
    ret.data = data_matrix
    ret.flag = ref_array
    ret.samples = len(ref_array)

    return ret


def simple_perception(sp, C = 1e-10, max_round = 10000):

    def predict(X):
        cr = w.dot(np.append(X, 1))
        return reverse_flag_map[cr.argmax()]

    sample_dim = sp.data.shape[1] + 1
    all_flags = sorted(list(set(sp.flag)))
    n_clusters = len(all_flags)
    flag_map = dict(zip(all_flags, range(n_clusters)))
    reverse_flag_map = { v: k for k, v in flag_map.items() }
    data = np.c_[sp.data, [1] * sp.samples]
    round_count = 0

    w = np.matrix(np.zeros([n_clusters, sample_dim]))
    while True:
        bad_count = 0
        round_count += 1

        for index in range(sp.samples):
            vec = data[index, :]
            d_vec = w.dot(vec)
            flag = flag_map[sp.flag[index]]
            di = d_vec[0, flag]
            need_update = False
            for i, d in enumerate(d_vec.flat):
                if i != flag and d >= di:
                    w[i, :] -= C * vec
                    #w[flag, :] += C * vec
                    need_update = True

            if need_update:
                w[flag, :] += C * vec
                bad_count += 1

        if bad_count == 0:
            break
        if round_count >= max_round:
            print("Didn't convergence after %d rounds" % max_round)
            break

    #print(w)
    return predict


def wow_svm(sp):
    clf = svm.SVC()
    clf.fit(sp.data, sp.flag)
    return lambda X: clf.predict(X.reshape(1, -1))[0] 


def linear_svm(sp):
    clf = svm.LinearSVC()
    clf.fit(sp.data, sp.flag)
    return lambda X: clf.predict(X.reshape(1, -1))[0] 


def main():
    method_list = {
        "simple_perception": simple_perception,
        "svm": wow_svm,
        "linear_svm": linear_svm,
    }

    parser = argparse.ArgumentParser()
    parser.add_argument("trainset",
                        help="path to the training csv file")
    parser.add_argument("testset",
                        help="path to the testing csv file")
    parser.add_argument("config",
                        help="path to the config file")
    parser.add_argument("-m", "--method",
                        type=lambda k: method_list[k],
                        default="simple_perception",
                        help="clustering method",)
    parser.add_argument("-p", "--pca",
                        type=int,
                        default=0,
                        help="PCA dimens")
    args = parser.parse_args()

    trainset_sp = read_data(args.trainset, args.config)
    testset_sp = read_data(args.testset, args.config)

    # clustering
    predict = args.method(trainset_sp)

    correct = 0
    guess = []
    ct = Counter()
    for i in range(testset_sp.samples):
        X = testset_sp.data[i, :]
        guess.append(predict(X))
        ct[(testset_sp.flag[i], guess[i])] += 1
        if guess[i] == testset_sp.flag[i]:
            correct += 1
    print(ct)

    # plot result
    print("Correct: %f" % (correct / testset_sp.samples))
    pandas_plot(testset_sp, guess)


def pandas_plot(sp, ref, function=radviz):
    data = np.copy(sp.data)
    data.reshape((-1, len(sp.data_header)))
    dict_data = { h: sp.data[:,i]  for i, h in enumerate(sp.data_header)}

    dict_data["REF"] = sp.flag
    df = pd.DataFrame(dict_data)

    dict_data["REF"] = ref
    df2 = pd.DataFrame(dict_data)

    fig, axes = plt.subplots(nrows=1, ncols=2)
    function(df, 'REF', marker='.', ax=axes[0])
    function(df2, 'REF', marker='.', ax=axes[1])
    plt.show()


if __name__ == "__main__":
    ret = main()
