#include <cmath>
#include "POKE.h"
using namespace std;

bool operator ==(string& a, string& b) {//overload the == operator for strings so that it waives capitalization
	if (a.length() != b.length())
		return 0;
	for (int i = 0; i < a.length(); i++) {
		if ((a[i] != b[i]) && !((a[i] - 'a' < 26) && (a[i] - 'a' >= 0) && (a[i] - 'a' == b[i] - 'A')) && !((a[i] - 'A' < 26) && (a[i] - 'A' >= 0) && (a[i] - 'A' == b[i] - 'a')))
			return 0;
	}
	return 1;
}


//All of the member functions of LIST
//LIST is a singly-linked list, where each node points to a story and 1 other node.
//It is fully equipped with most basic tools for a good LIST.
LIST::LIST() {//basic initializer
	length = 0;
	first = NULL;
	last = NULL;
	max_length = 0;
}
LIST::LIST(int l) {//initializer with the optional max_length parameter
	length = 0;
	first = NULL;
	last = NULL;
	max_length = (l > 0 ? l : 0);
}
LIST::~LIST() {//the uninitializer for the list
	if (max_length != 0) {//calls shallow if there is a max length
		shallow_delete();
	}
	else {
		deep_delete();//calls deep delete for all normal lists
	}
}
Node* LIST::traverse(int loc) {//traverses to a point in the list. Helpful for other functions.
	if (loc >= 0 || loc < length) {
		if (loc == 0) {
			return first;
		}
		if (loc == length - 1) {
			return last;
		}
		Node* current = first;
		for (int i = 0; i < loc; i++) {
			current = current->link;
		}
		return current;
	}
	else
		std::cout << "There was an internal error.\n";
	return NULL;
}

void LIST::insert(story* s) {//inserts the chosen item a the end of the list.
	if (length == 0) {//the list is empty
		first = new Node;
		last = first;
		first->link = NULL;
		first->S = s;
		length++;
	}
	else {
		if (length != max_length) {//for any normal insertion
			Node* n = new Node;
			last->link = n;
			n->S = s;
			n->link = NULL;
			last = n;
			length++;
		}
		else {//if length is at max length
			Node* t = first;
			first = first->link;
			delete t;
			t = new Node;
			last->link = t;
			last = t;
			last->S = s;
			last->link = NULL;
		}
	}
}
void LIST::remove(int loc) {//removes the item at index loc.
	if (loc >= 0 || loc < length) {
		if (length == 1) {//if the list has a single item
			delete first;
			length--;
			first = NULL;
			last = NULL;
		}
		else {
			if (loc == length - 1) {//if the target it the last iemt
				Node* prev = traverse(loc - 1);
				delete last;
				length--;
				last = prev;
				prev->link = NULL;
			}
			else {
				if (loc == 0) {//if the target is the first item
					Node* T = first->link;
					delete first;
					length--;
					first = T;
				}
				else {//default case
					Node* prev = traverse(loc - 1);
					Node* next = prev->link->link;
					delete prev->link;
					length--;
					prev->link = next;
				}
			}
		}
	}
	else {
		std::cout << "There was an internal error.\n";
	}

}
story* LIST::pop(int loc) {//removes the item at index loc, then returns the associated story
	story* s = NULL;
	if (loc >= 0 || loc < length) {
		if (length == 1) {//if the list has a single item
			s = first->S;
			delete first;
			length--;
			first = NULL;
			last = NULL;
		}
		else {
			if (loc == length - 1) {//if the target it the last iemt
				Node* prev = traverse(loc - 1);
				s = last->S;
				delete last;
				length--;
				last = prev;
				prev->link = NULL;
			}
			else {
				if (loc == 0) {//if the target is the first item
					Node* T = first->link;
					s = first->S;
					delete first;
					length--;
					first = T;
				}
				else {//default case
					Node* prev = traverse(loc - 1);
					Node* next = prev->link->link;
					s = prev->link->S;
					delete prev->link;
					length--;
					prev->link = next;
				}
			}
		}
	}
	else {
		std::cout << "There was an internal error.\n";
	}
	return s;

}

//search() has two modes, one for string and the other for pointer
int LIST::search(std::string L) {//searches the list based on the identifier of the story. Returns location, or -1 if not found
	Node* current = first;
	int i = 0;
	while (current != NULL) {
		//if ((current->S == NULL ? 0 : sorta_equal(current->S->id, L))) {
		if ((current->S == NULL ? 0 : current->S->id == L)) {
			return i;
		}
		current = current->link;
		i++;
	}
	return -1;
}
int LIST::search(story* L) {//searches the list based on the address of the story. Returns location, or -1 if not found
	Node* current = first;
	int i = 0;
	while (current != NULL) {
		if (current->S == L) {
			return i;
		}
		current = current->link;
		i++;
	}
	return -1;
}
story* LIST::fetchStory(int loc) {//returns the story at a given index
	Node* current = traverse(loc);
	if (current == NULL) {//If there is some sort of internal error, it will create and return an empty story rather than NULL
		story* failure = new story;
		failure->id = "";
		failure->elim = NULL;
		return failure;
	}
	return(current->S);
}

void LIST::print() {//prints the list
	if (length == 0) {
		cout << "Internal error. Something is VERY wrong if you can see this." << endl;
	}
	Node* that = first;
	while (that != NULL) {
		//cout << that->S << " "<<that->S->id<<endl;
		cout << that->S->id << endl;
		that = that->link;
	}
}
void LIST::winprint() {//prints the list while ranking each of them
	if (length == 0)
		cout << "nothing to see here! Make some choices to add things to the winners list!" << endl;
	Node* then = first;
	for (int i = 1; then != NULL; i++) {
		std::cout << i << ") " << then->S->id << std::endl;
		//std::cout << i << ") " << then->S << std::endl;
		then = then->link;
	}
}
void LIST::elimprint() {//prints the list, along with all eliminated items
	if (length == 0) {
		cout << "nothing to see here! When you make choices, you'll 'eliminate' items, and you can find them here!" << endl;
	}
	Node* that = first;
	while (that != NULL) {
		cout << that->S->id << " (by " << (that->S->elim == NULL ? "NULL" : that->S->elim->id) << ")\n";
		//cout << that->S << " (by " << that->S->elim << ")\n";
		that = that->link;
	}
}

void LIST::rearrange() {//A function which will rearrange the list based on the user's whim.
	int u = 0;
	int v = 0;
	while (u != -1 && v != -1) {
		A();A();
		std::cout << "Which item would you like to move? (type the number of the object, or 0 to quit)" << std::endl;
		winprint();
		INPUT(u);//the item to be moved ( 1 <= u <= length)
		if (u == 0) { break; }
		std::cout << "Where would you like to move it to? (type the number of the object, or 0 to quit)" << std::endl;
		INPUT(v);//the final location of the item ( 1= < v <= length)
		if (v == 0) { break; }
		if (u > 0 && u <= length && v > 0 && v <= length) {
			if (u != v) {
				u--;//convert to index of 0 being first
				v--;
				Node* home;
				if (u == length - 1) {//if the target it the last iemt
					Node* prev = traverse(u - 1);
					home = last;
					last = prev;
					prev->link = NULL;
				}
				else {
					if (u == 0) {//if the target is the first item
						home = first;
						first = home->link;
						home->link = NULL;
					}
					else {//default case
						Node* prev = traverse(u - 1);
						home = prev->link;
						prev->link = home->link;
						home->link = NULL;
					}
				}
				if (v == 0) {//if the target is the first item
					home->link = first;
					first = home;
				}
				else {
					if (v == length - 1) {//if the target is the last item
						last->link = home;
						home->link = NULL;
						last = home;
					}
					else {
						Node* prev = traverse(v - 1);//default case
						home->link = prev->link;
						prev->link = home;
					}
				}
				cout << "Succesfully moved!" << endl;
			}
			else {
				std::cout << "It's already there, silly!\n";
			}
		}
		else {
			if (u == 0 || v == 0) {//in order to leave the program
				break;
			}
			std::cout << "Sorry, one or both of those numbers was invalid.\n";
		}
	}
}
void LIST::shallow_delete() {//an uninitializer that will leave all stories intact
	Node* trail = first;
	Node* next = first;
	while (trail != NULL) {
		next = next->link;
		delete trail;
		trail = next;
		length--;
	}
	first = NULL;
	last = NULL;
	length = 0;
}
void LIST::deep_delete() {//an uninitializer that will also uninitialize all stories
	Node* trail = first;
	Node* next = first;
	story* L = NULL;
	while (trail != NULL) {
		next = next->link;
		L = trail->S;
		if (L != NULL)
			delete L;
		delete trail;
		trail = next;
	}
	first = NULL;
	last = NULL;
	length = 0;
}
void LIST::fixlengths() {//will cut the length of all the id's to prevent overflow in the Cencrypt::EXPORT2() function
	Node* current = first;
	while (current != NULL) {
		if (current->S->id.length() >= 40) {
			string h = current->S->id;
			string k = "";
			for (int i = 0; i < 40 - 1; i++) {
				k += "0";
				k[i] = h[i];
			}
			current->S->id = k;
		}
		current = current->link;
	}
}


void LIST::debug() {//various debug info
	std::cout << "first =   \t" << first << std::endl;
	std::cout << "first->link =\t" << (first == NULL ? NULL : first->link) << std::endl;
	std::cout << "first->S =\t" << (first == NULL ? NULL : first->S) << std::endl;
	std::cout << "first->S->id =\t" << (first == NULL ? "NULL" : (first->S == NULL ? "NULL" : first->S->id)) << std::endl;
	std::cout << "first->S->elim=\t" << (first == NULL ? NULL : (first->S == NULL ? NULL : first->S->elim)) << std::endl;
}

//The member functions for the Cencrypt Class
//The Cencrypt protocol was designed by me to save the Data from the program in the form of a string, that can then be loaded at any point.
//It treats strings of keyboard characters (chars between 32 and 126) as base-94 numbers.
//Each character is a c-bit, and contains approximately 6.5 bits
//10 characters is a C-byte. Treating a C-byte as a base-94 number allows you to convert it into an unsigned long long int.
//This unsigned long long int can store data.
//For example, if I wanted to store the letters a-z in one of these C-bytes,
//I could make a base-26 number, where each digit is the letter of choice and turn it into an unsigned long long int.
//I could then turn that unsigned long long int into a C-byte and print it to the screen.
//Using this theory, the IMPORT and EXPORT functions will convert LIST data into strings, and vice versa
const static bool seventeen = 1;//There are currently two modes of encoding. seventeen = 1 is the better of the two.
void Cencrypt::IMPORT(LIST& winners, LIST& Ns, LIST& eliminated) {//manages importing a savestate
	string STRING;
	cout << B() << "\n\nPlease paste the data you copied:\n\n\n" << endl;
	cin >> STRING;
	int k = IMPORT2(winners, Ns, eliminated, STRING, seventeen);//import
	while (k == 0) {//ensures there the import data is valid
		cout << "Bad Data. Failed to input. Please try again, or type \'0\' to cancel." << endl;
		cout << B() << "\n\nPlease paste the data you copied:\n\n\n" << endl;
		cin >> STRING;
		k = IMPORT2(winners, Ns, eliminated, STRING, seventeen);
	}

}
string Cencrypt::EXPORT(LIST& winners, LIST& Ns, LIST& eliminated) {//function that manages the exporting of the list.
	string yodel = EXPORT2(winners, Ns, eliminated, seventeen);
	cout << "\n\n\nCopy the following block of text.\n" << endl;
	cout << yodel << endl;//user will copy and past this
	return yodel;//returns the string in case a deceloper needs to use it.
	//beta_EXPORT(winners, Ns, eliminated);
}
bool Cencrypt::IMPORT2(LIST& winners, LIST& Ns, LIST& eliminated, string STRING, bool eleven) {//the actual importing function. Returns 1 from a succesful import or 2 from an unsuccesful one.
	if (STRING == "0")//escape sequence
		return 1;
	if (STRING.length() < 4)//bad data
		return 0;
	STRING = decrypt(STRING);//a layer of decryption for the fun of it.
	if (STRING.length() % 10) {//bad data
		return 0;
	}
	int alpha = STRING.length() / 10;//number of C-Bytes
	vector<string> STRINGDTA;//stores all of the Cbytes
	for (int i = 0; i < alpha; i++) {
		STRINGDTA.push_back("0000000000");
		for (int j = 0; j < 10; j++) {
			STRINGDTA[i][j] = STRING[10 * i + j];//fill it with CBits
		}
	}
	vector<unsigned long long int> ULLIDTA;//stores all the decoded C-bytes
	for (int i = 0; i < alpha; i++) {
		ULLIDTA.push_back(string_to_int(STRINGDTA[i]));//decode the C-bytes
	}
	vector<int> L = vect_data_to_int256(ULLIDTA[0]);//the lengths of the three lists
	int stringct = L[0] + L[1] + L[2];//number of items on the list
	int D = (L[1] + L[2] == 0 ? 0 : floor(64 * log(2) / log(L[1] + L[2])));//The number of elimination datapoints per C-byte
	vector<int> lengths;//stores all of the lengths
	int letct = 0;//number of combined letters across all strings
	short int BBYTE = 0;//number of Cbytes associated with letters, or unused in mode 1
	short int ABYTE = ceil(static_cast<double>(stringct) / 12);//number of Cbytes associated with Lengths, or letters in mode 1
	vector<int> letters;//stores all of the letter data
	vector<string> names;//all of the string data
	if (L[4] != 0)//bad data
		return 0;
	if (eleven) {//mode 1 encryption
		for (int i = 1; i < ULLIDTA.size(); i++) {//unpack ALL of the data
			vector<int> twelve = vect_data_to_twelve_ints(ULLIDTA[i]);
			for (int j = 0; j < 12; j++) {
				letters.push_back(twelve[j]);
			}
		}
		for (int i = 0; i < letters.size(); i++) {//filter the data based on the stop points
			string ouch = "";
			while (letters[i] != 39 && letters[i] != 32) {
				ouch += "0";
				ouch[ouch.length() - 1] = int_to_char(letters[i], 1);
				i++;
			}
			names.push_back(ouch);
			if (letters[i] == 32) {
				ABYTE = (i + 1) / 12;//find the correct number of letter bytes
				break;
			}
		}
		for (int q = 0; q < names.size(); q++) {//make sure every string is receiveble via the cin function
			if (names[q][0] == ' ')
				names[q][0] = '_';
			if (names[q][names[q].length() - 1] == ' ')
				names[q][names[q].length() - 1] = '_';
		}
	}
	else {
		if (alpha < 1 + ABYTE && D)//bad data
			return 0;
		for (int i = 1; i < ABYTE; i++) {
			vector<int> twelve = vect_data_to_twelve_ints(ULLIDTA[i]);//decode
			for (int j = 0; j < 12; j++) {
				lengths.push_back(twelve[j]);//fill with lengths
			}
		}
		vector<int> twelve = vect_data_to_twelve_ints(ULLIDTA[ABYTE]);//does something different for the last length byte
		for (int i = 0; i < (stringct % 12 == 0 ? 12 : stringct % 12); i++) {
			lengths.push_back(twelve[i]);//the last length-byte will contain some redundant data, so this cuts out the redundancies
		}



		for (int i = 0; i < stringct; i++) {
			letct += lengths[i];
		}
		BBYTE = (eleven ? 0 : ceil(static_cast<double>(letct) / 13));
		if (alpha < 1 + ABYTE + BBYTE && D)//bad data
			return 0;

		for (int i = 1 + ABYTE; i < BBYTE + ABYTE; i++) {
			vector<int> thirteen = vect_data_to_thirteen_letters(ULLIDTA[i]);//decode
			for (int j = 0; j < 13; j++) {
				letters.push_back(thirteen[j]);//fill with letters
			}
		}
		vector<int> thirteen = vect_data_to_thirteen_letters(ULLIDTA[ABYTE + BBYTE]);//does something different for the last letter byts
		for (int i = 0; i < (letct % 13 == 0 ? 13 : letct % 13); i++) {
			letters.push_back(thirteen[i]);//removes redunant data
		}


		int currrent = 0;
		for (int i = 0; i < lengths.size(); i++) {//iterates through the lengths list
			string ouch = "";
			for (int j = 0; j < lengths[i]; j++) {//iterates through the letters list
				ouch += "0";
				ouch[j] = int_to_char(letters[currrent]);//fills the appropriate string with the appropriate characters
				if (ouch[j] == ' ' && ((j == 0) || (j == lengths[i] - 1)))
					ouch[j] = '_';//adds an underscore if the last or first letter is a space. This prevents messing with the cin function.
				currrent++;
			}
			names.push_back(ouch);
			//cout << names[i] << endl;
		}
	}
	int elimct = L[2];//the number of eliminated items
	short int CBYTE = (D == 0 ? 0 : ceil(static_cast<double>(elimct) / D));//the number of C-bytes associated with elimination
	if (alpha != 1 + ABYTE + BBYTE + CBYTE && D)//bad data
		return 0;
	vector<int> elims;//stores all the elimination data
	if (D) {//will not trigger if there is no elimination data.
		for (int i = 1 + ABYTE + BBYTE; i < CBYTE + ABYTE + BBYTE; i++) {
			vector<int> eight = vect_to_custom_int(ULLIDTA[i], L[1] + L[2], D);
			for (int j = 0; j < D; j++) {
				elims.push_back(eight[j]);
			}
		}
		vector<int> eight = vect_to_custom_int(ULLIDTA[ABYTE + BBYTE + CBYTE], L[1] + L[2], D);
		for (int i = 0; i < (elimct % D == 0 ? D : elimct % D); i++) {
			elims.push_back(eight[i]);
		}
	}

	winners.deep_delete();//clears the lists for preparation
	Ns.deep_delete();
	eliminated.deep_delete();
	story* n;
	for (int i = 0; i < L[0]; i++) {//fills winners
		n = new story;
		n->id = names[i];
		winners.insert(n);
	}
	for (int i = L[0]; i < L[0] + L[1]; i++) {//fills Ns
		n = new story;
		n->id = names[i];
		Ns.insert(n);
	}
	for (int i = L[0] + L[1]; i < L[0] + L[1] + L[2]; i++) {//fills eliminated
		n = new story;
		n->id = names[i];
		eliminated.insert(n);
	}
	for (int i = 0; i < L[2]; i++) {//eliminates all of the proper items
		int q = elims[i];
		if (q < Ns.L()) {
			eliminated.fetchStory(i)->elim = Ns.fetchStory(q);//if it was eliminated by a choosing item
		}
		else {
			if (eliminated.L() <= q - Ns.L())
				return 0;
			eliminated.fetchStory(i)->elim = eliminated.fetchStory(q - Ns.L());//if it was eliminated by an eliminated item
		}
	}
	cout << B(2) << "\nDidn't crash!\n" << endl;//victory cheer (Mostly for me. It was sooo hard to debug this)
	B();
	return 1;
}
std::string Cencrypt::EXPORT2(LIST& winners, LIST& Ns, LIST& eliminated, bool eight) {//converts LIST data into a string
	if (!eight) {
		winners.fixlengths();
		eliminated.fixlengths();
		Ns.fixlengths();
	}
	int D = (Ns.L() + eliminated.L() == 0 ? 0 : floor(64 * log(2) / log(Ns.L() + eliminated.L())));//the number of elimination data that can be fint into a Cbyte
	vector<int> macro_lengths = { winners.L(),Ns.L(),eliminated.L() };//the lengths of the list
	vector<string> strings;//A string of every single story id.
	for (int i = 0; i < winners.L();i++) {
		strings.push_back(winners.fetchStory(i)->id);//winners ids
	}
	for (int i = 0; i < Ns.L();i++) {
		strings.push_back(Ns.fetchStory(i)->id);//Ns ids
	}
	for (int i = 0; i < eliminated.L();i++) {
		strings.push_back(eliminated.fetchStory(i)->id);//eliminated ids
	}
	const int thirteen = 13 - eight;
	vector<int> letters = list_of_strings_to_letters(strings, eight);//stores all of the letters data
	vector<int> lengths;//stores all of the lengths data
	vector<int> elims;//stores all of the elimination data
	for (int i = 0; i < eliminated.L(); i++) {
		int j = Ns.search(eliminated.fetchStory(i)->elim);
		if (j == -1) {
			j = Ns.L() + eliminated.search(eliminated.fetchStory(i)->elim);
		}
		elims.push_back(j);//fills elims with the elimination data
	}
	for (int i = 0; i < strings.size() && !eight; i++) {
		lengths.push_back(strings[i].length());//fills lengths with the appropriate data
	}
	while (letters.size() % thirteen) {
		letters.push_back(0);//rounds out the cbyte
	}
	if (eight) {
		letters[letters.size() - 1] = 32;
	}
	while (lengths.size() % 12 && !eight) {
		lengths.push_back(0);//rounds out the cbyte
	}
	while (macro_lengths.size() % 8) {
		macro_lengths.push_back(0);
	}
	if (D) {//if there is elimination data
		while (elims.size() % D) {
			elims.push_back(0);//rounds out the cbyte
		}
	}



	vector<unsigned long long int> TOTAL;//the data to be exported, in the form of unsigned long long int
	TOTAL.push_back(eightints_to_data(macro_lengths));//convert length data into int
	for (int i = 0; i < lengths.size() / 12 && !eight; i++) {
		vector<int> t;
		for (int j = 0; j < 12; j++) {//breaks the length data into chunks
			t.push_back(lengths[12 * i + j]);
		}
		TOTAL.push_back(twelveints_to_data(t));//adds length data to TOTAL
	}
	for (int i = 0; i < letters.size() / thirteen; i++) {
		vector<int> t;
		for (int j = 0; j < thirteen; j++) {//breaks the letter data into chunks
			t.push_back(letters[thirteen * i + j]);
		}
		TOTAL.push_back((eight ? twelveints_to_data(t) : thirteenletters_to_data(t)));//adds letter data to TOTAL
	}
	if (D) {//if there is elimination data
		for (int i = 0; i < elims.size() / D; i++) {
			vector<int> t;
			for (int j = 0; j < D; j++) {
				t.push_back(elims[D * i + j]);//breaks elim data into chunks
			}
			TOTAL.push_back(customints_to_data(t, Ns.L() + eliminated.L(), D));//adds elimination data to TOTAL
		}
	}
	string yodel = "";//the string that will be used
	for (int i = 0; i < TOTAL.size(); i++) {
		yodel += int_to_string(TOTAL[i]);//fill Yodel with each block of data
	}
	yodel = encrypt(yodel);//add a layer of encryption, just for the fun of it
	return yodel;
}

std::string Cencrypt::int_to_string(unsigned long long int data) {//converts an unsigned long long int into a string
	char* Dta = new char[10];
	for (int i = 1; i <= 10; i++) {//picks apart the dada
		int j = pow(94, i);
		int l = pow(94, i - 1);
		//char x = 33 + (data % j) / l;
		char x = 33 + static_cast<char>(data % 94);
		Dta[i - 1] = x;
		data /= 94;

	}
	std::string lol = "0000000000";
	for (int i = 0; i < 10; i++) {
		lol[i] = Dta[i];//fills lol
	}
	delete[] Dta;
	return lol;
}
unsigned long long int Cencrypt::string_to_int(std::string Dta) {//converts a Cbyte string into an unsigned long long int
	unsigned long long int data2 = 0;
	unsigned long long int l = 1;
	for (int i = 0; i < 10; i++) {//forms the data into unsigned long long int
		data2 += (static_cast<unsigned long long int>(Dta[i] - 33)) * l;
		l *= 94;
	}
	return data2;
}

//these functions will encode a number of integers into an unsigned long long int. The upper maximum value of the integer determines how many can be stored.
unsigned long long  int Cencrypt::twelveints_to_data(vector<int> lengths) {//twelve ints of 0-39
	unsigned long long int data = 0;
	for (int i = 0; i < 12; i++) {
		unsigned long long int d = lengths[i];
		for (int j = 0; j < i; j++) {
			d *= 40;
		}
		data += d;
	}
	return data;
}
unsigned long long  int Cencrypt::thirteenletters_to_data(vector<int> letters) {//13 ints of 0-29
	unsigned long long int data = 0;
	for (int i = 0; i < 13; i++) {
		unsigned long long int d = letters[i];
		for (int j = 0; j < i; j++) {
			d *= 30;
		}
		data += d;
	}
	return data;
}
unsigned long long  int Cencrypt::eightints_to_data(vector<int> letters) {//8 ints of 0-255
	unsigned long long int data = 0;
	for (int i = 0; i < 8; i++) {
		unsigned long long int d = letters[i];
		for (int j = 0; j < i; j++) {
			d *= 256;
		}
		data += d;
	}
	return data;
}
unsigned long long  int Cencrypt::customints_to_data(vector<int> letters, int max, int D) {//custom number of ints
	//int D = floor(64 * log(2) / log(max));//D is a function of the maximum value (add 1 if you include zero)
	unsigned long long int data = 0;
	for (int i = 0; i < D; i++) {
		unsigned long long int d = letters[i];
		for (int j = 0; j < i; j++) {
			d *= max;
		}
		data += d;
	}
	return data;
}


//Some of the data being encoded involves strings. These functions allow you to convert between lists of chars and lists of ints
//In order to maximize the number of letters I can store in a C-byte, the only special characters I allow are space, comma, apostophe, and period.
//If you would like to change this, you'll have to change quite a lot of the Cencrypt protocol, but it is possible.
char Cencrypt::int_to_char(int i) {
	if (1 <= i && i <= 26) {
		return 'a' + i - 1;
	}
	switch (i) {
	case 27:
		return '\'';
	case 28:
		return '.';
	case 29:
		return ',';
	case 0:
	default:
		return ' ';
	}
}
int Cencrypt::char_to_int(char i) {
	if ('a' <= i && i <= 'z')
		return i - 'a' + 1;
	if ('A' <= i && i <= 'Z')
		return i - 'A' + 1;
	switch (i) {
	case '\'':
		return 27;
	case '.':
		return 28;
	case ',':
		return 29;
	case ' ':
	default:
		return 0;
	}
}
vector<int> Cencrypt::list_of_strings_to_letters(vector<string> N) {//given a list of strings, will pick it a part into ints
	vector<int> letters;
	for (int i = 0; i < N.size(); i++) {
		for (int j = 0; j < N[i].length(); j++) {
			letters.push_back(char_to_int(N[i][j]));
		}
	}
	return letters;
}
char Cencrypt::int_to_char(int i, bool eleven) {
	if (1 <= i && i <= 26) {
		return 'a' + i - 1;
	}
	if (!eleven) {
		return(int_to_char(i));
	}
	switch (i) {
	case 27:
		return '\'';
	case 28:
		return '.';
	case 29:
		return ',';
	case 30:
		return '!';
	case 31:
		return '2';
	case 33:
		return '_';
	case 34:
		return ':';
	case 35:
		return '/';
	case 36:
		return '-';
	case 37:
		return '(';
	case 38:
		return ')';
	case 0:
	default:
		return ' ';
	}
}
int Cencrypt::char_to_int(char i, bool eleven) {
	if ('a' <= i && i <= 'z')
		return i - 'a' + 1;
	if ('A' <= i && i <= 'Z')
		return i - 'A' + 1;
	if (!eleven) {
		return(char_to_int(i));
	}
	switch (i) {
	case '\'':
		return 27;
	case '.':
		return 28;
	case ',':
		return 29;
	case '!':
		return 30;
	case '2':
		return 31;
	case '_':
		return 33;
	case ':':
		return 34;
	case '/':
		return 35;
	case '-':
		return 36;
	case '(':
		return 37;
	case ')':
		return 38;
	case ' ':
	default:
		return 0;
	}
}
vector<int> Cencrypt::list_of_strings_to_letters(vector<string> N, bool eleven) {//given a list of strings, will pick it a part into ints

	vector<int> letters;
	for (int i = 0; i < N.size(); i++) {
		for (int j = 0; j < N[i].length(); j++) {
			letters.push_back(char_to_int(N[i][j], eleven));
		}
		if (eleven)
			letters.push_back(39);
	}
	return letters;
}





//These functions will convert back from unisgned long long int to a list of integers. THey are the inverses of the Xints_to_data functions
vector<int> Cencrypt::vect_data_to_twelve_ints(unsigned long long int data) {//twelve ints of size 0-39
	vector<int> rel;
	for (int i = 0; i < 12; i++) {
		rel.push_back(data % 40);
		data = data - (data % 40);
		data /= 40;
	}
	return rel;
}
vector<int> Cencrypt::vect_data_to_thirteen_letters(unsigned long long int data) {//13 ints of size 0-29
	vector<int> rel;
	for (int i = 0; i < 13; i++) {
		rel.push_back(data % 30);
		data = data - (data % 30);
		data /= 30;
	}
	return rel;
}
vector<int> Cencrypt::vect_data_to_int256(unsigned long long int data) {//8 ints of size 0-255
	vector<int> rel;
	for (int i = 0; i < 8; i++) {
		rel.push_back(data % 256);
		data = data - (data % 256);
		data /= 256;
	}
	return rel;
}
vector<int> Cencrypt::vect_to_custom_int(unsigned long long int data, int max, int D) {//custom number of ints
	//int D = floor(64 * log(2) / log(max));//D is a function of maximum size
	vector<int> rel;
	for (int i = 0; i < D; i++) {
		rel.push_back(data % max);
		data = data - (data % max);
		data /= max;
	}
	return rel;
}


vector<int> add = { 41,43,36,86,87,26,10,30,78,24 };//A key used in the encryption/decryption process
std::string Cencrypt::encrypt(std::string data) {
	int L = data.length();
	int k = 0;
	while (data.back() == '!') {//replace redundant zeroes at the ends
		L--;
		data.pop_back();
		k++;
	}
	vector<int> DTA;//The values will be passed back and forth between DTA and LAL in the encrytption process
	vector<int> LAL;
	vector<int> p = { 3,5,7,11,13,17,19,23,29,31 };//the second through eleventh prime numbers
	for (int i = 0; i < 4; i++) {
		DTA.push_back(data[i] - 33);//fills with numberical equivalents of the chars.
	}
	for (int i = 10; i < L; i++) {//excludes the redundant block of zeroes in the first C-byte
		DTA.push_back(data[i] - 33);
	}
	string LOL = "";
	for (int i = 0; i < L - 6; i++) {
		LAL.push_back(((DTA[i] + add[i % 10]) * p[i % 10]) % 94);//multiplies by the (n+1)th prime (n being position in C-byte) and adds a number from the key
		LOL += "0";
		LOL[i] = (LAL[i] + 33);
		//LOL.append(LAL[i] + 33);
	}
	LOL += "0";
	LOL[L - 6] = k + 33;//the number of redundant zeroes at the end
	int j = 2;
	while (LOL.length() % j == 0) {//finds the smallest number that is NOT a factor of LOL.length()
		j++;
	}
	string yodel = LOL;
	for (int i = 0; i < yodel.length(); i++) {//ceaser cipher by j
		if (i - j < 0) {
			yodel[i] = LOL[i - j + yodel.length()];
		}
		else {
			yodel[i] = LOL[i - j];
		}
	}
	vector<int> inverses1;
	vector<int> inverses2;
	for (int i = 2; i < yodel.length(); i++) {
		int y = yodel.length() - 1;
		bool kappa = 1;
		while (y >= 2 && kappa) {
			if (y * i % yodel.length() == 1) {//finds the list of inverses-mod-length of the string
				inverses1.push_back(i);
				inverses2.push_back(y);
				kappa = 0;
			}
			y--;
		}
	}
	LOL = yodel;
	for (int i = 0; i < inverses1.size(); i++) {
		LOL[inverses1[i]] = yodel[inverses2[i]];//swaps all of the items with the inverse-mod-length of their index
	}
	return LOL;
}
std::string Cencrypt::decrypt(std::string yodel) {//will undo the encryption done to the string
	string data = yodel;
	vector<int> inverses1;
	vector<int> inverses2;
	for (int i = 2; i < yodel.length(); i++) {
		int y = yodel.length() - 1;
		bool kappa = 1;
		while (y >= 2 && kappa) {
			if (y * i % yodel.length() == 1) {//find all of the inverses-mod-length
				inverses1.push_back(i);
				inverses2.push_back(y);
				kappa = 0;
			}
			y--;
		}
	}
	for (int i = 0; i < inverses1.size(); i++) {
		data[inverses1[i]] = yodel[inverses2[i]];//swap each element with the inverse-mod-length of its index
	}
	int j = 2;
	while (data.length() % j == 0) {//find the smallest number that is NOT a factor of length()
		j++;
	}
	for (int i = 0; i < data.length(); i++) {
		yodel[i] = data[(i + j) % data.length()];//ceaser cipher by that number
	}
	data = yodel;
	int L = data.length();
	int k = static_cast<int>(data[L - 1] - 33);
	L--;
	vector<int> DTA;
	vector<int> LAL;
	vector<int> p = { 63,19,27,77,29,83,5,45,13,91 };//the inverse-mod-94 of the second through eleventh primes
	for (int i = 0; i < L; i++) {
		DTA.push_back(data[i] - 33);
	}
	for (int i = 0; i < L; i++) {
		LAL.push_back(((DTA[i] * p[i % 10]) % 94) - add[i % 10]);//multiplies by the inverse then subtracts the key number
		if (LAL[i] < 0) {
			LAL[i] += 94;
		}
		data[i] = LAL[i] + 33;
	}
	string LOL = "";
	for (int i = 0; i < 4; i++) {
		LOL += "0";
		LOL[i] = data[i];
	}
	for (int i = 4; i < 10; i++) {//adds the redundant zeroes in the first C-byte
		LOL += "!";
	}
	for (int i = 10; i < L + 6; i++) {
		LOL += "0";
		LOL[i] = data[i - 6];
	}
	for (int i = 0; i < k; i++) {//adds the redundant zeroes to the end
		LOL += "!";
	}
	return LOL;
}

bool findloop(story* name, story* targ) {//ensure there would be no self reference if name was eliminated by targ
	while (targ != NULL && targ != name) {
		targ = targ->elim;
	}
	return targ != NULL;
}
int es(int k) {//estimates the number of choices remaining using empirical data.
	//the function was determined using a least squares regression. But instead of doing mx + b, I used a(x-1)^b.
	//It has two different functions depending on how many items remain. It's mostly accurate
	if (k > 31.5) {//large number of choices left
		float K = k;
		float alpha = pow(k - 1, 1.165);
		return floor(1.694 * alpha);
	}
	float K = k;//small number of choices left
	float alpha = pow(k - 1, 1.253);
	return floor(1.254 * alpha);
}
void INPUT(int& j) {//A protected way to input integers.
	//if the user inputs a string that doesn't look like a number (i.e, 1234tg7084r7fhg) it will reject it
	int a = -1;
	while (a == -1) {
		a = cinumer(-1);
	}
	j = a;
}
void INPUT(bool& j) {//A protective way to input bools
	string y;
	cin >> y;
	j = (y != "0");//will return 1 unless the inputted string is "0".
}
std::string INPUT(std::string& k) {//the getline() function is a little wonky, so this will input the whole line.
	cin.clear();
	string l;
	cin >> k;
	getline(cin, l);
	k += l;
	return k;
}
int cinumer(int def) {//protective CIN funciton. Will return def if the integer is invalid.
	cout << "";
	string yodel;
	cin >> yodel;
	int SUM = 0;
	if (yodel.length() > 10) {//if it would surpass the integer limit
		cout << "Error, failed to imput. Please try again." << endl;
		return def;
	}
	if (yodel.length() == 10 && yodel[0] >= '2') {//if it would surpass the integer limit
		cout << "Error, failed to imput. Please try again." << endl;
		return def;
	}
	for (int i = 0; i < yodel.length(); i++) {//if this character is not a number
		if (yodel[i] < '0' || yodel[i] > '9') {
			cout << "Error, failed to imput. Please try again." << endl;
			return def;
		}
		else {
			SUM += (yodel[i] - 48) * pow(10, (yodel.length() - i - 1));//compiles all of the numbers into one actual integer
		}
	}
	return SUM;

}

//a developer use function.
int interpret() {//this function is only meant for setup. It will generate a line of code to be copy-pasted into the setup process. This is purely for my convenience
	cout << "Entering Debug mode." << endl;//Debug mode protections
	if (password()) {
		textblock(4);
		return 0;
	}
	std::cout << "Please enter the names of all the items you would like to display. End with a -1" << std::endl;
	std::string L;
	std::string K = "";
	int i = 0;
	while (std::cin >> L) {
		if (L != "-1") {

			K += (i == 0 ? "\"" : ", \"");//selectively input each name
			std::string lol;
			getline(std::cin, lol);
			L += lol;
			K += L;
			K += "\"";
			i++;
		}
		else {
			break;
		}
	}
	cout << "What would you like to call this? (no spaces)" << endl;
	cin >> L;
	std::cout << "vector <string> " << L << " = {" << K << "};" << endl;//the developer will copy-paste this into the default_list() function
	return 0;

}
string wait(int i) {//same as B(i)
	return B(i);
}
string B() {//same as B(1)
	A();
	return "";
}
string B(int k) {//will wait i seconds, then return "". The use of the string is so that this can be slotted into cout<< B(1) << "message" << endl;
	for (int i = 0; i < k; i++) {
		A();
	}
	return "";
}
void textblock(int k) {//Stores the lengthy blocks of text to reduce clutter in other areas of the code
	if (k == 0) {
		//Further Introduction to the program
		cout << B() << "This program will help you rank a long list of items based on your preferences" << endl;
		cout << B() << "It uses an \'elimination\' system" << endl;
		cout << B() << "Let's use an example: " << endl;
		cout << B() << "You're given the choice between \'iphone\' and \'android\'" << endl;
		cout << B() << "If you choose Android, Iphone becomes eliminated." << endl;
		cout << B() << "Then, the program will keep giving you more choices." << endl;
		cout << B() << "Eventually, android will be left as the only item on the list" << endl;
		cout << B() << "At this point, the program will move android to the list of winners, ";
		cout << B() << "and all the items eliminated by android will be moved back to the choosing list." << endl;
		cout << B() << "By doing this action repeatedly, eventually the choosing and eliminated list will both be empty." << endl;
		cout << B() << "Once that happens, you have a full list, COMPLETELY ranked!" << endl;
		cout << B() << endl;cout << B() << "You have three options for lists: " << endl;
		cout << B() << "Using a default list will allow you to choose from one of my lists that I've already set up" << endl;
		cout << B() << "If you want to make your own list, you will have to simply type out the names of all the things you want to rank" << endl;
		cout << B() << "Importing a list is the best way to \'save your progress.\'";
		cout << B() << "At any time, while you are choosing, use the export function (it'll be under special options)";
		cout << B() << "\nCopy what the program gives you, then paste it in the import function in order to resume where you left off!" << endl;
		cout << endl;
		cout << B(3) << "I think that's everything! Happy choosing!\n\n" << endl;
		cout << B(2) << "To start, what list would you like to rank:\n1: Use one of the default lists\n2: Make your own list\n3: Import list\n";
	}
	if (k == 1) {
		//display all of the valid choices to the user
		cout << "Special options:\nz: undoes your previous action. It remembers actions from up to 5 choices ago.\np: Displays the list of winners, up for choosing, and eliminated." << endl;
		cout << "r: More Advanced version of undo. Will allow you to search for a specific item. if it is eliminated, you can rescue it. If it already won, you can push it back to the choosing list." << endl;
		cout << "w: Allows you to rearrange the winners list. Useful if you change your mind later.\nx: \'saves\' your choices. You'll be given a block of text to copy paste, which stores your save information.";
		cout << "\ni: Loads your choices that you saved when pressing \'x\'\nn: rename an item on the list";
		cout << "\nd: allows you to permanently eliminate an item, barring it from the entire rankings list. You will never see it again.";
		cout << "\na: Allows you to add a completetely new item to the standings\nc: Prematurely ends the choosing process\nm: Allows you to manually eliminate an item" << endl;
		cout << "e: Estimates how many choices are left until you finish choosing." << endl;
		cout << "If you enter something that does not match any of these, I will run the \"skip\" function, which just generates a new set of choices for you.\n" << endl;
		cout << "To perform any of these actions, simply type their associated character instead of 1, 2, or q, when presented with a choice\n\n";
	}
	if (k == 2) {
		cout << B() << "Welcome to the selective choice machine!" << endl;//Introduce the program to the user
		cout << B(2) << "You will be given a series of this or that questions in order to choose your favourite!" << endl;
		cout << B(2) << "Press 1 or 2 to choose which you like more" << endl;
		cout << B(2) << "You can also press q to view more advanced options" << endl;
		srand(time(0));//random seed
	}
	if (k == 3) {
		//program termination process
		cout << B(2) << "To end the program, type any number, then press enter" << endl;
		INPUT(k);
		k = 3;
		cout << B(3) << "Program Terminated" << endl;
		B();
	}
	if (k == 4) {
		//password denial
		cout << B() << "Processing..." << endl;
		cout << B() << "Please wait..." << endl;
		cout << B() << "...";cout << B() << "...";cout << B() << "...";
		cout << B() << "\nWomp womp. Incorrect passowrd." << endl;
		cout << B() << "Self Destruct Activated.";
		B(3);
	}
	if (k == 5) {
		//the default lists
		cout << B() << "Which of the default lists would you like to use?";
		cout << B() << "\n1: Gen IV Pokemon\n2: Gen 7-9 pokemon\n3: Slay the Princess Princesses\n4: Slay the Princess All Endings\n5: Slay the Princess Voices\n6: Ghost type Pokemon\n7: Assorted foods\n";
		cout << "8: Fire type Pokemon\n9: DRG missions\n10: Video Games\n11: All favorite Pokemon\n12: Writing Prompt Wednesday titles\n";
	}
	if (k == 6) {
		//a warning for very long lists
		A();
		cout << "NOTE: " << endl;
		cout << B(2) << "This list is too big for the build in \"save function\" to work properly" << endl;
		cout << B(2) << "If you would like to save your progress, you will have to delete a few items." << endl;
		cout << B(2) << "You can delete items by pressing 'd'" << endl;
		B(2);
	}
}

std::vector<std::string> default_lists(int k) {//this will return one of the default lists based on its associated value
	if (k == 12) {
		//Writing Prompt Wednesday
		vector<string> WPW = { "Wait, that's NOT supposed to happen!", "Two legs, how I've missed you!", "The feeling of Nostalgia", "Road trip!",
			"Another one of those crazy Human Hunters", "Decisions, decisions", "...are you even my partner anymore?", "Sensory overload",
			"Evolution Revolution.", "How do you do?", "What did you say?", "Save Scumming", "Wait, I know you!", "What do you mean, you're perfectly okay with that?" };
		return WPW;
	}
	if (k == 1) {
		//Gen 4 Pokemon
		vector <string> G4 = { "leafeon", "pachirisu", "purugly", "vespiquen", "lucario", "mismagius", "lopunny", "mega lopunny", "luxray",
		 "arceus", "gallade", "mega gallade", "froslass", "roserade", "dialga", "garchomp", "azelf", "sky shaymin", "land shaymin",
		 "shinx", "weavile", "rampardos", "lumineon", "buizel", "floatzel" };
		return G4;
	}
	if (k == 2) {
		//Gen 7,8,9 Pokemon
		vector < string> G789 = { "primarina", "iron valiant", "hisuian zoroark", "alolan ninetales", "midnight lycanroc", "hisuian goodra",
		"hisuian zorua", "hisuian lilligant", "walking wake", "brionne", "alolan vulpix", "galarian rapidash", "galarian ponyta",
		"sneasler", "obstagoon", "salazzle", "ceruledge", "hisuian samurott", "pheromosa", "espathra", "alolan marowak", "lurantis",
		"ribombee", "sensu oricorio", "origin dialga", "raboot", "hisuian sneasel", "hisuian typhlosion", "tinkatuff", "hatterene",
		"thievul", "chien pao", "alolan raichu", "meowscarada", "popplio", "midday lycanroc", "wooloo", "mimikyu" };
		return G789;
	}
	if (k == 3) {
		//Princesses
		vector < string> PS = { "Base Princess", "Stranger", "Witch", "Razor", "Full Razor", "Beast", "Spectre", "Nightmare", "Prisoner",
		"Damsel", "Adversary", "Tower", "Drowned Grey", "Burned Grey", "Happily Ever After", "Cage", "Den", "Thorn", "Wild", "Dragon",
		"Wraith", "Moment of Clarity", "Fury", "Apotheosis", "Eye of the Needle", "The Shifting Mound" };
		return PS;
	}
	if (k == 11) {
		//All favorite Pokemon
		vector <string> J = { "primarina", "leafeon", "mawile", "iron valiant", "suicune", "ninetales", "hisuian zoroark", "pachirisu", "alolan ninetales", "meloetta",
			"lilligant", "midnight lycanroc", "espeon", "mega absol", "rapidash", "hisuian goodra", "hisuian zorua", "floette", "purugly", "hisuian lilligant",
			"walking wake", "brionne", "mismagius", "absol", "skitty", "kirlia", "alolan vulpix", "vespiquen", "goodra", "galarian rapidash", "audino", "galarian ponyta",
			"ponyta", "braixen", "aggron", "lopunny", "sneasler", "gardevoir", "sylveon", "lucario", "mega lopunny", "arceus", "diancie", "obstagoon", "salazzle",
			"mega ampharos", "ceruledge", "hisuian samurott", "pheromosa", "espathra", "flaafy", "spring deerling", "autumn deerling", "winter deerling",
			"debutante furfrou", "mienshao", "autumn sawsbuck", "cinccino", "alolan marowak", "virizion", "lurantis", "ribombee", "azelf", "weavile", "sensu oricorio",
			"froslass", "origin dialga", "mewtwo", "rampardos", "aurorus", "raboot", "mega beedrill", "misdreavus", "florges", "mega gallade", "hisuian sneasel",
			"hisuian typhlosion", "garchomp", "land shaymin", "tinkatuff", "serperior", "meowstic", "dialga", "hatterene", "furfrou", "sky shaymin", "houndoom",
			"delphox", "zorua", "thievul", "zoroark", "dratini", "luxray", "chien pao", "alolan raichu", "furret", "rhydon", "milotic", "floatzel", "cyndaquil",
			"moltres", "meowscarada", "dewott", "popplio", "pichu", "servine", "vulpix", "jirachi", "chimeco", "mareep", "vivillon", "wooloo", "spheal",
			"sliggoo", "buizel", "mimikyu", "espurr" };
		return J;
	}
	if (k == 9) {
		//DRG missions
		vector <string> dwrf = { "Mining","On Site Refining","Deep Scan","Elimination","Industrial Sabotage","Egg Hunt","Escort","Point Extraction","Salvage" };
		return dwrf;
	}
	if (k == 6) {
		//ghost type pokemon
		vector < string> boo = { "hisuian zoroark", "hisuian zorua", "mismagius", "ceruledge", "alolan marowak", "sensu oricorio", "misdraevus" };
		return boo;
	}
	if (k == 7) {
		//assorted foods
		vector <string> yum = { "lasagna", "cake", "ice cream", "baked ziti", "egg burrito", "filet mignion", "mac and cheese", "hawaiian rolls", "toasted bread", "PB&J", "frosted flakes" };
		return yum;
	}
	if (k == 8) {
		//fire type pokemon
		vector <string> fire = { "braixen", "ceruledge", "cyndaquil", "flareon", "quilava", "delphox", "rapidash", "cinderace", "raboot", "typhlosion",
			"chandelure", "ponyta", "ninetales", "moltres", "salazzle", "oricorio", "monferno", "vulpix", "charizard", "houndoom", "reshiram" };
		//vector <string> fire = {"Delphox", "Delphox", "Delphox", "Delphox", "Delphox", "Delphox", "Delphox", "Delphox", "Delphox", "Braixen" };
		return fire;
	}
	if (k == 10) {
		//Video Games
		vector <string> $GME = { "Forza 4", "Forza 5", "Elder Scrolls V", "Elder Scrolls IV", "Minecraft", "Terraria", "Stardew Valley", "Deep Rock Galactic", "TABS",
			"Minecraft Dungeons", "Mario Kart: Wii", "Super Mario Brothers", "Portal 2", "Team Fortress 2", "Half-life 2", "Halo CE", "Halo 2", "Halo 3", "Halo 4",
			"Halo Infinite", "Halo Reach", "Halo ODST", "DRG: Survivor", "Warcraft III: Frozen Throne", "Pokemon GO", "Bloons TD 6", "FPS Chess", "Lego Star Wars: The Complete Saga",
			"Slime Rancher", "Goat Simulator", "Portal 1", "Geometry Dash", "Youtube Shorts", "Ultrakill" };
		return $GME;
	}
	if (k == 4) {
		//STP endings
		vector <string> SPE = { "Bow down before the Tower", "Fight forever with the Adversary", "Free the Spectre", "Free the Nightmare", "Fall down the stairs with the Witch",
			"Get locked downstairs wiht the Witch", "From her stomach, free the Den", "Free the Damsel", "Deconstruct the Damsel", "Stranger", "By waiting forever, free the Prisoner",
			"With a clever trick, free the Prisoner's head", "With hunted, outmanuever and slay the Eye of the Needle", "Fight the Eye of the Needle Head-on", "Free the Eye of the Needle",
			"Crushed at the door by the Eye of the Needle", "Survive through her suffering, and slay the Fury", "Survive through her suffering, and leave the Fury alone", "Free the Fury",
			"Slay the Tower, then Slay the Fury", "You didn't hear no bell; Slay the Fury", "Master yourself, and slay the Razor in the end", "Master yourself, and let the Razor slay herself",
			"Abandon the gentle Dragon in the basement", "Merge with the Dragon", "Seperate from the Dragon, and leave together", "Use your will to throw the Wraith into the pit",
			"Free the Wraith", "Free the Moment of Clarity", "Free the Thorn", "Attempt to leave the Thorn in the basement", "Attempt to slay the Thorn", "Slay the wounded wild",
			"Free the Wounded Wild", "Break your cage with the Networked Wild", "Starve together with the Den", "Free the Den", "With stubborn, retain your humanity and slay the Den",
			"With skeptic, lure her out and slay the Den", "Ignore the voices in your head, and die by the Den", "Embrace instinct, and become one with the Den",
			"After luring her out, flinch, and be killed by the Den", "Slay the Happily Ever After", "Stay forever with the Happily Ever After", "Free the Happily Ever After",
			"Slay the Damsel: Burned Grey", "Slay the Prisoner: Drowned Grey", "With Paranoid, solve the riddle and Slay the Cage", "Lose your head and see the truth with the Cage",
			"Break the system and free the cage", "Tempt her with freedom, then drop the cage", "The good ending" };
		return SPE;
	}
	if (k == 5) {
		//STP voices
		vector <string> Vcs = { "Hero", "Hunted", "Opportunist", "Skeptic", "Smitten", "Contrarian", "Cheated", "Cold", "Paranoid", "Stubborn", "Broken" };
		return Vcs;
	}



}
