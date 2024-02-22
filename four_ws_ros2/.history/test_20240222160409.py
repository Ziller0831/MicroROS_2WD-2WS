class NPC():
    def __init__(self, weight, height):
        self.weight = weight
        self.height = height

    def say(self):
        print(self.weight)
        print(self.height)



cup1 = Cup("blue")
cup2 = Cup("red")

cup1.say()
cup2.say()
