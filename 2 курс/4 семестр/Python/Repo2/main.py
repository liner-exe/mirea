import numpy as np
import matplotlib.pyplot as plt

import random


def create_symmetry_matrix():
    matrix = np.zeros((5, 5))

    for i in range(5):
        for j in range(3):
            if random.random() >= 0.5:
                matrix[i][j] = 1

    for i in range(5):
        for j in range(3, 5):
            matrix[i][j] = matrix[i][4 - j]

    return matrix


def build_sprite_map(width=20, height=10, sprite_size=5, padding=1):
    tile_size = sprite_size + 2 * padding

    map_height = height * (sprite_size + 2 * padding)
    map_width = width * (sprite_size + 2 * padding)
    sprite_map = np.zeros((map_height, map_width))

    for y in range(height):
        for x in range(width):
            sprite = create_symmetry_matrix()

            y_start = y * tile_size + padding
            x_start = x * tile_size + padding

            sprite_map[
                y_start:y_start + sprite_size,
                x_start:x_start + sprite_size
            ] = sprite

    return sprite_map


def stay_alive():
    plt.pause(1)
    stay_alive()


def main():
    plt.figure(figsize=(12, 6))
    plt.ion()

    sprite_map = build_sprite_map(padding=2)
    plt.imshow(sprite_map, cmap="gray", interpolation="nearest")

    plt.xticks(range(0, 200, 25))
    plt.yticks(range(0, 100, 20))

    stay_alive()
    plt.show()


if __name__ == "__main__":
    main()
