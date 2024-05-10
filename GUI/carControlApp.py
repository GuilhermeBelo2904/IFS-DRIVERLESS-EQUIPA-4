import time
import serial
import customtkinter as ctk

# Initialize the serial port with a lower baud rate to ensure compatibility
# Baud rate 115200 is typically fine with Arduino Uno
arduino_serial = serial.Serial('COM6', 9600, timeout=0.1)  # Adjust the baud rate and timeout

# Function to send a command
def send_command(command):
    arduino_serial.write(command)
    print(f"Sent '{command.decode()}' to Arduino")

# Functions to send specific commands
def send_left_command(event):
    send_command(b'L')

def send_right_command(event):
    send_command(b'R')
    
def send_forward_command(event):
    send_command(b'F')
    
def send_backward_command(event):
    send_command(b'B')
    
def send_stop_command(event):
    send_command(b'S')
    
def send_automatic_mode_command(event):
    send_command(b'A')
    print("Switched to automatic mode")
    
def send_manual_mode_command(event):
    send_command(b'M')
    print("Switched to manual mode")
    
def send_exit_mode_command(event):
    send_command(b'E')        
    print("Exiting the choosen mode...")    

# Main function for the car control app
def carControlApp():
    ctk.set_appearance_mode("dark")
    ctk.set_default_color_theme("blue")

    window = ctk.CTk()
    window.geometry("400x300")
    window.title("Car Control App")

    label = ctk.CTkLabel(window, text="Car Control App", font=("Arial", 20))
    label.pack(pady=20)

    status_label = ctk.CTkLabel(window, text="Use arrow keys to control the car", font=("Arial", 12))
    status_label.pack(pady=10)

    # Bind arrow keys to corresponding commands
    window.bind("<Left>", send_left_command)
    window.bind("<Right>", send_right_command)
    window.bind("<Up>", send_forward_command)
    window.bind("<Down>", send_backward_command)
    window.bind("<space>", send_stop_command)
    window.bind("<a>", send_automatic_mode_command)
    window.bind("<m>", send_manual_mode_command)
    window.bind("<e>", send_exit_mode_command)

    exit_button = ctk.CTkButton(window, text="Exit", command=window.quit)
    exit_button.pack(pady=20)

    window.mainloop()

# Start the application
carControlApp()
