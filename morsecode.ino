# Import necessary libraries
import tkinter as tk
from tkinter import Label, Entry, Button, Text, Scrollbar
import RPi.GPIO as GPIO
import time

# Morse code dictionary
morse_code_dict = {
    # Define Morse code mappings for letters, numbers, and space
    # Each letter is represented by a sequence of dots (.) and dashes (-)
    # Space is represented as a slash (/)
}

# LED configurations
led_pin = 18  # Specify the GPIO pin for the LED
GPIO.setmode(GPIO.BCM)  # Set the GPIO mode to use Broadcom SOC channel
GPIO.setup(led_pin, GPIO.OUT)  # Configure the GPIO pin for output

# Function to convert text to morse code
def convert_text_to_morse(text):
    morse_code = ""
    for char in text:
        if char in morse_code_dict:
            morse_code += morse_code_dict[char] + " "  # Add morse code for the character and space
        else:
            morse_code += ""  # Ignore characters not in the dictionary
    return morse_code

# Function to handle conversion, display results, and blink LED
def handle_conversion_display_and_blink():
    input_text = input_entry.get().upper()  # Get input text and convert it to uppercase
    morse_result = convert_text_to_morse(input_text)  # Convert input text to morse code
    output_text.config(state=tk.NORMAL)  # Enable the output text widget for editing
    output_text.delete("1.0", tk.END)  # Clear any previous text in the output text widget
    output_text.insert(tk.END, morse_result)  # Insert the morse code result into the output text widget
    output_text.config(state=tk.DISABLED)  # Disable the output text widget for editing
    
    # Blink the LED based on morse code
    blink_led_for_morse(morse_result)

# Function to blink the LED based on morse code
def blink_led_for_morse(morse_result):
    for symbol in morse_result:
        if symbol == ".":
            GPIO.output(led_pin, GPIO.HIGH)  # Turn on the LED for a dot
            time.sleep(0.6)  # Keep the LED on for a short duration (dot)
        elif symbol == "-":
            GPIO.output(led_pin, GPIO.HIGH)  # Turn on the LED for a dash
            time.sleep(0.6)  # Keep the LED on for a longer duration (dash)
        else:
            GPIO.output(led_pin, GPIO.LOW)  # Turn off the LED for space
            time.sleep(0.4)  # Keep the LED off for a short duration (space)
        GPIO.output(led_pin, GPIO.LOW)  # Turn off the LED after dot, dash, or space
        time.sleep(0.2)  # Pause between symbols

# Creating the main GUI window
root = tk.Tk()
root.title("Morse code converter")  # Set the title for the GUI window

# Creating widgets
input_label = Label(root, text="Type Something ")  # Create a label widget
input_entry = Entry(root)  # Create an entry widget for user input
convert_button = Button(root, text="Convert and Blink LED", bg='white', command=handle_conversion_display_and_blink)  # Create a button to trigger conversion and LED blinking
output_text = Text(root, height=5, width=30, wrap=tk.WORD, state=tk.DISABLED)  # Create a text widget for displaying morse code output
scrollbar = Scrollbar(root, command=output_text.yview)  # Create a scrollbar for the output text widget
output_text.config(yscrollcommand=scrollbar.set)  # Configure scrollbar to control the output text widget's scrolling

# Arrange widgets in the window using pack() method
input_label.pack()  # Pack the input label widget
input_entry.pack()  # Pack the input entry widget
convert_button.pack()  # Pack the convert button widget
output_text.pack()  # Pack the output text widget
scrollbar.pack(side=tk.RIGHT, fill=tk.Y)  # Pack the scrollbar widget

root.mainloop()  # Start the main GUI event loop
GPIO.cleanup()  # Cleanup and release GPIO resources when the GUI window is closed

