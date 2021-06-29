from tkinter import *
from tkinter.constants import NE, NW
from PIL import ImageTk,Image 
import tkinter.font as tkFont
import os 
BOARD_SIZE_OPTIONS = [
"3x3",
"4x4",
"5x5",
"6x6",
"7x7",
"8x8"
]
PIECE_OPTIONS = [
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
]

window = Tk()
window.title("Chessboard Menu")
window.minsize(600,600)
window.resizable(width = FALSE, height = FALSE)


roboto16=tkFont.Font(family="Roboto", size=16)
roboto12=tkFont.Font(family="Roboto",size=12)

board_size_label = Label(text="Select board size: ",font=roboto16).grid(row=0,column=0)



board_size_option = StringVar(window)
board_size_option.set(BOARD_SIZE_OPTIONS[0]) # default value


board_size_select= OptionMenu(window, board_size_option, *BOARD_SIZE_OPTIONS)
board_size_select.grid(row=0,column=1,pady=10)
board_size_select.config(font=roboto16)
board_size_menu = window.nametowidget(board_size_select.menuname)
board_size_menu.config(font=roboto12)  # Set the dropdown menu's font

number_of_pieces_label = Label(text="Select piece count:",font=roboto16).grid(row=1,column=0,padx=10,pady=15)


queen_img = ImageTk.PhotoImage(Image.open("pieces/queen.png"))  
king_img = ImageTk.PhotoImage(Image.open("pieces/king.png"))
rook_img = ImageTk.PhotoImage(Image.open("pieces/rook.png"))
bishop_img = ImageTk.PhotoImage(Image.open("pieces/bishop.png"))
knight_img = ImageTk.PhotoImage(Image.open("pieces/knight.png"))

queen_label=Label(text="Queen",font=roboto16).grid(row=2,column=0)
queen_canvas = Canvas(window, width = 106, height = 106)
queen_canvas.create_image(60, 50, image=queen_img) 
queen_canvas.grid(row=4,column=0)
number_of_queens_option = StringVar(window)
number_of_queens_option.set(PIECE_OPTIONS[0]) #default value
number_of_queens_select= OptionMenu(window, number_of_queens_option, *PIECE_OPTIONS)
number_of_queens_select.grid(row=4,column=1)
number_of_queens_select.config(font=roboto16)
queen_count_menu = window.nametowidget(number_of_queens_select.menuname)
queen_count_menu.config(font=roboto12)  # Set the dropdown menu's font

king_label=Label(text="King",font=roboto16).grid(row=5,column=0)
king_canvas = Canvas(window, width = 106, height = 106)
king_canvas.create_image(60,50,image=king_img)
king_canvas.grid(row=6,column=0)
number_of_kings_option = StringVar(window)
number_of_kings_option.set(PIECE_OPTIONS[0]) #default value
number_of_kings_select= OptionMenu(window, number_of_kings_option, *PIECE_OPTIONS)
number_of_kings_select.grid(row=6,column=1)
number_of_kings_select.config(font=roboto16)
king_count_menu = window.nametowidget(number_of_kings_select.menuname)
king_count_menu.config(font=roboto12)  # Set the dropdown menu's font

rook_label=Label(text="Rook",font=roboto16).grid(row=7,column=0)
rook_canvas = Canvas(window, width = 106, height = 106)
rook_canvas.create_image(60,50,image=rook_img)
rook_canvas.grid(row=8,column=0)
number_of_rooks_option = StringVar(window)
number_of_rooks_option.set(PIECE_OPTIONS[0]) #default value
number_of_rooks_select= OptionMenu(window, number_of_rooks_option, *PIECE_OPTIONS)
number_of_rooks_select.grid(row=8,column=1)
number_of_rooks_select.config(font=roboto16)
rook_count_menu = window.nametowidget(number_of_rooks_select.menuname)
rook_count_menu.config(font=roboto12)  # Set the dropdown menu's font

bishop_label=Label(text="Bishop",font=roboto16).grid(row=2,column=4)
bishop_canvas = Canvas(window, width = 106, height = 106)
bishop_canvas.create_image(60,50,image=bishop_img)
bishop_canvas.grid(row=4,column=4)
number_of_bishops_option = StringVar(window)
number_of_bishops_option.set(PIECE_OPTIONS[0]) #default value
number_of_bishops_select= OptionMenu(window, number_of_bishops_option, *PIECE_OPTIONS)
number_of_bishops_select.grid(row=4,column=5,padx=20)
number_of_bishops_select.config(font=roboto16)
bishop_count_menu = window.nametowidget(number_of_bishops_select.menuname)
bishop_count_menu.config(font=roboto12)  # Set the dropdown menu's font

knight_label=Label(text="Knight",font=roboto16).grid(row=5,column=4)
knight_canvas = Canvas(window, width = 106, height = 106)
knight_canvas.create_image(60,50,image=knight_img)
knight_canvas.grid(row=6,column=4)
number_of_knights_option = StringVar(window)
number_of_knights_option.set(PIECE_OPTIONS[0]) #default value
number_of_knights_select= OptionMenu(window, number_of_knights_option, *PIECE_OPTIONS)
number_of_knights_select.grid(row=6,column=5)
number_of_knights_select.config(font=roboto16)
knight_count_menu = window.nametowidget(number_of_knights_select.menuname)
knight_count_menu.config(font=roboto12)  # Set the dropdown menu's font

def startAllCombinations():
    board_size=board_size_option.get()[:1]
    print ("board size:" + board_size)
    queen_count = number_of_queens_option.get()
    print ("queens:" + queen_count)
    king_count = number_of_kings_option.get()
    print ("kings:" + king_count)
    rook_count = number_of_rooks_option.get()
    print ("rooks:" + rook_count)
    bishop_count = number_of_bishops_option.get()
    print ("bishops:" + bishop_count)
    knight_count = number_of_knights_option.get()
    print ("knights:" + knight_count)
    
    os.system("Project1.exe 1 "+str(board_size)+" "+str(queen_count)+" "+str(king_count)+" "+str(rook_count)+" "+str(bishop_count)+" "+str(knight_count))

def startCoupleCombinations():
    board_size=board_size_option.get()[:1]
    print ("board size:" + board_size)
    queen_count = number_of_queens_option.get()
    print ("queens:" + queen_count)
    king_count = number_of_kings_option.get()
    print ("kings:" + king_count)
    rook_count = number_of_rooks_option.get()
    print ("rooks:" + rook_count)
    bishop_count = number_of_bishops_option.get()
    print ("bishops:" + bishop_count)
    knight_count = number_of_knights_option.get()
    print ("knights:" + knight_count)

    os.system("Project1.exe 2 "+str(board_size)+" "+str(queen_count)+" "+str(king_count)+" "+str(rook_count)+" "+str(bishop_count)+" "+str(knight_count))


button_some_combinations = Button(window,text="Display couple of combinations",height=2,bg="#dcf7d5", font=roboto12,command = startCoupleCombinations).grid(row=9,column=4)
button_all_combinations = Button(window, text="        Display all combinations!   ",height=2,bg="#d5e4f7",font=roboto12, command=startAllCombinations).grid(row=10,column=4,pady=10)








window.mainloop()