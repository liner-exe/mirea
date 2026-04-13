import matplotlib.pyplot as plt
import time

import random


def create_symmetry_matrix():
    matrix = [[0] * 5 for _ in range(5)]

    for i in range(5):
        for j in range(3):
                if random.random() >= 0.5:
                    matrix[i][j] = 1

    for i in range(5):
        for j in range(3, 5):
            matrix[i][j] = matrix[i][4-j]

    return matrix


def endlessly_generate(im):
    im.set_data(create_symmetry_matrix())
    plt.draw()
    plt.pause(1)
    endlessly_generate(im)


def stay_alive():
    plt.pause(1)
    stay_alive()


def main():
    plt.figure(figsize=(6, 6))

    matrix = create_symmetry_matrix()
    im = plt.imshow(
        matrix,
        cmap="gray_r",
        interpolation="nearest",
        vmin=0,
        vmax=1
    )

    plt.xticks(range(0, 5, 2))
    plt.yticks(range(5))

    plt.ion()

    stay_alive()
    # endlessly_generate(im)
    plt.show()


if __name__ == "__main__":
    main()
