#!/usr/bin/python3

import numpy as np

import matplotlib.pyplot as plt


class Map():
    def __init__(self, filepath):
        self.data = []
        self.path = []

        self.build_map(filepath=filepath)

    def build_map(self, filepath):
        file = open(filepath, 'r')
        data = []

        while True:
            content = file.readline()
            if not content:
                break
            if 'height' in content:
                self.height = content.split(' ')[-1]
            elif 'width' in content:
                self.width = content.split(' ')[-1]
            else:
                # print(content.split(' ')[:-1])
                row = content.split(' ')
                # row.remove('\n')
                data.append([float(i) for i in row if i != '\n'])
                # self.data.append(int(content))
        file.close()
        print(len(data[-1]), len(data[-2]))
        print(np.array(data[0]).shape)

        # self.data = np.array([np.array(d) for d in data], dtype=object)
        self.data = np.array(data).reshape(50, 50)
        print(self.data.shape)

    def get_result(self, result_path):
        file = open(result_path, 'r')
        rows = 0
        while True:
            content = file.readline()
            if not content:
                break
            row = content.split(' ')
            self.path.append([int(i) for i in row if i != '\n'])
            rows += 1

        file.close()
        for i, p in enumerate(self.path):
            if i in [1, 2, 3]:
                self.data[p[0]][p[1]] = float((i+1)/rows)
            else:
                self.data[p[0]][p[1]] = float(i/rows)
            # print(f'{p[0]}, {p[1]}: {self.data[p[0]][p[1]]} next: {self.data[p[0]+1][p[1]+1]} frac: {i} {rows} {i/rows} {float(i/rows)}')

    def plot_map(self):
        plt.imshow(self.data, interpolation='nearest')
        plt.colorbar()
        plt.title('2-D Heat Map')
        plt.show()

    def plot_path(self):
        plt.imshow(self.data, interpolation='nearest')
        plt.colorbar()
        for i, p in enumerate(self.path):
            plt.annotate(str(i), xy=(p[1]+0.5, p[0]+0.5), ha='center', va='center', color='white')

        plt.title('2-D Heat Map')
        plt.show()

if __name__ == '__main__':

    map_path = '/home/unanditha02/projects_ws/src/Motion-Planning/resources/map_basic.txt'
    result_path = '/home/unanditha02/projects_ws/src/Motion-Planning/resources/path.txt'

    mymap = Map(filepath=map_path)
    mymap.plot_map()

    mymap.get_result(result_path)
    mymap.plot_map()

    # mymap.plot_path()