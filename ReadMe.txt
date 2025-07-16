Welcome to the Selective Choice machine!
This program is designed to assist a user in determining their favorite item on a list of items.
It will work perfectly for ranking your favorite princesses, endings, or voices!

---TL;DR---
Press 0 and enter to start the program
then 1 and enter for default list
then 3, 4, or 5 for the Princess lists
The program will continuously ask you "this or That" with princesses, voices, or endings.
Choose this by pressing 1 or choose that by pressing 2.
Once you're done, it will show you your ranked list!


---FAQ---
Ask a question in the commments, and I'll reply to you then put the answer in here for other users.


---The basic concept---
There are three lists at all times:
winners, current, and eliminated.
All items start in the current list.
The program will keep asking you "this or that" questions using items in the current list.
The item you don't choose gets "eliminated." This is because it's impossible for that item to be your favorite.
Once there is only 1 item left in current, it gets moved to winners. Congrats! You found a favorite!
The program will then "un-eliminate" everything that was eliminated by the new favorite. These items then fight for second place.
It repeats until Winners is full, and both current and eliminated are empty.
Now, you have a fully ranked list, from most favorite to least!
More information as follows:


---starting the program---
When you start the program, it will ask you to type the number 0 and press enter.
This is mostly so that users unfamiliar with the C++ terminal will understand the process of inputting choices to the program
If you do not press 0, it will kick you out.
Next, the program will give you 4 options
1: use a default list. 
I have twelve different default lists right now. Some are just my lists, but 3 of them, the Slay the Princess lists, will be relevant to you.
2: make your own list
This will allow you to type out the names of your own list in order to rank a completely customly made list. Note that making a new list will NOT add it to the defaults
3: Import list
This will allow you to "load your progress" using a save code that the program gives you. To get one of these save codes, press 'x' during the normal operations of the program.
4: how does this work?
This will explain the basics of how my program works and what the three list options mean.


---Choosing Favorites---
Repeatedly, the program will ask you to choose which you like more between two options.
Press 1 to choose the left, and 2 to choose the right.
You will keep being given choices until you succesfully rank the entire list.
If you enter something other than 1 or 2, I will execute one of the special options


---special options---
You can also, rather than choosing an item, perform one of many special options by pressing:
q - View all the special options
p - displays your favorites list, your not yet chosen list, and your eliminated list.
e - shows your progress by Estimating how many choices you have left. 
z - UNDO. It remembers up to 5 choices in the past.
r - more advanced version of undo. It will allow you to search for a specific item. If it is eliminated, you can rescue it. If it's already on your favorites list, you can push it back down to choosing.
w - Rearranges your favorites list. Useful if you change your mind later
x - SAVE. The program will give you a save code to copy. You can paste it either 1. at the start of the program, choose "import list", or 2: press 'i' during normal operations of the program
i - LOAD. Will load a save code you copied when pressing x.
d - DELETE. Allows you to permanently delete an item you don't like. You will never see it again. (items that were eliminated by it are not lost)
a - Adds a completely new item to the list.
Note: using the combination of a and d, you can manipulate the list to your will.
For example, I have the wild as a single element on this list. If you wanted to change that, you could run the commands:
d wild
a wounded wild
a networked wild
m - ELIMINATE. Normally, items are eliminated when you choose one over the other. This function lets you manually eliminate an item.
c - END. This will prematurely finish the rankings with a half-ranked list. If you only want your top 10 or 20, use this when you reach that mark.
If you enter anything else, the program will skip this choice and generate a new choice.


---cleanup and finish---
Once you completely rank your list, the program will display it to you. Feel free to copy-paste!
Then, it will ask you if you want to rearrange it, making and last-minute changes. This works exactly the same way the 'w' command does.
Then, it will give you a save code for your fully ranked list.
Finally, it will ask you to enter a single number to end the program. Once you do that, it will close the window, so make sure to copy-paste your List OR your save code before you do this!






/*---Data Types---
--story--
When I say "item" I am almost always reffering to a data type called a "Story"
A story is a struct that has two data members:
id - a string that the story is known as
elim - a pointer to another story.
id is used for when something is needed to be printed to the screen.
the elim in the eliminated items will alwasy point to the story that eliminated them.
(All elim on the Ns and winners list will be NULL)
--Node--
Each list is implemented in a node-based singly linked list.
A Node contains two things:
S - a pointer to the associated story
link - a pointer to the next node in the list.
These are pretty standard for a linked list.
--LIST--
The LIST is implemented using a Node-based singly linked list.
Each Node points to another Node, except for the last one on the list.
public:
int length = 0; - The number of items in the list
Node* first = NULL; - A pointer to the first node in the list
Node* last = NULL; - A pointer to the second Node of the list
void insert(story* s); - will create a new node at the end of the list, and point that node to the given story
void remove(int loc); - removes the node at the given location (first = 0, last = length - 1), and conforms the rest of the list around it.
int search(std::string L); - Searches the list based on the given string, comparing with each story. Will return the location of the item, or -1 if it is not found.
story* fetchStory(int loc); - Retrieves the story at the given location on the list
void print(); - prints off the list
void rearrange(); - an interactive program that allows the user to rearrange the list at will
void shallow_delete(); - Deletes all the nodes in the list, and itself
void deep_delete(); - Deletes all the node in the list, itself, and all of the stories that the nodes pointed to.
private:
Node* traverse(int loc); - Returns the Node at the given location on the list

Notably, length, first, and last are public data members, which is quite unusual for a list.
I use this to my advantage and occasionally manipulate the lists in the middle of the code.
--IMPORT and EXPORT--
One of the greatest challenges of this program was allowing the user to import and export the state of the choosing.
You can see the remains of my first attempt in the functions that are labeled as "Not used in the final project"
This is true.
The modern IMPORT and EXPORT functions behave very simply:
IMPORT will print to the screen:
The length of the three lists, respectively,
all of the names of items, with spaces replaced with underscores,
and then the locations that all of the eliminated stories pointed to.
This is very easy for the program to interpret, which is a good change of pace from the failed attempts.
The User will copy this string, and paste it at a later time.

---int main()---

---Lines 9 to 27---
This bars what I like to call "debug mode"
In reality, all it does is call the interpret() function
(The passcode is "3.141")
--Interpret--
The interpret function has one primary use: to help the developer create new default lists.
Just enter the names of all of the items (even with spaces), and end with a -1.
it will give you a line of text to paste into the code. NOTE: There are more steps. See "using a deafult list"

---Lines 28 to 184---
This is what I like to call the 'BIOS' of the program. It sets everything up for the actual function.
There are three ways to start the program:
--using a default list--
This creates a lot of data, and then selectively fills Ns with the data that the user wants.
If you would like to add something to the default list, perform the following steps:
1. Create a vector containing the names of all of your items. Put it with the other vectors.
2. Increase the static int Q by 1.
3. Add your vector to the end of N
4. change the message sent to the user to include your list, with a short description.
That's it!
Subsequently, if you dislike one of my lists, follow these same steps in reverse.
--Making your own list--
This runs very similarly to the interpret() function.
The User will list off all of the elements they want to rank, and end with a -1.
Then, it jumps right into the choosing.
--Import a list--
This pairs right with the IMPORT and EXPORT functions.
When you EXPORT, you'll want to paste all of that text right here.

---lines 195 to 209---
This part is fairly simple.
It will present the user with two items, randomly chosen from the list, and prompts the user for an input.
What it does with that input can greatly vary:
--'1' or '2'--
The program will take the item that was not chosen, remove it from Ns, add it to eliminated, and point its 'elim' towards the item that was chosen
--'z'--
The program will attempt to undo the user's previous action
It uses a list, Z, to store the previous 5 actions at a time.
when you call the undo function, it will look to the last member of Z, and it is brought back to Ns.*/