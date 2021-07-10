from tkinter import *
from tkinter.constants import NE, NW
from PIL import ImageTk,Image 
import tkinter.font as tkFont
import os 
import subprocess
import sys

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
    "9"
]

window = Tk()
window.title("Chessboard Menu")
window.minsize(900,600)
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


queen_img = ImageTk.PhotoImage(Image.open("images/pieces/queen.png"))  
king_img = ImageTk.PhotoImage(Image.open("images/pieces/king.png"))
rook_img = ImageTk.PhotoImage(Image.open("images/pieces/rook.png"))
bishop_img = ImageTk.PhotoImage(Image.open("images/pieces/bishop.png"))
knight_img = ImageTk.PhotoImage(Image.open("images/pieces/knight.png"))

queen_label=Label(text="Queen",font=roboto16).grid(row=2,column=0)
queen_canvas = Canvas(window, width = 106, height = 106)
queen_canvas.create_image(60, 50, image=queen_img) 
queen_canvas.grid(row=4,column=0)
queen_count_option = StringVar(window)
queen_count_option.set(PIECE_OPTIONS[0]) #default value
queen_count_select= OptionMenu(window, queen_count_option, *PIECE_OPTIONS)
queen_count_select.grid(row=4,column=1)
queen_count_select.config(font=roboto16)
queen_count_menu = window.nametowidget(queen_count_select.menuname)
queen_count_menu.config(font=roboto12)  # Set the dropdown menu's font

king_label=Label(text="King",font=roboto16).grid(row=5,column=0)
king_canvas = Canvas(window, width = 106, height = 106)
king_canvas.create_image(60,50,image=king_img)
king_canvas.grid(row=6,column=0)
king_count_option = StringVar(window)
king_count_option.set(PIECE_OPTIONS[0]) #default value
king_count_select= OptionMenu(window, king_count_option, *PIECE_OPTIONS)
king_count_select.grid(row=6,column=1)
king_count_select.config(font=roboto16)
king_count_menu = window.nametowidget(king_count_select.menuname)
king_count_menu.config(font=roboto12)  # Set the dropdown menu's font

bishop_label=Label(text="Bishop",font=roboto16).grid(row=2,column=5)
bishop_canvas = Canvas(window, width = 106, height = 106)
bishop_canvas.create_image(60,50,image=bishop_img)
bishop_canvas.grid(row=4,column=5)
bishop_count_option= StringVar(window)
bishop_count_option.set(PIECE_OPTIONS[0]) #default value
bishop_count_select= OptionMenu(window, bishop_count_option, *PIECE_OPTIONS)
bishop_count_select.grid(row=4,column=6,padx=20)
bishop_count_select.config(font=roboto16)
bishop_count_menu = window.nametowidget(bishop_count_select.menuname)
bishop_count_menu.config(font=roboto12)  # Set the dropdown menu's font

knight_label=Label(text="Knight",font=roboto16).grid(row=5,column=5)
knight_canvas = Canvas(window, width = 106, height = 106)
knight_canvas.create_image(60,50,image=knight_img)
knight_canvas.grid(row=6,column=5)
knight_count_option = StringVar(window)
knight_count_option.set(PIECE_OPTIONS[0]) #default value
knight_count_select= OptionMenu(window, knight_count_option, *PIECE_OPTIONS)
knight_count_select.grid(row=6,column=6)
knight_count_select.config(font=roboto16)
knight_count_menu = window.nametowidget(knight_count_select.menuname)
knight_count_menu.config(font=roboto12)  # Set the dropdown menu's font

rook_label=Label(text="Rook",font=roboto16).grid(row=2,column=7)
rook_canvas = Canvas(window, width = 106, height = 106)
rook_canvas.create_image(60,50,image=rook_img)
rook_canvas.grid(row=4,column=7)
rook_count_option = StringVar(window)
rook_count_option.set(PIECE_OPTIONS[0]) #default value
rook_count_select= OptionMenu(window, rook_count_option, *PIECE_OPTIONS)
rook_count_select.grid(row=4,column=8)
rook_count_select.config(font=roboto16)
rook_count_menu = window.nametowidget(rook_count_select.menuname)
rook_count_menu.config(font=roboto12)  # Set the dropdown menu's font

def startAllLayouts():
    board_size=board_size_option.get()[:1]
    queen_count = queen_count_option.get()
    king_count = king_count_option.get()
    rook_count = rook_count_option.get()
    bishop_count = bishop_count_option.get()
    knight_count = knight_count_option.get()

    pieces_inputed = True

    if int(queen_count) + int(king_count) + int(rook_count) + int(bishop_count) + int(knight_count) == 0:
        pieces_inputed = False

    if pieces_inputed:

        output = os.system("ChessCombinationEngine.exe 1 "+str(board_size)+" "+str(queen_count)+" "+str(king_count)+" "+str(rook_count)+" "+str(bishop_count)+" "+str(knight_count))
        
        if output < 0:
            output_frame.destroy()
            not_possible_label = Label(window,text="Not possible!",width = 33, height = 8, bg = "#ff9180",font=roboto16)
            not_possible_label.grid(row=9,column=6,columnspan = 4,rowspan=3,padx=20)

        else:
            output_frame.destroy()
            success_label = Label(window,text="Number of displayed layouts: "+str(output),width = 33, height = 8, bg = "#99ff9b",font=roboto16)
            success_label.grid(row=9,column=6,columnspan = 4,rowspan=3,padx=20)
    else:
        output_frame.destroy()
        fail_label = Label(window,text="Select pieces!",width = 33, height = 8, bg = "#ff9180",font=roboto16)
        fail_label.grid(row=9,column=6,columnspan = 4,rowspan=3,padx=20)

def startFirstlayoutsForEveryPermutation():
    board_size=board_size_option.get()[:1]
    queen_count = queen_count_option.get()
    king_count = king_count_option.get()
    rook_count = rook_count_option.get()
    bishop_count = bishop_count_option.get()
    knight_count = knight_count_option.get()

    pieces_inputed = True

    if int(queen_count) + int(king_count) + int(rook_count) + int(bishop_count) + int(knight_count) == 0:
        pieces_inputed = False

    if pieces_inputed:

        output = os.system("ChessCombinationEngine.exe 2 "+str(board_size)+" "+str(queen_count)+" "+str(king_count)+" "+str(rook_count)+" "+str(bishop_count)+" "+str(knight_count))
        
        if output < 0:
            output_frame.destroy()
            not_possible_label = Label(window,text="Not possible!",width = 33, height = 8, bg = "#ff9180",font=roboto16)
            not_possible_label.grid(row=9,column=6,columnspan = 4,rowspan=3,padx=20)

        else:
            output_frame.destroy()
            success_label = Label(window,text="Number of displayed layouts: "+str(output),width = 33, height = 8, bg = "#99ff9b",font=roboto16)
            success_label.grid(row=9,column=6,columnspan = 4,rowspan=3,padx=20)
    else:
        output_frame.destroy()
        fail_label = Label(window,text="Select pieces!",width = 33, height = 8, bg = "#ff9180",font=roboto16)
        fail_label.grid(row=9,column=6,columnspan = 4,rowspan=3,padx=20)

def startFirstPossibleLayout():
    board_size=board_size_option.get()[:1]
    queen_count = queen_count_option.get()
    king_count = king_count_option.get()
    rook_count = rook_count_option.get()
    bishop_count = bishop_count_option.get()
    knight_count = knight_count_option.get()

    pieces_inputed = True

    if int(queen_count) + int(king_count) + int(rook_count) + int(bishop_count) + int(knight_count) == 0:
        pieces_inputed = False

    if pieces_inputed:

        output = os.system("ChessCombinationEngine.exe 3 "+str(board_size)+" "+str(queen_count)+" "+str(king_count)+" "+str(rook_count)+" "+str(bishop_count)+" "+str(knight_count))
        
        if output < 0:
            output_frame.destroy()
            not_possible_label = Label(window,text="Not possible!",width = 33, height = 8, bg = "#ff9180",font=roboto16)
            not_possible_label.grid(row=9,column=6,columnspan = 4,rowspan=3,padx=20)

        else:
            output_frame.destroy()
            success_label = Label(window,text="Number of displayed layouts: "+str(output),width = 33, height = 8, bg = "#99ff9b",font=roboto16)
            success_label.grid(row=9,column=6,columnspan = 4,rowspan=3,padx=20)
    else:
        output_frame.destroy()
        fail_label = Label(window,text="Select pieces!",width = 33, height = 8, bg = "#ff9180",font=roboto16)
        fail_label.grid(row=9,column=6,columnspan = 4,rowspan=3,padx=20)

    

button_all_layouts = Button(window, text="View All",height=2,width=12,bg="#d5e4f7",font=roboto16, command=startAllLayouts).grid(row=9,column=5,pady=10)
button_first_combination_for_every_permutation = Button(window,text="View Some",height=2,width=12,bg="#dcf7d5", font=roboto16,command = startFirstlayoutsForEveryPermutation).grid(row=10,column=5)
button_first_combination = Button(window, text="View One",height=2,width=12,bg="#ffcda1",font=roboto16, command=startFirstPossibleLayout).grid(row=11,column=5,pady=10)

label_all_layouts = Label(window,text ="               Display all possible layouts -",font=roboto12).grid(row=9,column=0,columnspan=5,padx=10)
label_first_combination_for_every_permutation = Label(window,text ="Display combination for every permutation -",font=roboto12).grid(row=10,column=0,columnspan=5,padx=10)
label_first_combination = Label(window,text ="              Display first possible combination -",font=roboto12).grid(row=11,column=0,columnspan=5,padx=10)

output_label = Label(window,text ="Output:",font=roboto16).grid(row=7,column=7)
output_frame = Frame(window,width = 400, height = 200, bg = "#e8e8e8")
output_frame.grid(row=9,column=6,columnspan = 4,rowspan=3,padx=20)

instruction1_label = Label(window, text="Instructions:",font=roboto16)
instruction1_label.grid(row=12,column = 0,padx=20,pady=20)
instruction2_label = Label(window, text="-              Press Space to move forward",font=roboto12)
instruction2_label.grid(row=13,column = 0,padx=20,pady=5)
instruction3_label = Label(window, text="-  Press Backspace to move backward",font=roboto12)
instruction3_label.grid(row=14,column = 0,padx=20,pady=5)
instruction4_label = Label(window, text="-                       Press Enter to exit",font=roboto12)
instruction4_label.grid(row=15,column = 0,padx=20,pady=5)





window.mainloop()