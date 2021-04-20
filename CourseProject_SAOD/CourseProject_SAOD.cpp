#include "List.h"
#include "AVL.h"
#include "HashTable.h"


using namespace std;

struct Passanger {

	string passport_number;	// size = 12
	string place_date;		// size = 128
	string full_name;		// size = 64

	Passanger() : passport_number(""), place_date(""), full_name("") {};

	Passanger(string pass_num, string place_date, string full_name) : 
		passport_number(pass_num), place_date(place_date), full_name(full_name) {};

	Passanger(string pass_num) :
		passport_number(pass_num), place_date(""), full_name("") {};

	bool operator >  (Passanger a)
	{
		return this->passport_number > a.passport_number ? true : false;
	}

	bool operator <  (Passanger a)
	{
		return this->passport_number < a.passport_number ? true : false;
	}

	bool operator == (Passanger a)
	{
		return this->passport_number == a.passport_number ? true : false;
	}

	friend std::ostream& operator << (std::ostream& out, Passanger& a)
	{
		return out << "passport_number: " << a.passport_number << endl <<
			"place_date: " << a.place_date << endl << 
			"full_name: " << a.full_name << endl;
	}
};

struct Flight {

	string flight_number;	// size = 8
	string airline_name;	// size = 64
	string a_from;			// size = 64
	string a_to;			// size = 64
	string date;			// size = 11
	string time;			// size = 6
    unsigned int all_seats;
    unsigned int free_seats;

	Flight() : flight_number(""), airline_name(""), a_from(""), a_to(""), 
		date(""), time(""), all_seats(0), free_seats(0) {};

	Flight(string f_num, string a_name, string a_from, string a_to, string date,
		string time, unsigned int all_seats, unsigned int free_seats) 
	{
		this->flight_number = f_num;
		this->airline_name = a_name;
		this->a_from = a_from;
		this->a_to = a_to;
		this->date = date;
		this->time = time;
		this->all_seats = all_seats;
		this->free_seats = free_seats;
	}

	Flight(string f_num)
	{
		this->flight_number = f_num;
		this->airline_name = "";
		this->a_from = "";
		this->a_to = "";
		this->date = "";
		this->time = "";
		this->all_seats = 0;
		this->free_seats = 0;
	}

	bool operator >  (Flight a)
	{
		return this->flight_number > a.flight_number ? true : false;
	}

	bool operator <  (Flight a)
	{
		return this->flight_number < a.flight_number ? true : false;
	}

	bool operator == (Flight a)
	{
		return this->flight_number == a.flight_number ? true : false;
	}

	friend std::ostream& operator << (std::ostream& out, Flight& a)
	{
		return out << "flight_num: " << a.flight_number << endl <<
			"airline_name: " << a.airline_name << endl << endl << endl;
	}
};

struct Ticket {

	string passport_number; // size = 11
	string flight_number;	// size = 7
	string ticket_number;	// size = 9

	Ticket() : passport_number(""), flight_number(""), ticket_number("") {};

	Ticket(string pas_num, string fly_num, string tick_num) : passport_number(pas_num),
		flight_number(fly_num), ticket_number(tick_num) {};

	Ticket(string tick_num) : passport_number(""),
		flight_number(""), ticket_number(tick_num) {};

	bool operator >  (Ticket a)
	{
		return this->ticket_number > a.ticket_number ? true : false;
	}

	bool operator <  (Ticket a)
	{
		return this->ticket_number < a.ticket_number ? true : false;
	}

	bool operator == (Ticket a)
	{
		return this->ticket_number == a.ticket_number ? true : false;
	}

	friend std::ostream& operator << (std::ostream& out, Ticket& a)
	{
		return out << "pass: " << a.passport_number << endl <<
			"flight_num: " << a.flight_number << endl <<
			"ticket_num: " << a.ticket_number << endl;
	}
};

int main()
{
	/*List<int> root;

	int mas[5] = { 2,3,6,1,7 };

	for (int i = 0; i < 5; i++)
	{
		root.push_back(mas[i]);
	}
	
	cout << "Size = " << root.size() << endl;

	for (int i = 0; i < 5; i++)
	{
		cout << root[i] << "\t";
	}

	cout << endl << endl << "contains(5) = " << root.contains(5);
	cout << endl << endl << "contains(2) = " << root.contains(2);*/

	/*HashTable<std::string, Flight> Table;

	Flight f = Flight("RUS-359");
	Flight a = Flight("GER-329");
	Flight v = Flight("FIN-319");

	Table.add(f.flight_number, f);
	Table.add(a.flight_number, a);
	Table.add(v.flight_number, v);

	std::cout << Table["RUS-359"] << std::endl
		<< Table["GER-329"] << std::endl
		<< Table["FIN-319"] << std::endl;

	std::cout << Table.contains("FIN-319") << std::endl
		<< Table.contains("FIN-329") << std::endl;*/

	/*AVL<Flight> root;
	
	root.add(Flight("111"));
	root.add(Flight("222"));
	root.add(Flight("333"));
	root.add(Flight("444"));
	root.add(Flight("555"));
	root.add(Flight("666"));

	root.postOrder();

	cout << endl << endl << endl;
	root.remove(Flight("444"));

	root.postOrder();*/
}