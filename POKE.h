#pragma once
#include <iostream>
#include <string>
#include <vector>

bool main();






struct story {//the building block of this entire project
	std::string id;//a string to identify the object
	story* elim = NULL;//the item that eliminated this one
};
struct Node {
	story* S;//the story associated with this item
	Node* link;//the next item in the list
};
class LIST {//a singly linked list used to sort stories.
protected:
	int max_length = 0;	//an optional member; if nonzero the list will delete the first element when attempting to insert another.
	int length = 0;	//the number of nodes in the list
	Node* first = NULL;	//a pointer to the first node of the list
	Node* last = NULL;	//a pointer to the last node of the list
	Node* traverse(int loc);//retrieves the node of the list at the given location, only use for member functions
public:
	void debug();
	LIST();	//initializer
	LIST(int l);	//initializer with optional max_length
	void insert(story* s);	//inserts the story at the end of the list
	void remove(int loc);	//removes the item at the location. Fails if out of bounds
	int search(std::string L);	//searches the list for the story by id
	int search(story* L);		//searches the list for the story by adress
	story* fetchStory(int loc);	//retrieves an item of the list based on location
	story* pop(int loc);	//will remove the element at that location, then return it.
	void print();	//prints the list
	void winprint();//prints the lsit, ranked
	void elimprint();	//prints the list, including eliminations
	void rearrange();	//Allows the user to selectively rearrange the list
	void shallow_delete();	//Deletes the list, but not all of the stories
	void deep_delete();	//Deletes the list AND all of the stories it contains
	inline const int L() { return length; }//returns the length of the list
	~LIST();	//uninitializes the list through shallow or deep depending on needs
	void fixlengths();	//cuts the length of all strings in the list to a max.
	friend void beta_EXPORT(LIST &winners, LIST &Ns, LIST &eliminated) {//an earlier version of the export function. It still works fine, though I didn't keep the old import function.
		std::cout << std::endl;
		short int total = winners.length + Ns.length + eliminated.length;
		short int limlgth = eliminated.length;
		std::cout << winners.length << " " << Ns.length << " " << eliminated.length << " ";
		Node* travel = winners.first;
		std::string S;
		while (travel != NULL) {
			S = travel->S->id;
			for (int i = 0; i < S.length(); i++) {
				if (S[i] == ' ') {
					S[i] = '_';
				}
			}
			std::cout << S << " ";
			travel = travel->link;
		}
		travel = Ns.first;
		while (travel != NULL) {
			S = travel->S->id;
			for (int i = 0; i < S.length(); i++) {
				if (S[i] == ' ') {
					S[i] = '_';
				}
			}
			std::cout << S << " ";
			travel = travel->link;
		}
		travel = eliminated.first;
		while (travel != NULL) {
			S = travel->S->id;
			for (int i = 0; i < S.length(); i++) {
				if (S[i] == ' ') {
					S[i] = '_';
				}
			}
			std::cout << S << " ";
			travel = travel->link;
		}
		for (int i = 0; i < limlgth; i++) {
			int j = Ns.search(eliminated.fetchStory(i)->elim->id);
			if (j == -1) {
				j = eliminated.search(eliminated.fetchStory(i)->elim->id);
				std::cout << j + Ns.length << " ";
			}
			else {
				std::cout << j << " ";
			}

		}
		std::cout << "\n\n\n";
	}
	story* operator[](int loc) { return fetchStory(loc); }//unused, but could potentially be used
};

class Cencrypt{//a set of functions used for exporting and importing save data
private:
	static char int_to_char(int i, bool eleven);
	static int char_to_int(char i, bool eleven);
	static std::vector<int> list_of_strings_to_letters(std::vector <std::string> N, bool eleven);
	static bool IMPORT2(LIST& winners, LIST& Ns, LIST& eliminated, std::string STRING, bool thirteen);//export the data
	static std::string EXPORT2(LIST& winners, LIST& Ns, LIST& eliminated, bool thirteen);//import the data
	//convert between unsigned long long int and string
	static std::string int_to_string(unsigned long long int data);
	static unsigned long long int string_to_int(std::string Dta);
	//custom ints is for any value, determined by the program. given the max, you can calculate D, the number of variables stored, using D = floor(64 * log(2) / log(max));
	//convert between vector<int> and unsigned long long int
	static unsigned long long  int twelveints_to_data(std::vector<int> lengths);
	static unsigned long long  int thirteenletters_to_data(std::vector<int> letters);
	static unsigned long long  int eightints_to_data(std::vector<int> letters);
	static unsigned long long  int customints_to_data(std::vector<int> letters, int max, int D);
	static std::vector<int> vect_data_to_twelve_ints(unsigned long long int data);
	static std::vector<int> vect_data_to_thirteen_letters(unsigned long long int data);
	static std::vector<int> vect_data_to_int256(unsigned long long int data);
	static std::vector<int> vect_to_custom_int(unsigned long long int data, int max, int D);
	//Some of the data being encoded involves strings. These functions allow you to convert between lists of chars and lists of ints
	static char int_to_char(int i);
	static int char_to_int(char i);
	
	//convert between vector<string> and vector<int>
	static std::vector<int> list_of_strings_to_letters(std::vector<std::string> N);
	//These functions will encrypt and decrypt a string using fairly basic encryption methods.
	static std::string encrypt(std::string data);
	static std::string decrypt(std::string yodel);
public:
	//The functions that manage importing and exporting
	static void IMPORT(LIST& winners, LIST& Ns, LIST& eliminated);
	static std::string EXPORT(LIST& winners, LIST& Ns, LIST& eliminated);
};

void setup(LIST& Ns, int& G, char imput);//sets up the list at the beginning of main
void Loop(LIST& winners, LIST& Ns, LIST& eliminated, LIST& Z, int& G, story* &L);//manages the user's choices
void Undo(LIST&, LIST&, LIST&, LIST&);//undoes an action
void del(LIST& winners, LIST& Ns, LIST& eliminated, LIST& Z, std::string y, int& G);//deletes an item
void Rescue(LIST& winners, LIST& Ns, LIST& eliminated, std::string y);//resuces something for eliminated, or condemns it from winners
story* getstory(LIST& Ns, story* A, story* &L);//ensures no duplicates when getting stories
void restore(LIST& Ns, LIST& eliminated, story* L);//restores all items eliminated by a certain ite,
bool manelim(std::string y, LIST& Ns, LIST& elim);//manually eliminates an item
bool findloop(story* name, story* targ);//ensures no self-reference in elimination
bool rename(LIST&, LIST&, LIST&);

//various waiting functions
void A();
std::string wait(int i);
std::string B();
std::string B(int k);


int interpret();//a developer use function

//various imput functions
int cinumer(int def);
void INPUT(int& j);
void INPUT(bool& j);
std::string INPUT(std::string& y);


int es(int k);//a simple "f(x)=" function

//for storing large quantities of data outside of the main function
std::vector<std::string> default_lists(int k);
void textblock(int);



//protects the password protected areas of the program
static bool password() {
	std::cout << "To prove that you are the developer, please enter the password: " << std::endl;
	std::string check;
	std::cin >> check;
	return (check != "3.141");
}






