import serial
import customtkinter as ctk

# Open serial communication (modify 'COM3' to match your Arduino's COM port)
arduino_serial = serial.Serial('COM6', 9600, timeout=1)  # Adjust COM port and baud rate if necessary

# Function to send the left command
def send_left_command(event):
    arduino_serial.write(b'L')  # Send 'L' to Arduino
    print("Sent 'L' to Arduino")

# Function to send the right command
def send_right_command(event):
    arduino_serial.write(b'R')  # Send 'R' to Arduino
    print("Sent 'R' to Arduino")

# Main function for the car control app
def carControlApp():
    ctk.set_appearance_mode("dark")
    ctk.set_default_color_theme("blue")

    window = ctk.CTk()
    window.geometry("400x300")
    window.title("Servo Control App")

    label = ctk.CTkLabel(window, text="Servo Control App", font=("Arial", 20))
    label.pack(pady=20)

    status_label = ctk.CTkLabel(window, text="Press left or right arrow keys", font=("Arial", 16))
    status_label.pack(pady=10)

    # Bind arrow keys to corresponding commands
    window.bind("<Left>", send_left_command)
    window.bind("<Right>", send_right_command)

    exit_button = ctk.CTkButton(window, text="Exit", command=window.quit)
    exit_button.pack(pady=20)

    window.mainloop()

# Start the application
carControlApp()
