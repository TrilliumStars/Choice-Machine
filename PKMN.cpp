#include <random>
#include <ctime>
#include "POKE.h"
using namespace std;
//TODO LIST:
//find some way to mitigate the problem with having too many variables in a List.


void A() {//this function will wait 1 second, doing nothing.
	time_t c = time((0));
	//while (time(0) == c) {}//comment out this line to skip all waiting time in the program.
}
bool main() {//The main function of the program. It's a bool because Why Not?
	cout << "Type the number '0' and press enter to begin the program" << endl;
	int j = 0;
	INPUT(j);
	if (j) {//A tool to help the developer
		interpret();
		return 0;
	}
	textblock(2);//introduce the user
	LIST Ns;//List to store elements currently being chosen
	LIST eliminated;//list to store eliminated items
	LIST winners;//List to store stories that have won
	int G = 0;//Number of items being ranked
	char imput = '1';string lol = "";story* L = NULL;//general use variables
	cout << B(5) << "To start, what list would you like to rank:\n1: Use one of the default lists\n2: Make your own list\n3: Import list\nq: How does this work?\n";
	cin >> imput;
	if (imput == 'q') {//provide the user with basic information
		textblock(0);
		cin >> imput;

	}
	if (imput == '3') {//resume the choosing from a List the User imports
		Cencrypt::IMPORT(winners, Ns, eliminated);
		G = winners.L() + Ns.L() + eliminated.L();
		A();
		cout << "Note: If some of the names look a little wierd, type 'n' to rename them" << endl;
		A();
	}
	else
		setup(Ns, G, imput);//The other two options for choosing
	LIST Z(5);//A list to store previous actions; Has a maximum length of 5.
	if (winners.L() != G)
		//cout << "(This will take, on average, " << (floor(pow(((G - 1) - winners.L()), 1.323)) - eliminated.L()) << " choices)" << endl;B(2);
		cout << "(This will take, on average, " << (es(G - winners.L()) - eliminated.L()) << " choices)" << endl;B(2);//estimate choices left
	while (winners.L() < G) {//A loop to perform the choosing; each iteration should introduce 1 new winner. Ends when all items have been chosen

		imput = '0';j = 0;L = NULL;//initialize the control variables, just in case

		while (Ns.L() > 1 && G != -1) {//The loop of choosing; each iteration will either perform a special action or eliminate 1 item.
			Loop(winners, Ns, eliminated, Z, G, L);
		}

		if (G == -1)//The escape sequence to end the program early.
			break;

		L = Ns.pop(0);//the winning story
		restore(Ns, eliminated, L);//restore everything eliminated by that story
		winners.insert(L);//select this story as a winner
		Z.insert(L);//add to the UNDO
		if (winners.L() == 1) {//A message that displays when the first item is aded to winners
			cout << B() << "\nCongrats! You found your favorite thing on the list: " << winners.fetchStory(0)->id <<"!"<< endl;
			cout << B(2) << "If you want to end here, type 'c'. Otherwise, let's keep ranking the rest of them!\n" << endl;
			B(2);
		}
	}
	if (G != 0) {//COA when the list is fully chosen
		Z.shallow_delete();//deallocate the Undo List
		cout << "\nCongratulations! You finished choosing!\n\n";
		winners.winprint();//show the rankings
		cout << "\n\nWould you like to rearrange this list? Type 0 to end, 1 to rearrange\n";
		INPUT(j);
		if (j)
			winners.rearrange();//one last chance to move things around
		cout << "Okay, then. Thanks for using the selective choice machine!" << endl;
		cout << "Feel free to take a screenshot or copy-paste, before the program terminates." << endl << B(2);
		cout << B(2) << "\nIf you ever want to use this list again, here's a save code:" << endl;
		B(2);
		Cencrypt::EXPORT(winners, Ns, eliminated);//A save code for the user just in case
		cout << "\n\nMake sure to Copy-paste this block of text" << endl;
		cout << B(2) << "The next time you start the program, choose \'import list,\' then paste this" << endl;
		textblock(3);
		winners.deep_delete();//deallocate all memory
		Ns.deep_delete();
		eliminated.deep_delete();
		return 0;
	}
	//message if the list was empty
	cout << "Sorry, it looks like there was nothing to rank!" << endl;
	cout << B() << "Terminating the program in three seconds.";
	B(3);
	return static_cast<bool>('?');//return 1;
}


void setup(LIST& Ns, int& G, char imput) {//The setup function of the program. Will initialize the Lists per user request
	story* L;
	if (imput == '2') {//Protocol for generating a custom list
		cout << "Please enter the names of all the items in the list. End with a -1" << std::endl;
		cout << B() << "Special characters other than -_,.':/() are not recognized by the program, and will be replaced with spaces." << endl;
		string y;
		while (y != "-1") {
			INPUT(y);
			if (y != "-1") {
				//get the string
				L = new story;//make the story
				L->elim = NULL;
				L->id = y;
				Ns.insert(L);//insert into the list
			}
			else {
				break;//escape sequence
			}
		}
		L = NULL;
		G = Ns.L();//G is the number of items being chosen
		cout << "\nIf you want to save this list, press x, then enter. It will give you a block of text to copy." << endl;
		if (G > 255) {
			textblock(6);//A warning in case the user puts too many items in a list
		}
		cout << B(2) << "Next time you start the program, use the \'import list\' option, and paste this data." << endl;
	}
	else {
		if (imput != '1') {//default
			cout << "I don't understand your input. So let's just use a default list." << endl;
		}
		//Set up all of the different lists

		


		//If you want to add more lists:
		//1: create a vector <string> that has the names of all of your items
		//2: Increment Q
		//3: Add your vector to the default_vector() function for the new unused value
		//4: update the displayed message with a brief description of your list in textblock(5)
		const int Q = 12;//The number of valid lists
		textblock(5);
		int j = 0;
		INPUT(j);
		while (j > Q || j == 0) {//ensure that there is a valid input
			if (j == 0) {//debug mode: will automatically generate a list
				cout << "Entering debug mode. Please enter the password to confirm you are the developer." << endl;
				if (password()) {//prevent normal users from accessing the debug list generation
					cout << "Wrong password. Womp womp. Please enter a valid number next time" << endl;
					A();
				}
				else {
					j = -1;break;
				}
			}
			cout << "that's not a valid number. Try again!" << endl;
			INPUT(j);
		}
		if (j == -1) {//the automatically generated list
			cout << "How long would you like the list to be?" << endl;
			cin >> G;
			cout << "How long would you like the items to be?" << endl;
			int kap;
			INPUT(kap);
			string kalpho;
			for (int i = 0; i < kap; i++) {
				kalpho += "0";
				kalpho[i] = static_cast<char>(32 + rand() % 94);//randomized string
			}
			for (int i = 0; i < G; i++) {
				L = new story;
				while (Ns.search(kalpho) != -1) {
					kalpho[rand() % kap] = static_cast<char>(32 + rand() % 94);//make sure each string is different
				}
				L->id = kalpho;
				L->elim = NULL;
				Ns.insert(L);
			}
		}
		else {
			vector<string> N = default_lists(j);//fetch the default list in question
			G = N.size();
			for (int i = 0; i < G;i++) {//fill Ns with all of the items
				L = new story;
				L->id = N[i];
				L->elim = NULL;
				Ns.insert(L);
			}
		}
		L = NULL;

	}
}
void Loop(LIST& winners, LIST& Ns, LIST& eliminated, LIST& Z, int& G, story* &L) {//This function is called many times in the program, and is how the user manages their ist
	string y;
	int a;int b;
	story* A;story* B;
	if (Ns.L() > 2) {//fetch two different storeis
		a = rand() % Ns.L();
		A = Ns.fetchStory(a);
		while (A == L) {//find a story that was not used in the previous choice
			a = rand() % Ns.L();
			A = Ns.fetchStory(a);
		}
		B = getstory(Ns, A, L);//ensure no duplicates
		b = Ns.search(B);
	}
	else {//if there are only two choices, we only have one option
		a = 0;
		A = Ns.fetchStory(a);
		b = 1;
		B = Ns.fetchStory(b);
	}
	cout << "\"" << (A == NULL ? "ERROR!" : A->id) << "\" or \"" << (B == NULL ? "ERROR!" : B->id) << "\" (1 or 2) (or q to view special options)\n";//present a choice to the user
	char imput = '0';
	cin >> imput;//input that choice
	//imput = rand() % 2 + '1';//randomized choice
	switch (imput) {
	case'q'://provide the user with more information
		textblock(1);
		break;
	case 'e'://estimate the User's progress. It is impossible to predict exaclty how many choices will be required.
		cout << "You have already ranked " << winners.L() << " of " << G << " items in the list" << endl;
		//cout << "You have " << Ns.L() - 1 << " choices until your next favorite is added to the list" << endl;
		//cout << "I estimate that you need " << (floor(pow(((G - 1) - winners.L()), 1.323)) - eliminated.L()) << " more choices in order to finish choosing." << endl;
		cout << "I estimate that you need " << (es(G - winners.L()) - eliminated.L()) << " more choices in order to finish choosing." << endl;
		
		break;
	case '1'://eliminating the second element
		Ns.remove(b);
		eliminated.insert(B);
		B->elim = A;
		Z.insert(B);
		L = A;//make sure A doesn't appear next round
		break;
	case '2'://eliminating the first element
		Ns.remove(a);
		eliminated.insert(A);
		A->elim = B;
		Z.insert(A);
		L = B;//make sure B doesn't appear next round
		break;
	case 'D'://A debug mode, for developer usage
		if (password()) {
			cout << "Wrong password, lol" << endl;
			break;
		}
		winners.debug();
		Ns.debug();
		eliminated.debug();
		break;
	case 'R':
		if (password()) {
			cout << "Wrong password, lol" << endl;
			break;
		}
		winners.deep_delete();
		Ns.deep_delete();
		eliminated.deep_delete();
		Z.shallow_delete();
		setup(Ns, G, '1');
		break;
	case 'z'://undoing the user's previous choice
		Undo(winners, Ns, eliminated, Z);
		break;
	case 'd'://remove an item from the list
		cout << "What is the name of the item you would like to delete? (type NULL to cancel)" << endl;
		INPUT(y);
		if (y == "NULL") {
			cout << "Cancelling delete" << endl;
			break;
		}
		del(winners, Ns, eliminated, Z, y, G);
		break;
	case 'a'://add a new element to the list
		cout << "what would you like to call this new item? (type NULL to cancel)" << endl;
		INPUT(y);
		if (y == "NULL") {
			cout << "Cancelling addition" << endl;
			break;
		}
		if (Ns.search(y) != -1 || winners.search(y) != -1 || eliminated.search(y) != -1) {//warn the user if there is a duplicate
			cout << "It looks like " << y << " is already an item on this list. Would you like to add a second copy? (1 = yes, 0 = cancel)" << endl;
			cin >> imput;
			if (imput != '1')
				break;
		}
		L = new story;
		L->id = y;
		G++;
		Ns.insert(L);
		L = NULL;
		cout << "Succesfully Added" << endl;
		if(G > 255)
			textblock(6);
		break;
	case 'p'://display information for the user
		std::cout << "\nwinners:\n";
		winners.winprint();
		std::cout << "\nCurrently being chosen:\n";
		Ns.print();
		cout << "\nEliminated:\n";
		eliminated.elimprint();
		cout << endl;
		break;
	case 'r'://attempt to rescue an item
		cout << "Which Item would you like to rescue?" << endl;
		INPUT(y);
		Rescue(winners, Ns, eliminated, y);
		break;
	case 'w'://rearrange the winners list
		if (winners.L() <= 1) {//prevent crashes
			cout << "You can't rearrange a list that small" << endl;
		}
		else {
			winners.rearrange();
			Z.shallow_delete();//Z will act weird if we don't flush it first.
		}
		break;
	case 'i'://import a saved state
		Z.shallow_delete();
		Cencrypt::IMPORT(winners, Ns, eliminated);
		G = winners.L() + Ns.L() + eliminated.L();
		if (Ns.L() == 0) {
			G = -1;//prevent crashes if the List is already fully chosen
		}
		break;
	case 'x'://export the save state
		cout << "Exporting Data..." << endl;
		cout << wait(1) << "..." << endl;
		cout << wait(1);
		Cencrypt::EXPORT(winners, Ns, eliminated);
		cout << "\n\n\n\n";
		break;
	case 'c'://prematurely end the choosing
		cout << "Are you sure you would like to prematurely end the program?" << endl;
		cout << wait(1) << "type ^ and enter to confirm, or anything else to cancel" << endl;
		cin >> imput;
		if (imput == '^')
			G = -1;
		else
			cout << "Resuming loop" << endl;
		break;
	case 'n':
		rename(winners, Ns, eliminated);
		break;
	case 'm'://manually eliminate an item
		cout << "Which item would you like to eliminate?" << endl;
		INPUT(y);
		if (manelim(y, Ns, eliminated)) {
			cout << "Succesfully eliminated" << endl;
		}
		break;
	default://default
		cout << "Let's skip that one.\n";
		L = NULL;
		break;
	}
}
void Undo(LIST& winners, LIST& Ns, LIST& eliminated, LIST& Z) {//will undo the item of the User's choice
	if (Z.L() != 0) {
		story* L = Z.fetchStory(Z.L() - 1);
		int u = eliminated.search(L);
		if (u != -1) {//if the item was eliminated
			eliminated.remove(u);
			L->elim = NULL;
			Ns.insert(L);
			Z.remove(Z.L() - 1);
			cout << "Returned \"" << L->id << "\" to the choosing table (from Eliminated)\n";
		}
		else {
			u = winners.search(L);
			if (u != -1) {//if the item was chosen as a favorite
				winners.remove(u);
				L->elim = NULL;
				Ns.insert(L);
				Z.remove(Z.L() - 1);
				cout << "Returned \"" << L->id << "\" to the choosing table (from Winners)\n";
			}
			else {//default
				cout << "\"" << L->id << "\" is already in the choosing table. No worries!" << endl;
				Z.remove(Z.L() - 1);
			}
		}
	}
	else {
		cout << "Sorry, you can't undo any more. Use the 'r' function for more help." << endl;
	}
}
void del(LIST& winners, LIST& Ns, LIST& eliminated, LIST& Z, string y, int& G) {//A function to delete an item from the list
	cout << "looking for item " << y << "..." << endl;
	int u = eliminated.search(y);
	story* L = NULL;
	if (u != -1) {//if the item has been eliminated
		L = eliminated.pop(u);
		restore(Ns, eliminated, L);//restore anything eliminated by L
		u = Z.search(y);
		if (u != -1) {
			Z.remove(u);//make sure it's gone from Z
		}
		delete L;
		G--;
		cout << "succesfully removed" << endl;
	}
	else {
		u = winners.search(y);
		if (u != -1) {//if the item has already been chosen
			L = winners.pop(u);
			u = Z.search(y);
			if (u != -1) {
				Z.remove(u);//make sure it's not in Z
			}
			delete L;
			G--;
			cout << "succesfully removed" << endl;
		}
		else {
			u = Ns.search(y);
			if (u != -1) {//if the item is currently up for choice
				L = Ns.pop(u);
				restore(Ns, eliminated, L);//restore anything eliminated by L
				u = Z.search(y);
				if (u != -1) {
					Z.remove(u);//make sure Z doesn't contain L
				}
				delete L;
				G--;
				cout << "succesfully removed" << endl;

			}
			else {
				cout << "Sorry, couldn't find that item. Perhaps you mispelled it? Next time, press \'p\' to see its proper spelling" << endl;
			}
		}
	}
}
void Rescue(LIST& winners, LIST& Ns, LIST& eliminated, string y) {//a function for rescuing eliminated items or condemning chosen items
	int u = eliminated.search(y);
	story* L = NULL;
	int j = 0;
	if (u != -1) {//if the item has been eliminated
		L = eliminated.fetchStory(u);
		cout << L->id << " was eliminated by " << L->elim->id << ". enter a nonzero number to rescue it, or zero to leave it there\n";
		INPUT(j);
		if (j) {
			eliminated.remove(u);//restore item
			Ns.insert(L);
			L->elim = NULL;
		}
	}
	else {
		u = winners.search(y);
		if (u != -1) {//if the item has already been chosen
			L = winners.fetchStory(u);
			cout << L->id << " is already in the rankings, at place " << u + 1 << ". Enter a nonzero number to put it back into choosing, or zero to leave it there\n";
			INPUT(j);
			if (j) {
				winners.remove(u);//condemn the item back to shoosings.
				Ns.insert(L);
			}
		}
		else {
			u = Ns.search(y);
			if (u != -1) {//if the item is currently up for choice
				cout << y << " is currently in circulation. You'll see it soon!\n";
			}
			else {
				cout << "Couldn't find an item called \"" << y << "\"\nperhaps you mispelled it?\n(Includes Capitalization. Press \'p\' to help find the correct speeling)\n";
			}
		}
	}
}
void restore(LIST& Ns, LIST& eliminated, story* L) {//restores all items eliminated by the story L
	story* t;
	for (int i = 0; i < eliminated.L(); i++) {//cycles through Eliminated
		t = eliminated.fetchStory(i);
		if (t->elim == L) {//if that item was eliminated, restore it
			t->elim = NULL;
			Ns.insert(t);
			eliminated.remove(i);
			i--;//account for the change in eliminated's length
		}
	}
}
story* getstory(LIST& Ns, story* A, story* &L) {//finds a story that is neither of A or L
	int q = rand() % Ns.L();
	story* alpha = Ns.fetchStory(q);
	while (alpha == A || alpha == L) {
		q = rand() % Ns.L();
		alpha = Ns.fetchStory(q);
	}
	return alpha;
}
bool manelim(string y, LIST& Ns, LIST& elim) {//allows the user to manually eliminate an item
	int u = Ns.search(y);//location of eliminated item/
	story* alpha;//the story we are eliminating
	story* beta;//the story it will be eliminated by
	bool NN = 0;//which list the Lis is in
	bool kappa = 0;//A confirmation from the User
	if (u != -1) {//the item is in Ns
		alpha = Ns.fetchStory(u);
		NN = 1;
	}
	else {//the item is in winners
		u = elim.search(y);
		if (u == -1) {//failed to find
			cout << "Couldn't find an item called \"" << y << "\". Did you mispell it? I won't recognize it if it's already in the winners list" << endl;
			return 0;
		}
		alpha = elim.fetchStory(u);
		cout << "It looks like \"" << alpha->id << "\" has already been eliminated by \"" << alpha->elim->id << "\". Would you like to change what it was eliminated by? (0 = leave, 1 = change)" << endl;
		INPUT(kappa);
		if (kappa == 0)//user confirmation
			return 0;
	}
	cout << "What would you like \"" << y << "\" to be eliminated by?" << endl;//find the item that the user wants to get
	string k;
	INPUT(k);//ask for beta
	int al = Ns.search(k);//location of beta
	if (al == -1) {
		al = elim.search(k);
		if (al == -1) {//failed to find
			cout << "Couldn't find an item called \"" << k << "\". Did you mispell it? I won't recognize it if it's already in the winners list." << endl;
			return 0;
		}
		beta = elim.fetchStory(al);
	}
	else {
		beta = Ns.fetchStory(al);
	}
	if (findloop(alpha,beta)) {//ensure there is no self-reference errors.
		cout << "Elimination of \"" << alpha->id << "\" by \"" << beta->id << "\" causes self-reference. Please try different items." << endl;
		return 0;
	}
	alpha->elim = beta;//eliminate it
	if (NN) {//only need to change lists if it wasn't already eliminated
		Ns.remove(u);
		elim.insert(alpha);
	}
	return 1;

}

bool rename(LIST& winners, LIST& Ns, LIST& eliminated) {//selectively changes the name of an item
	cout << "What item would you like to rename?" << endl;
	string y;
	INPUT(y);
	story* L;
	int a = Ns.search(y);
	if (a == -1) {
		a = eliminated.search(y);
		if (a == -1) {
			a = winners.search(y);
			if (a == -1) {
				cout << "couldn't find an item called \"" << y << "\". perhaps you mispelled it? press 'p' to view correct spellings" << endl;
				return 0;
			}
			else L = winners.fetchStory(a);
		}
		else L = eliminated.fetchStory(a);
	}
	else L = Ns.fetchStory(a);
	cout << "What would you like to rename \"" << y << "\" to?" << endl;
	INPUT(y);
	cout << "Succesfully renamed \"" << L->id << "\" to \"" << y << "\"" << endl;
	L->id = y;
	return 1;
}

