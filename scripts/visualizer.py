#!/usr/bin/python3

import argparse
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

from utils import ObstacleMap, Path


class Visualizer:
    """
    Class to setup frames for the Animation plot
    """
    def __init__(self, ax):
        self.path = []
        self.frames = 0
        self.ax = ax

    def update(self, i):
        p = self.path[i]
        self.ax.plot(p[1], p[0], 'ro')

    def get_path(self, path):
        self.path = path
        self.frames = len(path)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-m', '--map-filepath', type=str, required=True)
    parser.add_argument('-r', '--result-filepath', type=str, required=True)
    parser.add_argument('-v', '--viz-filepath', type=str, required=True)
    args = parser.parse_args()

    map_path = args.map_filepath
    result_path = args.result_filepath
    gif_path = args.viz_filepath

    fig, ax = plt.subplots()
    ax.set_title('A Star Path')

    mymap = ObstacleMap(filepath=map_path)
    mymap.plot_map(ax)

    mypath = Path(filepath=result_path)
    mypath.plot_path(ax)

    viz = Visualizer(ax)
    viz.get_path(path=mypath.path)

    ani = FuncAnimation(fig, viz.update, frames=viz.frames, interval=300)

    ani.save(gif_path, dpi=300, writer=PillowWriter(fps=4))
