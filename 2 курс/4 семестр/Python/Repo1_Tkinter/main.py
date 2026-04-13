import tkinter as tk
from tkinter import Tk
import random

import config as cfg

root = Tk()


def draw_square(canvas, pos_x, pos_y) -> None:
    if pos_x > cfg.SIDE_COUNT - 1 or pos_y > cfg.SIDE_COUNT - 1:
        return

    square_side = cfg.SIDE_SIZE / cfg.SIDE_COUNT

    canvas.create_rectangle(
        pos_x * square_side, pos_y * square_side,
        pos_x * square_side + square_side, pos_y * square_side + square_side,
        fill="#111",
        outline=""
    )


def create_symmetry_matrix():
    matrix = [[0] * cfg.SIDE_COUNT for _ in range(cfg.SIDE_COUNT)]

    is_even = len(matrix) % 2 == 0
    formula = int(cfg.SIDE_COUNT / 2) if is_even else int(cfg.SIDE_COUNT / 2 + 1)

    for i in range(cfg.SIDE_COUNT):
        for j in range(formula):
                if random.random() >= 0.5:
                    matrix[i][j] = 1

    for i in range(cfg.SIDE_COUNT):
        for j in range(formula, cfg.SIDE_COUNT):
            matrix[i][j] = matrix[i][cfg.SIDE_COUNT-1-j]

    return matrix


def generate(canvas):
    canvas.delete("all")

    matrix = create_symmetry_matrix()
    for i in range(cfg.SIDE_COUNT):
        for j in range(cfg.SIDE_COUNT):
            if matrix[i][j] == 1:
                draw_square(canvas, j, i)


def generate_endlessly(canvas):
    generate(canvas)
    root.after(cfg.GEN_INTERVAL_MS, lambda: generate_endlessly(canvas))


def main():
    root.geometry(f"{cfg.WIN_SIZE_X}x{cfg.WIN_SIZE_Y}+{cfg.WIN_OFFSET_X}+{cfg.WIN_OFFSET_Y}")
    root.configure(background="#aaa")

    canvas = tk.Canvas(
        root,
        width=cfg.SIDE_SIZE,
        height=cfg.SIDE_SIZE,
        bg="#fff",
        highlightthickness=0
    )
    canvas.pack(expand=True)

    generate(canvas)

    if cfg.IS_AUTO:
        generate_endlessly(canvas)
    else:
        button = tk.Button(text="generate", command=lambda: generate(canvas))
        button.pack()

    root.mainloop()


if __name__ == "__main__":
    main()
