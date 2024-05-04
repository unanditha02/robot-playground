import matplotlib.pyplot as plt

from utils import Map, Path


if __name__ == '__main__':

    fig, ax = plt.subplots()

    map_path = 'resources/map_basic.txt'
    result_path = 'resources/path.txt'

    mymap = Map(filepath=map_path)
    mymap.plot_map(ax)

    mypath = Path(filepath=result_path)
    mypath.plot_path(ax)

    ax.set_title('A Star Path')
    plt.show()
