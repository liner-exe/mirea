import matplotlib.colors
import numpy as np
import matplotlib.pyplot as plt

import random


FIELD_N = 5
FIELD_M = 5

SPRITE_N = 8
SPRITE_M = 8


colors = [
    "1D2B53", "7E2553", "008751", "AB5236", "5F574F",
    "C2C3C7", "FFF1E8", "FF004D", "FFA300", "FFEC27",
    "00E436", "29ADFF", "83769C", "FF77A8", "FFCCAA"
]


def create_symmetry_matrix():
    matrix = np.zeros((SPRITE_N, SPRITE_M, 3))

    print(matrix)

    is_even = SPRITE_N % 2 == 0
    half = SPRITE_N // 2 if is_even else SPRITE_N // 2 + 1

    for i in range(SPRITE_N):
        for j in range(half):
            if random.random() >= 0.5:
                pixel_color = matplotlib.colors.to_rgb("#" + random.choice(colors))
                matrix[i][j] = pixel_color

    for i in range(SPRITE_N):
        for j in range(half, SPRITE_N):
            matrix[i][j] = matrix[i][SPRITE_N - j - 1]

    return matrix


def build_sprite_map(width=20, height=10, sprite_size=5, padding=1):
    tile_size = sprite_size + 2 * padding

    map_height = height * tile_size
    map_width = width * tile_size
    sprite_map = np.zeros((map_height, map_width, 3))

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
    figure = plt.figure(figsize=(FIELD_N, FIELD_M))
    figure.canvas.manager.set_window_title("Colored sprite map by liner.exe")
    plt.ion()

    sprite_map = build_sprite_map(
        width=FIELD_N,
        height=FIELD_M,
        sprite_size=SPRITE_N,
        padding=2
    )

    plt.imshow(sprite_map, interpolation="nearest")

    plt.xticks(range(0, sprite_map.shape[1], 25))
    plt.yticks(range(0, sprite_map.shape[0], 20))

    stay_alive()
    plt.show()


if __name__ == "__main__":
    main()
