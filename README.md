# Choice-Machine

The following program is designed to aid the user in completely ranking a list of items.
It is derived from the DragonFly Cave's Favorite Pokemon Picker, using the same fundamental method of "this or that" style questions.

The logic works as follows:

At all times, there are three lists that are being tracked.
1. "winners", a list of the favorites that are known.
2. "Ns", a storage space for every item that is a candidate for the next spot on winners
3. "eliminated", a storage space for every item that has been eliminated by another item.

The program will continually ask the user "this or that" style questions, using items from Ns.
The item that is not chosen is moved to eliminated, and marked with the id of the item that was chosen.
Once Ns only has one item, that item is the only valid candidate and is moved to winners.
Then, every item that was eliminated by the winner is brought back to Ns from eliminated, and they compete for the next spot on winners.

Conisder this:
Coca Cola and Saranac Root Beer are both candidates for third place in a user's ranking of soda.
The program asks "Coca Cola OR Root Beer?" and the user says Coca Cola.
The program can now infer that it is impossible for root beer be the third place item, so it moves it to eliminated.
Coca Cola eventually makes it into the list, at fifth place. At this point, the program returns root beer to the table, since it IS a candidate for sixth place.

I have written up two versions of this code:
app.js, index.html, and cabin.ico come together to form a website that can rank a few, preset lists.
Choice_python.py is a simple python program that runs choices, but isn't very user-friendly
PKMN.cpp, SMUSUM.cpp, and POKE.h come together to form a C++ project; when compiled it can rank any possible list much more freely, though with a limited UI.

The python version came first. The C++ version expanded the project and made it user-friendly. The JS version was created to make things easier to port. ReadMe.txt gives some more information into the C++ version.




