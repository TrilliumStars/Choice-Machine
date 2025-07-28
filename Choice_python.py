import random
#The following program is designed to Aid the user in selsectively ranking a list of items
#Using a This or That form of questioning, the user


class Node:#A node contains a single item, and all of the items that is has removec
    id = ""#The identifier of the node
    elim = []#The list of all other eliminated nodes
    def __init__(self,ID):
        self.id = ID
        self.elim = []
    def __str__(self):
        return(self.id)
    
def routine(Ns):
    if(len(Ns)==1):
        return 1#If there is a winner, return 1
    else:
        a = random.randrange(len(Ns))#Generate two nodes from the list of available nodes
        b = random.randrange(len(Ns))
        while(b == a):
            b = random.randrange(len(Ns))#Make sure there are no duplicates
        a = Ns[a]
        b = Ns[b]
        print("\"" + a.id + "\" or \"" + b.id + "\"")#Prompt the user for a node
        g = input()
        if(g == '1'):#Perform the appropriate action
            Ns.remove(b)
            (a.elim).append(b)
        elif(g == '2'):
            Ns.remove(a)
            (b.elim).append(a)
        else:
            print("Sorry! I couldn't understand that. Let's try again!")
        return 0


print("The following program is designed to Aid the user in selectively ranking a list of items")
print("You will be shown items in a 'This or that' form.")
print("type '1' to choose the item on the left, and type '2' to choose the element on the right")
print("Ready? Let's begin.")
print("")
#L = ["That's NOT supposed to Happen","Two legs, how I've missed you!","The feeling of Nostalgia","road trip!","Another one of those Human Hunters","Decisions, decisions","Are you even my partner anymore?","Sensory Overload"]
L = ["Primarina","Suicune","Walking Wake","Brionne","Lumineon","Spheal","Samurott","Popplio"]
#L = ["Apple","Banana","Cucumber","Dragonfruit","Elderberry","Fruit Punch","Grape"]
#L = ["Home","Work","School","Camp","Beach","Campus","International","Neighbor's","Forest"]
NN = []
for i in range(len(L)):
    NN.append(Node(L[i]))
for i in range(len(NN)):
    (NN[i]).elim = []
Winners = []
while(len(Winners) < len(L)):
    while(routine(NN) == 0):
        i = 0
    g = NN[0]
    Winners.append(g)
    NN.remove(g)
    for i in range(len(g.elim)):
        NN.append(g.elim[i])
for i in range(len(Winners)):
    print(f"{i+1}) {Winners[i]}")





    