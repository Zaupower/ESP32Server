class Machine:
    def __init__(self, id, name):
        self.id = id
        self.name = name
        f = open("demofile3.txt", "a")
        f.write(self.name + " " + self.id)
        f.close()
