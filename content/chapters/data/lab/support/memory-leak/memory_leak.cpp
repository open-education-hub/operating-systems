#include <iostream>

class Student {
	public:
		Student(std::string name, unsigned int age, std::string favorite_os);
		void Print() const;

	private:
		std::string name_;
		unsigned int age_;
		std::string favorite_os_;
};

Student::Student(std::string name, unsigned int age, std::string favorite_os)
	: name_(name), age_(age), favorite_os_(favorite_os)
{
}

void Student::Print() const
{
	std::cout << name_ << " is " << age_ << " years old";
	std::cout << " and likes " << favorite_os_ << std::endl;
}

int main(void)
{
	Student *s;

	s = new Student("Andrei Popescu", 22, "Linux");
	s->Print();

	s = new Student("Ioana David", 23, "macOS");
	s->Print();

	delete s;

	return 0;
}
