class NPC():
    def __init__(self, weight, height):
        self.weight = weight
        self.height = height

    def say(self):
        print(self.weight)
        print(self.height)


Tom = NPC("blue")
cup2 = NPC("red")

cup1.say()
cup2.say()
