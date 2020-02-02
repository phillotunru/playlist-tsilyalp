#include<bits/stdc++.h>
#include "Playlist.h"
using namespace std;

//Playlist::Node::Node* insert_next(Node* p){
//	Node *temp = _next;
//	_next = p;
//	p->_next = temp;
//	size++;
//	return;
//}
//Playlist::Node::Node* remove_next(){
//	_next = _next->_next;
//	size--;
//	return this;
//}
bool Playlist::Song_Entry::set_id(int id){
	if (id<0) return false;
	_id = id;
	return true;
}
bool Playlist::Song_Entry::set_name(string name){
	if (name=="") return false;
	_name = name;
	return true;
}
Playlist::Playlist(){
	Song_Entry H(-1, "HEAD");
	Node *Head = new Node(H);
	_head = Head;
	_tail = Head;
	_prev_to_current = Head;
	_size = 0;
	return;
}
 
Playlist::~Playlist(){
	_size= 0;
	//clear();
	delete _head;
}

Playlist *Playlist::insert_at_cursor(const Song_Entry& s){
	_size++;
	Node *P = new Node(s);
	_prev_to_current->insert_next(P);
	return this;
}

Playlist *Playlist::push_back(const Song_Entry& s){
//	_size++;
	Node* temp = _prev_to_current;
	_prev_to_current = _tail;
	insert_at_cursor(s);
	_tail = _prev_to_current->get_next();
	_prev_to_current = temp;
	return this;
}

Playlist *Playlist::push_front(const Song_Entry& s){
//	_size++;
	Node* temp = _prev_to_current;
	_prev_to_current = _head;
	insert_at_cursor(s);
	_prev_to_current = temp;
	return this;
}
Playlist *Playlist::advance_cursor(){
	
	if (_prev_to_current == _tail) return nullptr;
	_prev_to_current = _prev_to_current->get_next();
	return this;
}

Playlist *Playlist::circular_advance_cursor(){
	if (_prev_to_current->get_next() == _tail){
		_prev_to_current = _head;
	}else advance_cursor();
	return this;
}

Playlist::Song_Entry& Playlist::get_current_song()const{
	if(_prev_to_current->get_next()==nullptr) return this->_head->get_song();
	return (_prev_to_current->get_next()->get_song());
}

Playlist *Playlist::remove_at_cursor(){
	_size--;
	if (_prev_to_current == _tail) return nullptr;
	_prev_to_current->remove_next();
	return this;
}

Playlist *Playlist::rewind(){
	_prev_to_current = _head;
	return this;
}

Playlist *Playlist::clear(){
	Node *now = _head->get_next();
	while(now!=nullptr){
		Node *temp = now->get_next();
		delete now;
		now = temp;
	}
	_size= 0;
	_prev_to_current = _tail = _head;
//	_head->insert_next(nullptr);
	return this;
}

Playlist::Song_Entry& Playlist::find_by_id(int id) const{
	Node* now = _head->get_next();
	while(now!=nullptr){
		if (now->get_song().get_id() == id){
			return (now->get_song());
		}
		now = now->get_next();
	}
	return (this->_head->get_song());
}

Playlist::Song_Entry& Playlist::find_by_name(string name) const{
	Node* now = _head->get_next();
	while(now!=nullptr){
		if (now->get_song().get_name() == name){
			return (now->get_song());
		}
		now = now->get_next();
	}
	return (this->_head->get_song());
}
string Playlist::to_string() const{
	int n = min(25, _size);
	string s = "Playlist: " + std::to_string(_size) + " entries.\n";	
	if (n==0) return s;
	Node *now = _head->get_next();
	while(n-- && now!= nullptr){
		int id = now->get_song().get_id();
		string name = now->get_song().get_name();
		s += "{ id: " + std::to_string(id) + ", name: " + name + " }";
		if (now==_prev_to_current) s+= " [P]";
		if (now==_tail) s+= " [T]";
		s += "\n";
		now = now->get_next();
	}
	if (_size>25) s+= "...\n";
	return s;
}













//// Important implementation note: With the exception of toString() and find...()
//// all Playlist methods below should operate in a constant amount of time
//// regardless of the size of the Playlist instance.
////
//// The semantics of prevToCurrent is such that it always points to the
//// node *BEFORE* the current one. This makes the manipulations easy because
//// we can only look forward (and not back) in singly linked lists.
//static Playlist::SongEntry Sentinel_Song(-1, "Non-existent song. Don't mess with it_");
//class Playlist {
//public:
//// Inner public class ---------------------------------------------------
//// The client can refer to it by using the qualified name Playlist::SongEntry
//	class SongEntry {
//	// TODO - your code here
//	private:
//		int id;
//		string name;
//	public:
//		SongEntry(int theId = 0, string theName = "Unnamed")
//		: id(theId), name(theName) {}
//		int get_id() const { return id; }
//		string get_name() const { return name; }
//		bool set_id(int id);
//		bool set_name(string theName);
//		bool operator==(const SongEntry& that) {
//		return this->id == that.id && this->name == that.name;
//		}
//		bool operator!=(const SongEntry& that) {
//		return !(*this == that);
//		}
//		friend std::ostream& operator<<(ostream& os, const SongEntry& s) {
//		return os << "{ id: "<< s.get_id() << ", name: " << s.get_name() << ")";
//		}
//		friend class Tests; // Don't remove this line
//	};
//// Inner private class ---------------------------------------------------
//private:
//// This is going to be our inner private class. The client doesn't need to
//// know.
//	class Node {
//	// TODO - your code here
//	private:
//		SongEntry song;
//		Node *next;
//		public:
//		Node(const SongEntry& theSong = SongEntry()) : song(theSong), next(nullptr) {}
//		~Node(); // Do not do recursive free
//		SongEntry& get_song() { return song; }
//		Node *get_next() { return next; }
//		Node *insert_next(Node *p);
//		Node *remove_next();
//		friend class Tests; // Don't remove this line
//	};
//// Playlist class -------------------------------------------------------
//private:
//// Ok, these the client definitely doesn't need to have access to
//	Node *head, *tail, *prevToCurr;
//	int size;
//	public:
//	Playlist(){
//		SongEntry H(0, "Header");
//		Node *Head = new Node(H);
//		head = sent;
//		tail = sent;
//		prevToCurr = sent;
//		size = 0;
//	}
//	~Playlist(){
//		clear();
//		delete head;
//	}
//	int get_size() const { return size; }
//	SongEntry& get_current_song(){
//		if (get_size()==0) return Sentinel_Song;
//	}
//	// The following return "this" on success, null on failure. See the spec
//	// for why.
//	Playlist *clear(){
//		Node *Head;
//		*Head = *head;
//		tail = Head;
//		prevToCurr = Head;
//		delete head;
//		return;
//	}
//	Playlist *rewind(){
//		prevToCurr = head;
//	}
//	Playlist *push_back(const SongEntry& s);
//	Playlist *push_front(const SongEntry& s);
//	Playlist *insert_at_curr(const SongEntry& s);
//	Playlist *remove_at_curr();
//	Playlist *advance_curr_to_next();
//	Playlist *circular_advance_curr_to_next();
//	// The following return the target node on success, null on failure
//	SongEntry& find_by_id(int id) const;
//	SongEntry& find_by_song_name(string songName) const;
//	string toString() const;
//	friend class Tests; // Don't remove this line
//};
