#include <iostream>
#include <iomanip> //��������������� ����� �����
#define NUMBER_PEOPLE 5
#include <fstream>
#include <string>
#include <sstream> //��� ��������� ����� �� ������ ����: 20.03.2025 (��������� �����)



struct DATE {
	int day;
	int month;
	int year;
};

struct Observation {

	DATE date;
	double weight;

};

class scales { //����

private:

	struct Person {


		std::string name;
		Observation* observation;
		int number_observation;
		int INC;

		Person() : number_observation(0), INC(5) {
			observation = new Observation[INC];
		}

		~Person() {
			delete[]observation;
			observation = nullptr;
		}

		// ��������� ����� ����������
		void observ_2(Observation& obs) {

			if (number_observation >= INC) {
				INC *= 2;

				Observation* new_observation = new Observation[INC];
				for (int i = 0; i < number_observation; i++) {
					new_observation[i] = observation[i];

				}
				delete[]observation;
				observation = new_observation;
			}
			observation[number_observation] = obs;
			++number_observation;
		}

	};


	DATE starting_date;
	Person family[NUMBER_PEOPLE];
	int count_people;

	//�������� �� ���������� ����
	int check_date(const DATE& d, const std::string& name) const {
		for (int i = 0; i < NUMBER_PEOPLE; i++) {
			if (family[i].name == name) {
				for (int j = 0; j < family[i].number_observation; j++) {
					if (family[i].observation[j].date.day == d.day
						&& family[i].observation[j].date.month == d.month
						&& family[i].observation[j].date.year == d.year) {
						return j; //������ ���� ��� ����
					}
				}
			}
		}
		return -1; //������ ���� ��� �� ����
	}

	//�������� �� ������������� ������
	int check_month(const std::string name, int month, int year) const {
		int index_man = check_man(name);
		if (index_man == -1) {
			std::cout << "The person is not on the list" << std::endl;
			return -1;
		}

		for (int i = 0; i < family[index_man].number_observation; i++) {
			if (family[index_man].observation[i].date.year == year && family[index_man].observation[i].date.month == month) {
				return 1;
			}
		}
		return -1; //���� �� ������ ����� � ��� ���������� ���


	}

	int check_man(const std::string name) const {

		for (int i = 0; i < NUMBER_PEOPLE; i++) {
			if (family[i].name == name) {
				return i;
			}
		}


		return -1;
	}

	//�������� �� ������������ ���� (������������ ��������� ����)
	int date_correct_start(DATE& date) {
		if (date.year < starting_date.year) {
			std::cout << "Error. Incorrect year relative to the start date" << std::endl; //������������ ��� ������������ ��������� ����
			return -7;
		}
		else if (date.year == starting_date.year && date.month < starting_date.month) {
			std::cout << "Error. Incorrect month relative to the start date" << std::endl; //�����
			return -7;
		}
		else if (date.year == starting_date.year && date.month == starting_date.month && date.day < starting_date.day) {
			std::cout << "Error. Incorrect day relative to the start date" << std::endl; // ����
			return -7;
		}
	}

	//�������� �� ���������� ���� � �������
	int date_correct_number_day(DATE& date) {

		if (date.day < 1) {
			std::cout << "Error. Incorrect date (day)" << std::endl; //������������ ���� (����)
			return -1;
		}

		switch (date.month) {
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
		{
			if (date.day > 31) {
				std::cout << "Error. In a given month, the maximum number of days is 31" << std::endl;
				return -1;
			}
			break;
		}

		case 4:
		case 6:
		case 9:
		case 11:
		{
			if (date.day > 30) {
				std::cout << "Error. In a given month, the maximum number of days is 30" << std::endl;
				return -1;
			}
			break;
		}

		case 2:
		{
			if (date.day > 28) {
				std::cout << "Error. In a given month, the maximum number of days is 28 (leap year is not considered in the program)" << std::endl;
				return -1;
			}
			break;
		}

		default:
			std::cout << "Incorrect month" << std::endl;
			return -1;

		}
	}

	//����� ��������� ����
	void new_starting_date(int new_day, int new_month, int new_year) {


		if (new_year < starting_date.year ||
			(new_year == starting_date.year && new_month < starting_date.month) ||
			(new_year == starting_date.year && new_month == starting_date.month && new_day < starting_date.day)) {

			return;
		}

		bool n1 = new_year == starting_date.year;
		bool n2 = new_month == starting_date.month;
		bool n3 = new_day == starting_date.day;

		if (n1 && n2 && n3) {
			return;
		}


		//starting_date = { new_day, new_month, new_year };

		for (int i = 0; i < count_people; i++) {
			int j = 0;
			while (j < family[i].number_observation) {
				bool is_earlier = false;

				if (family[i].observation[j].date.year < new_year) {
					is_earlier = true;
				}
				else if (family[i].observation[j].date.year == new_year && family[i].observation[j].date.month < new_month) {
					is_earlier = true;
				}
				else if (family[i].observation[j].date.year == new_year && family[i].observation[j].date.month == new_month && family[i].observation[j].date.day < new_day) {
					is_earlier = true;
				}


				if (is_earlier) {
					for (int m = j; m < family[i].number_observation - 1; m++) {
						family[i].observation[m] = family[i].observation[m + 1];
					}
					family[i].number_observation--;

				}
				else {
					j++;
				}
			}
		}

	}

public:

	scales(int c_p = 0, int day = 0, int month = 0, int year = 0) : count_people(c_p) {

		starting_date = { day, month, year }; //0 0 0 - ���� ��� �� �����������


	}

	//����������� ����������� ��� scales
	scales(const scales& fam) {
		starting_date.day = fam.starting_date.day;
		starting_date.month = fam.starting_date.month;
		starting_date.year = fam.starting_date.year;

		count_people = fam.count_people;
		for (int i = 0; i < count_people; i++) {
			family[i].name = fam.family[i].name;
			family[i].INC = fam.family[i].INC;
			family[i].number_observation = fam.family[i].number_observation;

			delete[]family[i].observation;
			family[i].observation = new Observation[family[i].INC];
			for (int j = 0; j < family[i].number_observation; j++) {
				family[i].observation[j] = fam.family[i].observation[j];
			}
		}
	}

	//��������������� ��������� ������������
	scales& operator = (const scales& fam) {
		if (this != &fam) {
			starting_date.day = fam.starting_date.day;
			starting_date.month = fam.starting_date.month;
			starting_date.year = fam.starting_date.year;

			count_people = fam.count_people;
			for (int i = 0; i < count_people; i++) {
				family[i].name = fam.family[i].name;
				family[i].INC = fam.family[i].INC;
				family[i].number_observation = fam.family[i].number_observation;

				delete[]family[i].observation;
				family[i].observation = new Observation[family[i].INC];
				for (int j = 0; j < family[i].number_observation; j++) {
					family[i].observation[j] = fam.family[i].observation[j];
				}
			}
		}

		return *this;
	}


	//�������� �������� � �����
	void add_to_family(const std::string name1) {

		if (count_people >= NUMBER_PEOPLE) {
			std::cout << "The number of people in the family is already 5!" << std::endl;
			return;
		}

		int index_man = check_man(name1);
		if (index_man != -1) {
			std::cout << "The person has already been added to the family" << std::endl;
			return;
		}

		for (int i = 0; i < NUMBER_PEOPLE; i++) {
			if (family[i].name == "") {
				family[i].name = name1;
				++count_people;
				std::cout << name1 << " has been added to the family." << std::endl;
				return;
			}
		}

	}

	//���������� ��������� ���� ����������
	void set_starting_date(int d, int m, int y) {

		if (d <= 0 || m <= 0 || y <= 0) {
			std::cout << "Incorrect starting date" << std::endl;
			return;
		}

		new_starting_date(d, m, y);

		starting_date = { d, m, y };
	}

	//������ ��������� ���� ����������
	void print_start_date() {

		if (starting_date.day == 0 && starting_date.month == 0 && starting_date.year == 0) {
			std::cout << "The initial date of the observations has not been set. Please set a starting date" << std::endl;
			return;
		}

		std::cout << "The initial date of observations: ";

		std::cout << std::setw(2) << std::setfill('0') << starting_date.day << "."
			<< std::setw(2) << std::setfill('0') << starting_date.month << "."
			<< std::setw(4) << std::setfill('0') << starting_date.year << std::endl;

	}

	//���������� ����������
	void set_the_observation(std::string name1, DATE& date1, double weight1) {
		int index = check_man(name1);

		if (weight1 < 0 || weight1>700.0) {
			std::cout << "Incorrect weight" << std::endl;
			return;
		}

		if (date1.day <= 0 || date1.month <= 0 || date1.year <= 0) {
			std::cout << "Incorrect date" << std::endl;
			return;
		}

		if (index == -1) {
			std::cout << "The person is not on the list" << std::endl; //�������� ��� � ������ 
			return;
		}

		//��������� �� ������������ ������������ ��������� ����
		int proverka_start = date_correct_start(date1);
		if (proverka_start == -7) {
			return;
		}

		//�������� �� ������������ ����� ���� � ������
		int proverka_number_day = date_correct_number_day(date1);
		if (proverka_number_day == -1) {
			return;
		}


		Observation new_obs = { date1, weight1 };
		int index_observation = check_date(date1, name1);
		if (index_observation == -1) {
			family[index].observ_2(new_obs); //���� �� ���� ����������
		}
		else {
			family[index].observation[index_observation].weight = weight1;
		}
	}

	//������ ��� � ��������� ����������
	void print_weight(const std::string name, const DATE& date) const {
		int index_observ = check_date(date, name);
		if (index_observ == -1) {
			std::cout << "Date not found" << std::endl;
			return;
		}

		int index_man = check_man(name);
		if (index_man == -1) {
			std::cout << "The person is not on the list" << std::endl; //�������� ��� � ������
			return;
		}

		std::cout << name << "'s" << " weight:" << std::fixed << std::setprecision(3) << family[index_man].observation[index_observ].weight << std::endl;
		//std::fixed<<std::setprecision(3) - ���������� ��������, ��� ����� ����� �������
	}

	//����� ������� ��� � ��������� ������
	void print_average_weight_month(const std::string name, int month, int year) const {

		int proverka_month_year = check_month(name, month, year); //���� �� ���������� � ������ ������ ������������� ����
		if (proverka_month_year == -1) {
			std::cout << "Date not found" << std::endl;
			return;
		}

		double sum_mass = 0;
		int count_obs = 0;
		int index_man = check_man(name);
		if (index_man == -1) {
			std::cout << "The person is not on the list" << std::endl; //�������� ��� � ������
			return;
		}
		for (int i = 0; i < family[index_man].number_observation; i++) {
			if (family[index_man].observation[i].date.month == month && family[index_man].observation[i].date.year) {
				sum_mass += family[index_man].observation[i].weight;
				count_obs++;
			}
		}
		double res = sum_mass / count_obs;
		std::cout << name << "'s average weight for the given month (" << month << "), year (" << year << "): " << res << std::endl;
	}

	//����� ������� ��� �� ��� ������� ����������
	void print_average_weight_history(const std::string name) const {
		double sum_mass = 0;
		int count_obs = 0;
		int index_man = check_man(name);
		if (index_man == -1) {
			std::cout << "The person is not on the list" << std::endl; //�������� ��� � ������
			return;
		}
		for (int i = 0; i < family[index_man].number_observation; i++) {
			sum_mass += family[index_man].observation[i].weight;
			count_obs++;
		}

		if (sum_mass == 0) {
			std::cout << "There are no observations (" << name << "). Please set up observation" << std::endl;
			return;
		}

		double res2 = sum_mass / count_obs;
		std::cout << name << "'s average weight over the entire history of observations: " << res2 << std::endl;
	}

	//����� ����������� ��� ����� ����� � ��������� ������
	void print_min_weight(const std::string name, int month, int year) const {

		int proverka_month_year = check_month(name, month, year);
		if (proverka_month_year == -1) {
			std::cout << "Date not found" << std::endl;
			return;
		}

		int index_man = check_man(name);
		if (index_man == -1) {
			std::cout << "The person is not on the list" << std::endl;
			return;
		}
		double min_weight = 1000000.0;

		int data_min_weight = 0;

		for (int i = 0; i < family[index_man].number_observation; i++) {
			if (family[index_man].observation[i].date.month == month && family[index_man].observation[i].date.year == year) {
				if (family[index_man].observation[i].weight < min_weight) {
					min_weight = family[index_man].observation[i].weight;
					data_min_weight = family[index_man].observation[i].date.day;

				}
			}

		}

		std::cout << "The minimum weight of " << name << " for the given month(" << month << "), year(" << year << "): " << min_weight << std::endl;
		std::cout << "The day on which " << name << "'s minimum weight was registered: " << data_min_weight << std::endl;
	}

	//����� ����������� ��� �� ��� ������� ����������
	void print_min_weight_history(const std::string name) const {

		int index_man = check_man(name);

		if (index_man == -1) {
			std::cout << "The person is not on the list" << std::endl;
			return;
		}


		int day_min_weight = 0;
		int month_min_weight = 0;
		int year_min_weight = 0;

		double min_weight = 1000000.0;
		for (int i = 0; i < family[index_man].number_observation; i++) {
			if (family[index_man].observation[i].weight < min_weight) {
				min_weight = family[index_man].observation[i].weight;

				day_min_weight = family[index_man].observation[i].date.day;
				month_min_weight = family[index_man].observation[i].date.month;
				year_min_weight = family[index_man].observation[i].date.year;
			}
		}

		if (min_weight == 1000000.0) {
			std::cout << "There are no observations (" << name << "). Please set up observation" << std::endl;
			return;
		}

		std::cout << "The minimum weight of " << name << " in the entire history of observations: " << min_weight << std::endl;

		std::cout << "The date on which " << name << "'s minimum weight was registered: " << std::setw(2) << std::setfill('0') << day_min_weight << "."
			<< std::setw(2) << std::setfill('0') << month_min_weight << "." << std::setw(4) << std::setfill('0') << year_min_weight << std::endl;
	}


	//����� ������������ ��� �� ������������ �����
	void print_max_weight(const std::string name, int month, int year) const {


		int proverka_month_year = check_month(name, month, year);
		if (proverka_month_year == -1) {
			std::cout << "Date not found" << std::endl;
			return;
		}

		int index_man = check_man(name);
		if (index_man == -1) {
			std::cout << "The person is not on the list" << std::endl;
			return;
		}

		int day_max_weight = 0;
		double max_weight = -1000000.0;

		for (int i = 0; i < family[index_man].number_observation; i++) {
			if (family[index_man].observation[i].date.month == month && family[index_man].observation[i].date.year == year) {
				if (max_weight < family[index_man].observation[i].weight) {
					max_weight = family[index_man].observation[i].weight;
					day_max_weight = family[index_man].observation[i].date.day;

				}
			}

		}

		std::cout << "The maximum weight of " << name << " for the given month(" << month << "), year(" << year << "): " << max_weight << std::endl;
		std::cout << "The day on which " << name << "'s maximum weight was registered: " << day_max_weight << std::endl;
	}

	//����� ������������ ��� ��� �������
	void print_max_weight_history(const std::string name) const {

		int index_man = check_man(name);
		if (index_man == -1) {
			std::cout << "The person is not on the list" << std::endl;
			return;
		}

		double max_weight = -100000.0;

		int day_max_weight = 0;
		int month_max_weight = 0;
		int year_max_weight = 0;

		for (int i = 0; i < family[index_man].number_observation; i++) {
			if (max_weight < family[index_man].observation[i].weight) {
				max_weight = family[index_man].observation[i].weight;
				day_max_weight = family[index_man].observation[i].date.day;
				month_max_weight = family[index_man].observation[i].date.month;
				year_max_weight = family[index_man].observation[i].date.year;
			}
		}

		if (max_weight == -100000.0) {
			std::cout << "There are no observations (" << name << "). Please set up observation" << std::endl;
			return;
		}


		std::cout << "The maximum weight of " << name << " in the entire history of observations: " << max_weight << std::endl;

		std::cout << "The date on which " << name << "'s maximum weight was registered: " << std::setw(2) << std::setfill('0') << day_max_weight << "."
			<< std::setw(2) << std::setfill('0') << month_max_weight << "." << std::setw(4) << std::setfill('0') << year_max_weight << std::endl;

	}

	//��������� ���������� � ����
	void save_fail(const std::string& file) {
		std::ofstream fout(file);
		if (fout.is_open()) {
			fout << "The initial date of observations: " << std::setw(2) << std::setfill('0') << starting_date.day << "."
				<< std::setw(2) << std::setfill('0') << starting_date.month << "."
				<< std::setw(2) << std::setfill('0') << starting_date.year << std::endl;


			for (int i = 0; i < count_people; i++) {
				fout << '\n';
				fout << family[i].name << ": " << std::endl;
				for (int j = 0; j < family[i].number_observation; j++) {

					fout << std::setw(2) << std::setfill('0') << family[i].observation[j].date.day << "."

						<< std::setw(2) << std::setfill('0') << family[i].observation[j].date.month << "."

						<< std::setw(4) << std::setfill('0') << family[i].observation[j].date.year

						<< "\tWeight " << family[i].observation[j].weight << std::endl;
				}
			}
		}
		else {
			std::cout << "Error. The file could not be opened" << std::endl;
		}
		fout.close();

	}


	//������� ����� ��� ���������� (�� ���� � �������, ������ ��� �������� � main)
	void print_observ() {
		std::cout << "The initial date of observations: " << std::setw(2) << std::setfill('0') << starting_date.day << "."
			<< std::setw(2) << std::setfill('0') << starting_date.month << "."
			<< std::setw(2) << std::setfill('0') << starting_date.year << std::endl;


		for (int i = 0; i < count_people; i++) {
			std::cout << '\n';
			std::cout << family[i].name << ": " << std::endl;
			for (int j = 0; j < family[i].number_observation; j++) {

				std::cout << std::setw(2) << std::setfill('0') << family[i].observation[j].date.day << "."

					<< std::setw(2) << std::setfill('0') << family[i].observation[j].date.month << "."

					<< std::setw(4) << std::setfill('0') << family[i].observation[j].date.year

					<< "\tWeight " << family[i].observation[j].weight << std::endl;
			}
		}
	}

	//������� ���������� �� �����
	void fail_uotput(const std::string& fail) {
		std::ifstream fin(fail);
		if (fin.is_open()) {
			std::string line;

			getline(fin, line);
			//std::cout << line << std::endl;
			int len = line.size();

			std::string date;


			for (char i : line) {
				if (i >= '0' && i <= '9' || i == '.') {
					date += i;
				}
			}


			std::stringstream ss(date); //������� ��������� �����, ������� � ���� ������ � ����� 

			int d, m, y;

			char razdelitel;
			ss >> d >> razdelitel >> m >> razdelitel >> y;

			starting_date = { d,m,y }; //������� ������ � ��������� ����

			fin.ignore(); //���������� ������ \n

			std::string str_1;
			while (getline(fin, str_1)) {

				if (str_1.empty()) {
					continue; //������ ������ ����������
				}

				std::string name;
				std::stringstream ss_name(str_1); //�������� � ��������� ����� str_1 
				getline(ss_name, name, ':'); //�� ���������� ������ � name �� : 

				int index = check_man(name);
				if (index == -1) {
					add_to_family(name); //�������� �������� � �����
					index = check_man(name);
				}

				while (getline(fin, str_1) && !str_1.empty()) {//������ ������ ���������� ����� ������ ������ ��������

					std::stringstream ss_obs(str_1);
					char razdelitel;
					int day, month, year;
					std::string we; //��� ����� Weight
					double weight;

					ss_obs >> day >> razdelitel >> month >> razdelitel >> year >> razdelitel;
					ss_obs >> we;
					ss_obs >> weight;

					DATE date = { day, month, year };

					int proverka_start = date_correct_start(date);

					if (proverka_start == -7) {
						continue; // ���� ���� �����������, ���������� ��� ����������
					}

					int proverka_number_day = date_correct_number_day(date);
					if (proverka_number_day == -1) {
						continue; // ���� ���������� ���� �����������, ���������� ��� ����������
					}

					Observation obs = { date, weight };
					int index_observation = check_date(date, name); // ���������, ���������� �� ��� ���������� �� ��� ���� 
					if (index_observation == -1) {
						family[index].observ_2(obs); // ���� ���, ��������� ����� ���������� 
					}
					else {
						family[index].observation[index_observation] = obs; // ���� ����, �������� ������ �� ����� 
					}

				}
			}

		}
		else {
			std::cout << "Error. The file could not be opened" << std::endl;
		}
		fin.close();
	}

	//������� ����� (� ������� �� ����)
	void clear_file(const std::string& filename) {
		std::ofstream file(filename, std::ios::trunc);
		if (file.is_open()) {
			file.close();
		}
		else {
			std::cout << "Error. The file could not be opened" << std::endl;
		}
	}


};

int main() {

	scales proverka;
	//proverka.clear_file("Proverka.txt"); //������� �����


	proverka.add_to_family("Vlad");
	proverka.add_to_family("Vlad");  //��� ���� � ������
	proverka.add_to_family("Alice");

	proverka.print_max_weight_history("Alice"); //�������� �� ������������ ��� (���������� ���)
	proverka.print_average_weight_history("Vlad");

	//��������� ����
	proverka.print_start_date(); //��������� ���� �� ���� �����������

	proverka.set_starting_date(20, 3, 2025);
	proverka.print_start_date();

	DATE d0 = { -1, 3, 2025 };
	proverka.set_the_observation("Vlad", d0, 60.0); //������������ ����

	DATE d1 = { 24,3,2025 };
	proverka.set_the_observation("Vlad", d1, 61.5);
	DATE d2 = { 25,3,2025 };
	proverka.set_the_observation("Vlad", d2, 61.42);

	proverka.print_weight("Vlad", d1);
	proverka.print_weight("Vlad", d2);

	proverka.set_the_observation("Alice", d1, 50.243);
	proverka.print_weight("Alice", d1);

	//������� ��� �� ��������� �����
	proverka.print_average_weight_month("Vlad", 3, 2025); // (61.500 + 61.420) : 2 = 61.460
	DATE d3 = { 26, 4, 2025 };

	//������� ��� �� ��� ������� ����������
	proverka.set_the_observation("Vlad", d3, 67.77);
	proverka.print_weight("Vlad", d3);
	proverka.print_average_weight_history("Vlad"); // (61.500 + 61.420 + 61.770) : 3 = 63.563

	//����������� ��� � ��������� ������
	DATE d4 = { 21, 4, 2025 };
	proverka.set_the_observation("Vlad", d4, 61.3);
	proverka.print_min_weight("Vlad", 4, 2026); //���� �� �������
	std::cout << '\n';
	proverka.print_min_weight("Vlad", 3, 2025);
	std::cout << '\n';

	//����������� ��� �� ��� ������� ����������
	proverka.print_min_weight_history("Vlad");
	std::cout << '\n';
	//������������ ��� � ��������� ������
	proverka.print_max_weight("Vlad", 3, 2025);
	std::cout << '\n';
	//������������ ��� �� ��� ������� ����������
	proverka.print_max_weight_history("Vlad");
	std::cout << '\n';


	proverka.add_to_family("Egor");
	proverka.add_to_family("Remi");
	proverka.add_to_family("Natasha");
	proverka.add_to_family("Alina"); //6 �������. ������� ������

	std::cout << '\n';
	//�������� ������������ ����������� � ��������� =
	std::cout << "Constructor Copy" << std::endl;
	scales proverka2(proverka);
	proverka2.print_max_weight("Vlad", 3, 2025);

	std::cout << '\n';
	scales proverka3;
	proverka3 = proverka;
	proverka3.print_start_date();
	proverka3.print_weight("Alice", d1);
	proverka3.print_average_weight_month("Alice", 3, 2025);

	proverka.print_observ();

	//�������� �� ��������� ��������� ���� ()
	proverka.set_starting_date(26, 3, 2025);
	proverka.print_observ();


	proverka.save_fail("Proverka.txt");  


	//�������� �� ���������� �� �����
	scales proverka4;
	proverka4.fail_uotput("Proverka.txt");

	proverka4.print_observ();
	proverka4.print_start_date(); 


	return 0;
}