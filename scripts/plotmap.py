#!/usr/bin/python3

import argparse
import matplotlib.pyplot as plt

from utils import ObstacleMap, Path


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('-m', '--map-filepath', type=str, required=True)
    parser.add_argument('-r', '--result-filepath', type=str, required=True)
    args = parser.parse_args()

    fig, ax = plt.subplots()

    # map_path = 'resources/map_basic.txt'
    map_path = 'resources/obstacle_map.txt'
    result_path = 'resources/path.txt'

    mymap = ObstacleMap(filepath=args.map_filepath)
    mymap.plot_map(ax)

    mypath = Path(filepath=args.result_filepath)
    mypath.plot_path(ax)

    ax.set_title('A Star Path')
    plt.show()
