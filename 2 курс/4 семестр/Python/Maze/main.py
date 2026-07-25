import cv2
import numpy as np
import time

from pathlib import Path
import matplotlib.pyplot as plt
from collections import deque


def plot_one_image(image: np.ndarray):
    """
    Отобразить изображение с помощью matplotlib.
    Вспомогательная функция.

    :param image: изображение для отображения
    :return: None
    """
    plt.figure(figsize=(8, 7))
    if len(image.shape) == 2:
        plt.imshow(image, cmap='gray')
    else:
        plt.imshow(image)

    plt.axis('off')
    plt.show()


def plot_maze_path(img, path):
    img = img.copy()
    if img.ndim != 3:
        img = cv2.cvtColor(img, cv2.COLOR_GRAY2RGB)

    img = img.copy()
    for point in path:
        cv2.circle(img, point, 1, (255, 0, 0), -1)

    for i in range(len(path) - 1):
        cv2.line(img, path[i], path[i + 1], (255, 0, 0), 1)

    return img


def get_start_end_point(grid):
    '''
    найти координаты старта и выхода
    '''
    h, w = grid.shape

    top_row = np.where(grid[0, :] > 200)[0]
    bottom_row = np.where(grid[h - 1, :] > 200)[0]

    if len(top_row) > 0:
        start_point = (int(np.mean(top_row)), 0)
    else:
        start_point = (np.argwhere(grid[0:5, :] > 200)[0][1], 0)

    if len(bottom_row) > 0:
        end_point = (int(np.mean(bottom_row)), h - 1)
    else:
        coords = np.argwhere(grid[h - 5:h, :] > 200)
        end_point = (coords[-1][1], h - 1)

    return start_point, end_point


def get_neighbors(pos, img):
    x, y = pos
    neighbors = []

    for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
        nx, ny = x + dx, y + dy

        if 0 <= nx < img.shape[1] and 0 <= ny < img.shape[0]:
            if img[ny, nx] > 200:
                neighbors.append((nx, ny))
    return neighbors


def solve_maze_bfs(img, start, end):
    queue = deque([start])
    visited = {start: None}

    while queue:
        current = queue.popleft()
        if current == end:
            break

        for neighbor in get_neighbors(current, img):
            if neighbor not in visited:
                visited[neighbor] = current
                queue.append(neighbor)

    path = []
    curr = end

    while curr is not None:
        path.append(curr)
        curr = visited.get(curr)

    return path[::-1] if path[0] == end else []


def solve_maze_dfs(img, start, end):
    stack = [start]
    visited = {start: None}

    while stack:
        current = stack.pop()
        if current == end:
            break

        for neighbor in get_neighbors(current, img):
            if neighbor not in visited:
                visited[neighbor] = current
                stack.append(neighbor)

    path = []
    curr = end

    while curr is not None:
        path.append(curr)
        curr = visited.get(curr)

    return path[::-1] if path[0] == end else []


def main():
    images_paths = sorted([str(f) for f in Path('images').glob('*.png')])

    image_index = 3

    img_path = images_paths[image_index]
    print(f"Обработка файла : {img_path}")

    image = cv2.imread(img_path, cv2.IMREAD_GRAYSCALE)
    if image is None:
        print("Не удалось загрузить изображение.")
        return

    start_pos, end_pos = get_start_end_point(image)

    print(f"Старт: {start_pos}, финиш: {end_pos}")

    t0 = time.time()
    path_bfs = solve_maze_bfs(image, start_pos, end_pos)
    t_bfs = time.time() - t0

    t0 = time.time()
    path_dfs = solve_maze_dfs(image, start_pos, end_pos)
    t_dfs = time.time() - t0

    print('-' * 30)
    print(f"BFS: время {t_bfs:.4f} сек, длина пути {len(path_bfs)} пикс.")
    print(f"DFS: время {t_dfs:.4f} сек, длина пути {len(path_dfs)} пикс.")
    print('-' * 30)

    res_bfs = plot_maze_path(image, path_bfs)
    res_dfs = plot_maze_path(image, path_dfs)

    plot_one_image(res_bfs)
    plot_one_image(res_dfs)

    plt.pause(1000)


if __name__ == "__main__":
    main()