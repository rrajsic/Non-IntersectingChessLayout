from tkinter import *
from tkinter.constants import NE, NW
from PIL import ImageTk, Image
from tkinter import ttk
from customtkinter import *
import os


class UI:
    def __init__(self):
        self.window = CTk()
        self.window.title("Chessboard Layout Menu")
        self.window.minsize(700, 600)
        self.window.resizable(width=FALSE, height=FALSE)

        self.BOARD_SIZE_OPTIONS = ["3x3", "4x4", "5x5", "6x6", "7x7", "8x8"]
        self.PIECE_OPTIONS = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]
        self.IMG_PIXEL_SIZE = 53
        self.roboto16 = CTkFont(family="Roboto", size=16)
        self.roboto12 = CTkFont(family="Roboto", size=12)

    def run(self):
        board_size_label = CTkLabel(
            self.window, text="Select board size: ", font=self.roboto16
        )
        board_size_label.place(relx=0.05, rely=0.05, anchor="w")

        self.board_size_option = StringVar(self.window)
        self.board_size_option.set(self.BOARD_SIZE_OPTIONS[0])  # default value

        board_size_select = CTkOptionMenu(
            self.window,
            variable=self.board_size_option,
            values=self.BOARD_SIZE_OPTIONS,
            width=70,
        )
        board_size_select.place(relx=0.25, rely=0.05, anchor="w")
        board_size_select.configure(font=self.roboto16)

        self.separator_1 = ttk.Separator(self.window, orient="horizontal")
        self.separator_1.place(relx=0.05, rely=0.10, anchor="w", relwidth=0.35)

        number_of_pieces_label = CTkLabel(
            self.window, text="Select piece count:", font=self.roboto16
        ).place(relx=0.05, rely=0.15, anchor="w")

        self.separator_2 = ttk.Separator(self.window, orient="horizontal")
        self.separator_2.place(relx=0.05, rely=0.20, anchor="w", relwidth=0.35)

        canvas_center = self.IMG_PIXEL_SIZE // 2  # Half of the canvas width
        # Queen
        queen_img = ImageTk.PhotoImage(Image.open("images/pieces/queen.png"))
        queen_canvas = CTkCanvas(
            self.window, width=self.IMG_PIXEL_SIZE, height=self.IMG_PIXEL_SIZE
        )
        queen_canvas.create_image(canvas_center, canvas_center, image=queen_img)
        queen_canvas.place(relx=0.05, rely=0.30, anchor="w")
        self.queen_count_option = StringVar(self.window)
        self.queen_count_option.set(self.PIECE_OPTIONS[0])
        queen_count_select = CTkOptionMenu(
            self.window,
            variable=self.queen_count_option,
            values=self.PIECE_OPTIONS,
            width=70,
        )
        queen_count_select.place(relx=0.15, rely=0.30, anchor="w")
        queen_count_select.configure(font=self.roboto16)

        # King
        king_img = ImageTk.PhotoImage(Image.open("images/pieces/king.png"))
        king_canvas = CTkCanvas(
            self.window, width=self.IMG_PIXEL_SIZE, height=self.IMG_PIXEL_SIZE
        )
        king_canvas.create_image(canvas_center, canvas_center, image=king_img)
        king_canvas.place(relx=0.05, rely=0.45, anchor="w")
        self.king_count_option = StringVar(self.window)
        self.king_count_option.set(self.PIECE_OPTIONS[0])
        king_count_select = CTkOptionMenu(
            self.window,
            variable=self.king_count_option,
            values=self.PIECE_OPTIONS,
            width=70,
        )
        king_count_select.place(relx=0.15, rely=0.45, anchor="w")
        king_count_select.configure(font=self.roboto16)

        # Bishop
        bishop_img = ImageTk.PhotoImage(Image.open("images/pieces/bishop.png"))
        bishop_canvas = CTkCanvas(
            self.window, width=self.IMG_PIXEL_SIZE, height=self.IMG_PIXEL_SIZE
        )
        bishop_canvas.create_image(canvas_center, canvas_center, image=bishop_img)
        bishop_canvas.place(relx=0.05, rely=0.60, anchor="w")
        self.bishop_count_option = StringVar(self.window)
        self.bishop_count_option.set(self.PIECE_OPTIONS[0])
        bishop_count_select = CTkOptionMenu(
            self.window,
            variable=self.bishop_count_option,
            values=self.PIECE_OPTIONS,
            width=70,
        )
        bishop_count_select.place(relx=0.15, rely=0.60, anchor="w")
        bishop_count_select.configure(font=self.roboto16)

        # Knight
        knight_img = ImageTk.PhotoImage(Image.open("images/pieces/knight.png"))
        knight_canvas = CTkCanvas(
            self.window, width=self.IMG_PIXEL_SIZE, height=self.IMG_PIXEL_SIZE
        )
        knight_canvas.create_image(canvas_center, canvas_center, image=knight_img)
        knight_canvas.place(relx=0.05, rely=0.75, anchor="w")
        self.knight_count_option = StringVar(self.window)
        self.knight_count_option.set(self.PIECE_OPTIONS[0])
        knight_count_select = CTkOptionMenu(
            self.window,
            variable=self.knight_count_option,
            values=self.PIECE_OPTIONS,
            width=70,
        )
        knight_count_select.place(relx=0.15, rely=0.75, anchor="w")
        knight_count_select.configure(font=self.roboto16)

        # Rook
        rook_img = ImageTk.PhotoImage(Image.open("images/pieces/rook.png"))
        rook_canvas = CTkCanvas(
            self.window, width=self.IMG_PIXEL_SIZE, height=self.IMG_PIXEL_SIZE
        )
        rook_canvas.create_image(canvas_center, canvas_center, image=rook_img)
        rook_canvas.place(relx=0.05, rely=0.90, anchor="w")
        self.rook_count_option = StringVar(self.window)
        self.rook_count_option.set(self.PIECE_OPTIONS[0])
        rook_count_select = CTkOptionMenu(
            self.window,
            variable=self.rook_count_option,
            values=self.PIECE_OPTIONS,
            width=70,
        )
        rook_count_select.place(relx=0.15, rely=0.90, anchor="w")
        rook_count_select.configure(font=self.roboto16)

        CTkButton_all_layouts = CTkButton(
            self.window,
            text="Display all",
            font=self.roboto16,
            width=200,
            command=lambda: self.runLayouts(1),
        ).place(relx=0.60, rely=0.70, anchor="w")
        CTkButton_first_combination_for_every_permutation = CTkButton(
            self.window,
            text="Display fundemental",
            font=self.roboto16,
            width=200,
            command=lambda: self.runLayouts(2),
        ).place(relx=0.60, rely=0.80, anchor="w")
        CTkButton_first_combination = CTkButton(
            self.window,
            text="Display first",
            font=self.roboto16,
            width=200,
            command=lambda: self.runLayouts(3),
        ).place(relx=0.60, rely=0.90, anchor="w")

        output_label = CTkLabel(self.window, text="Output:", font=self.roboto16).place(
            relx=0.75, rely=0.05, anchor="center"
        )
        output_frame = CTkFrame(self.window, width=200, height=100, bg_color="#e8e8e8")
        output_frame.place(relx=0.75, rely=0.15, anchor="center")

        self.window.mainloop()

    def runLayouts(self, layout_option):
        self.board_size = self.board_size_option.get()[:1]
        self.queen_count = self.queen_count_option.get()
        self.king_count = self.king_count_option.get()
        self.rook_count = self.rook_count_option.get()
        self.bishop_count = self.bishop_count_option.get()
        self.knight_count = self.knight_count_option.get()

        pieces_inputed = True

        if (
            int(self.queen_count)
            + int(self.king_count)
            + int(self.rook_count)
            + int(self.bishop_count)
            + int(self.knight_count)
            == 0
        ):
            pieces_inputed = False

        if pieces_inputed:

            output = self.createExeString(layout_option)

            if output < 0:
                self.createNotPossibleFail()

            else:
                self.createOutputSuccess(output)
        else:
            self.createSelectPiecesFail()

    def createExeString(self, layout_option):
        return os.system(
            "ChessLayoutEngine.exe "
            + str(layout_option)
            + " "
            + str(self.board_size)
            + " "
            + str(self.queen_count)
            + " "
            + str(self.king_count)
            + " "
            + str(self.rook_count)
            + " "
            + str(self.bishop_count)
            + " "
            + str(self.knight_count)
        )

    def createOutputSuccess(self, output):
        success_label = CTkLabel(
            self.window,
            text="Layouts displayed: " + str(output),
            width=200,
            height=100,
            bg_color="#0a4a1b",
            font=self.roboto16,
        )
        success_label.place(relx=0.75, rely=0.15, anchor="center")

    def createNotPossibleFail(self):
        not_possible_label = CTkLabel(
            self.window,
            text="Not possible!",
            width=200,
            height=100,
            bg_color="#4a1818",
            font=self.roboto16,
        )
        not_possible_label.place(relx=0.75, rely=0.15, anchor="center")

    def createSelectPiecesFail(self):
        fail_label = CTkLabel(
            self.window,
            text="Select pieces!",
            width=200,
            height=100,
            bg_color="#4a1818",
            font=self.roboto16,
        )
        fail_label.place(relx=0.75, rely=0.15, anchor="center")
