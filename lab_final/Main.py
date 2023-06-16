import pickle
from sklearn.feature_extraction.text import TfidfVectorizer
from joblib import load
import monpa
import Jetson.GPIO as GPIO

model = load('TZUYI/Voice/Priority_Recognition.joblib')

GPIO.setmode(GPIO.BOARD)
GREEN_LED_PIN = 297 
GPIO.setup(18, GPIO.OUT, initial=GPIO.LOW)

class GPIOController:
    def __init__(self, pin):
        self.led = pin

    def init_gpio_things(self):
        self.gpio_export()
        self.gpio_set_dir("out")
        self.gpio_set_value("0")

    def gpio_unexport(self):
        try:
            with open("/sys/class/gpio/unexport", "w") as file:
                file.write(str(self.led))
            return 0
        except Exception as e:
            print("gpio/unexport:", e)
            return -1

    def gpio_export(self):
        try:
            with open("/sys/class/gpio/export", "w") as file:
                file.write(str(self.led))
            return 0
        except Exception as e:
            print("gpio/export:", e)
            return -1

    def gpio_set_dir(self, direction):
        try:
            path = f"/sys/class/gpio/gpio{self.led}/direction"
            with open(path, "w") as file:
                file.write(direction)
            return 0
        except Exception as e:
            print("gpio/direction:", e)
            return -1

    def gpio_set_value(self, value):
        # try:
        #     path = f"/sys/class/gpio/gpio{self.led}/value"
        #     with open(path, "w") as file:
        #         file.write(value)
        #     return 0
        # except Exception as e:
        #     print("gpio/set-value:", e)
        #     return -1
        print(value == "1")
        GPIO.output(18, value == "1" )

    def cleanup(self):
        # self.gpio_set_value("0")
        self.gpio_unexport()


class RecgWords:
    def __init__(self):
        with open('TZUYI/Voice/train_final.pickle', 'rb') as file1:
            train_dataset = pickle.load(file1)
        self.tfidf_vect = TfidfVectorizer(ngram_range=(1, 2))
        train_text = train_dataset['retext']
        self.tfidf_vect.fit(train_text)

        self.stopWords = []
        with open('TZUYI/Voice/NEW_stopwords.txt', 'r',
                  encoding='UTF-8') as file:
            for data in file.readlines():
                data = data.strip()
                self.stopWords.append(data)

    def clean_seg(self, sentence):
        result_cut_batch = monpa.cut_batch(sentence)
        seg = []
        for item in result_cut_batch:
            seg.extend(item)
        seg = ' '.join(seg)
        seg = str(seg).split(" ")
        seg = ' '.join([word for word in seg if word not in self.stopWords])
        return seg

    def recognition(self, output_label):
        gpio_controller = GPIOController(GREEN_LED_PIN)
        print(output_label, gpio_controller.led)
        gpio_controller.init_gpio_things()
        gpio_controller.gpio_set_value(str(output_label))
        
        # Add additional logic here if needed
        gpio_controller.cleanup()


def main():
    recg = RecgWords()
    user_input = input("Please enter patient complaint: ")
    seg = recg.clean_seg(user_input)
    vectors_test = TfidfVectorizer(vocabulary=recg.tfidf_vect.vocabulary_).fit_transform([seg])
    output_label = model.predict(vectors_test)[0]
    recg.recognition(output_label)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        GPIO.cleanup()
