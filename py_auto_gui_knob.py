import pyautogui, sys
import serial

ser = serial.Serial('COM4', 115200, timeout=1)

value = 0


class Coords:
    decrease_button_x = 0
    decrease_button_y = 0
    increase_button_x = 0
    increase_button_y = 0
    button_x = 0
    button_y = 0


def set_coords():
    box = pyautogui.locateOnScreen("increase_button.png", confidence=.8)
    button_point = pyautogui.center(box)
    print(button_point)
    Coords.increase_button_x, Coords.increase_button_y = button_point


    box = pyautogui.locateOnScreen("decrease_button.png", confidence=.8)
    button_point = pyautogui.center(box)
    print(button_point)
    Coords.decrease_button_x, Coords.decrease_button_y = button_point

    box = pyautogui.locateOnScreen("change_button.png", confidence=.8)
    button_point = pyautogui.center(box)
    print(button_point)
    Coords.button_x, Coords.button_y = button_point


def click_button(image):
    box = pyautogui.locateOnScreen(image, confidence=.8)
    button_point = pyautogui.center(box)
    print(button_point)
    button_x, button_y = button_point

    pyautogui.click(button_x, button_y)


def click_increase():
    pyautogui.click(Coords.increase_button_x, Coords.increase_button_y)

def click_decrease():
    pyautogui.click(Coords.decrease_button_x, Coords.decrease_button_y)

def click_main_button():
    pyautogui.click(Coords.button_x, Coords.button_y)

old_value = 0

set_coords()

try:
    while True:

        serial_val = ser.readline()
        # print(serial_val)
        serial_val = str(serial_val).split("'")[1].split("\\r")[0]

        # x, y = pyautogui.position()
        # positionStr = 'X: ' + str(x).rjust(4) + ' Y: ' + str(y).rjust(4)
        # print(positionStr, end='')

        if serial_val.__len__() >= 1:

            if serial_val == "Pressed":
                click_main_button()


            else:
                value = float(serial_val)

                if old_value < value:
                    old_value = value
                    click_increase()

                elif old_value > value:
                    old_value = value
                    click_decrease()

            # click_button('windows_button.png')
            # print(serial_val)

        # pyautogui.moveTo(100+30*value, 200)

        # print('\b' * len(positionStr), end='', flush=True)
except KeyboardInterrupt:
    print('\n')
