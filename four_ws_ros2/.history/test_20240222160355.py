class NPC():
    def __init__(self, weight, height):
        self.weight = weight
        self.height = - height

    def say(self):
        print(self.color)

    def pour(self):
        print("把水倒出來")


cup1 = Cup("blue")
cup2 = Cup("red")

cup1.say()
cup2.say()
