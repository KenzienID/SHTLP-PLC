# Python code
#

def on_forever():
  led.plot_bar_graph(input.temperature(), 50)
  pins.servo_write_pin(AnalogPin.P2, (input.temperature() + 69))
basic.forever(on_forever)
