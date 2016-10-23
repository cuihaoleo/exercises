from types import SimpleNamespace
from collections import Counter
import numpy as np
import pandas as pd
from pandas.tools.plotting import andrews_curves, radviz, parallel_coordinates
import matplotlib.pyplot as plt
import argparse
from sklearn.decomposition import PCA
from sklearn.cluster import KMeans
from scipy.spatial.distance import pdist, squareform
from scipy.cluster.vq import kmeans2


def read_data(csv, config):
    with open(config) as fin:
        use = fin.readline().strip().split(',')
        ref = fin.readline().strip()

    with open(csv) as fin:
        header = fin.readline().strip().split(',')
        use.sort(key=lambda i: header.index(i))

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
                    use_data.append(np.log(float(val)))
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


def pca(sp, dimens):
    X_pca = PCA(n_components=dimens).fit_transform(sp.data)
    sp.data = X_pca
    sp.data_header = ["F%d" % i for i in range(dimens)]


def pandas_plot(sp, ref, function=radviz):
    data = np.copy(sp.data)
    data.reshape((-1, len(sp.data_header)))
    dict_data = {
            h: sp.data[:, i] for i, h in enumerate(sp.data_header)}

    dict_data["REF"] = sp.flag
    df = pd.DataFrame(dict_data)

    dict_data["REF"] = ref
    df2 = pd.DataFrame(dict_data)

    fig, axes = plt.subplots(nrows=1, ncols=2)
    function(df, 'REF', marker='.', ax=axes[0])
    function(df2, 'REF', marker='.', ax=axes[1])
    plt.show()


def kmeans(sp, n_clusters=None):
    K = len(set(sp.flag)) if n_clusters is None else n_clusters
    km = KMeans(n_clusters=K, init='k-means++', verbose=True, n_init=10)
    km.fit(sp.data)
    return km.labels_


def kmeans_np(sp, n_clusters=None):
    K = len(set(sp.flag)) if n_clusters is None else n_clusters
    centroid, mark = kmeans2(sp.data, K)
    return mark


def maxmin(sp, n_clusters=None):
    K = len(set(sp.flag)) if n_clusters is None else n_clusters
    samples = sp.samples

    centers = [np.random.randint(samples)]
    dist_table = np.array([], dtype=np.float).reshape((0, samples))

    while True:
        last_center = centers[-1]
        ndist = np.linalg.norm(sp.data - sp.data[last_center, :], axis=1)
        dist_table = np.vstack((dist_table, ndist))

        min_dist = dist_table.min(axis=0)

        if len(centers) >= K:
            break

        argmax = min_dist.argmax()
        if min_dist[argmax] != 0:
            centers.append(argmax)
        else:
            break

    mark = []
    for i in range(samples):
        if i in centers:
            mark.append(centers.index(i))
        else:
            mark.append(dist_table[:, i].argmin())

    return mark


def system_clustering(sp, n_clusters=None, distance="euclidean",
                      samples_threshold=np.inf):

    samples = sp.samples
    K = len(set(sp.flag)) if n_clusters is None else n_clusters

    clusters = [{i} for i in range(samples)]
    samples_dist_table = squareform(pdist(sp.data, distance))
    centers_dist_table = np.copy(samples_dist_table)

    while len(clusters) > K:
        np.fill_diagonal(centers_dist_table, np.inf)

        while True:
            min_dist = centers_dist_table.min()
            il, jl = np.where(centers_dist_table == min_dist)
            i, j = il[0], jl[0]
            if len(clusters[i]) + len(clusters[j]) > samples_threshold:
                centers_dist_table[i, j] = centers_dist_table[j, i] = np.inf
            else:
                break

        row_i = centers_dist_table[:, i]
        row_j = centers_dist_table[:, j]
        nr = np.maximum(row_i, row_j)
        centers_dist_table[:, i] = nr
        centers_dist_table[i, :] = nr

        centers_dist_table = np.delete(centers_dist_table, j, 1)
        centers_dist_table = np.delete(centers_dist_table, j, 0)

        clusters[i].update(clusters[j])
        clusters.pop(j)

    mark = [None for i in range(samples)]
    for i, c in enumerate(clusters):
        for j in c:
            mark[j] = i

    return mark


def main():
    method_list = {
        "maxmin": maxmin,
        "system": system_clustering,
        "kmeans": kmeans,
        "kmeans_np": kmeans_np,
    }

    parser = argparse.ArgumentParser()
    parser.add_argument("file",
                        help="path to the csv file")
    parser.add_argument("config",
                        help="path to the config file")
    parser.add_argument("-m", "--method",
                        type=lambda k: method_list[k],
                        default="system",
                        help="clustering method",)
    parser.add_argument("-p", "--pca",
                        type=int,
                        default=0,
                        help="PCA dimens")
    parser.add_argument("-k", "--clusters",
                        type=int,
                        default=None,
                        help="PCA dimens")
    args = parser.parse_args()

    sp = read_data(args.file, args.config)
    if args.pca > 0:
        pca(sp, args.pca)

    # clustering
    labels = args.method(sp, args.clusters)

    # guess what the real label is
    counter_dict = {}
    for label in set(labels):
        counter_dict[label] = Counter()

    for i, real_label in enumerate(sp.flag):
        counter_dict[labels[i]][real_label] += 1

    guess_map = {}
    for label in sorted(list(set(labels))):
        real_label, _ = counter_dict[label].most_common(1)[0]
        guess_map[label] = real_label

    result_labels = []
    correct = 0
    for i, real_label in enumerate(sp.flag):
        guess_label = guess_map[labels[i]]
        result_labels.append(guess_label)
        if guess_label == real_label:
            correct += 1

    # plot result
    print("Correct: %f" % (correct / sp.samples))
    pandas_plot(sp, result_labels)


if __name__ == "__main__":
    main()
