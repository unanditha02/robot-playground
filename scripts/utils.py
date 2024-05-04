#!/usr/bin/python3

import numpy as np

import matplotlib.pyplot as plt


class Map():

    def __init__(self, filepath):
        self.map = []
        self.build_map(filepath=filepath)

    def build_map(self, filepath):
        file = open(filepath, 'r')
        data = []

        while True:
            content = file.readline()
            if not content:
                break
            if 'height' in content:
                self.height = int(content.split(' ')[-1])
            elif 'width' in content:
                self.width = int(content.split(' ')[-1])
            else:
                row = content.split(' ')
                data.append([float(i) for i in row if i != '\n'])
        file.close()

        self.map = np.array(data).reshape(self.height, self.width)

    def plot_map(self, ax):
        plt.imshow(self.map, interpolation='nearest')
        plt.colorbar()


class Path():

    def __init__(self, filepath):
        self.path = []
        self.get_path(filepath)

    def get_path(self, filepath):
        file = open(filepath, 'r')
        while True:
            content = file.readline()
            if not content:
                break
            row = content.split(' ')
            self.path.append([int(i) for i in row if i != '\n'])
        file.close()

    def plot_path(self, ax):
        for p in self.path:
            ax.plot(p[1], p[0], 'r+')
        return ax


class AStarPlan():

    def __init__(self):
        self.plan = None

    def get_plan(self, filepath):
        pass
