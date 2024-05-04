
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation, PillowWriter

from utils import Map, Path


class Visualizer:

    def __init__(self, ax):
        self.path = []
        self.frames = 0
        self.ax = ax

    def update(self, i):
        p = self.path[i]
        self.ax.plot(p[1], p[0], 'ro')
        self.ax.set_xlim([0, 50])
        self.ax.set_ylim([50, 0])

    def get_path(self, path):
        self.path = path
        self.frames = len(path)


if __name__ == '__main__':

    map_path = 'resources/map_basic.txt'
    result_path = 'resources/path.txt'
    gif_path = 'results/astar.gif'

    fig, ax = plt.subplots()
    ax.set_title('A Star Path')

    mymap = Map(filepath=map_path)
    mymap.plot_map(ax)

    mypath = Path(filepath=result_path)
    mypath.plot_path(ax)

    viz = Visualizer(ax)
    viz.get_path(path=mypath.path)

    ani = FuncAnimation(fig, viz.update, frames=viz.frames, interval=300)

    ani.save(gif_path, dpi=300, writer=PillowWriter(fps=4))
