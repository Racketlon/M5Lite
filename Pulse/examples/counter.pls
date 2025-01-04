App "Counter":

label counter_label:
    position: center, 100
    font_size: 20
    text: 0

button increment_button:
    position: center, 200
    size: 150, 40
    text: "Increment"
    fn on_click():
        counter_label.text += 1

button reset_button:
    position: center, 300
    size: 150, 40
    text: "Reset"
    fn on_click():
        counter_label.text = 0
