class NPC():
    def __init__(self, weight, height):
        self.weight = weight
        self.height = height

    def say(self):
        print(self.weight)
        print(self.height)


Tom = NPC(170, 100)
Mark = NPC(50,)

Tom.say()
Mark.say()