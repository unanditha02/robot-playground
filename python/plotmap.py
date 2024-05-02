from map import Map


if __name__ == '__main__':

    map_path = '/home/unanditha02/projects_ws/src/Motion-Planning/resources/map_basic.txt'
    result_path = '/home/unanditha02/projects_ws/src/Motion-Planning/resources/path.txt'

    mymap = Map(filepath=map_path)
    mymap.plot_map()

    mymap.get_result(result_path)
    mymap.plot_map()