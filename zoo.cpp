#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <limits>

namespace Zoo {
	class Animal {
	protected:
		std::string name;
		int age;
		std::string food;
		int id;
	public:
		Animal(const std::string& n, int a, const std::string& f,int i): name(n), age(a), food(f), id(i){}
		
		virtual int getID() const { return id; }
		virtual void makeSound() const = 0;
		virtual void displayInfo() const = 0;
		virtual void feed() const = 0;

		virtual ~Animal() = default;
	};

	class Mammal :public Animal {
	public:
		Mammal(const std::string& n, int a, const std::string& f,int i): Animal(n,a,f,i){}
		void makeSound() const override {
			std::cout << name << " says: Woof or Meow (Mammal sound)\n";
		}
		void displayInfo() const override {
			std::cout << "Mammal: " << name << ", Age: " << age << "\n";
		}
		void feed() const override {
			std::cout <<name << " eats " << food << "\n";
		}
	};

	class Bird :public Animal {
	public:
		Bird(const std::string& n, int a, const std::string& f, int i) : Animal(n, a, f, i) {}
		void makeSound() const override {
			std::cout << name << " says: Tweet (Bird sound)\n";
		}
		void displayInfo() const override {
			std::cout << "Bird: " << name << ", Age: " << age << "\n";
		}
		void feed() const override {
			std::cout << name << " eats " << food << "\n";
		}
	};

	class Reptile : public Animal {
	public:
		Reptile(const std::string& n, int a, const std::string& f, int i) : Animal(n, a, f, i) {}
		void makeSound() const override {
			std::cout << name << " says: Ssshh (Reptile sound)\n";
		}
		void displayInfo() const override {
			std::cout << "Reptile: " << name << ", Age: " << age << "\n";
		}
		void feed() const override {
			std::cout << name << " eats " << food << "\n";
		}
	};

	class ZooManager {
		std::vector < std::shared_ptr<Animal>> animals;
	public:
		void addAnimal(std::shared_ptr<Animal> animal) {
			animals.push_back(animal);
		}

		void showAllAnimals() const {
			std::cout << "\nZoo Animals:\n";
			for (const auto& a : animals) {
				a->displayInfo();
				a->makeSound();
				a->feed();
				a->getID();
				std::cout << "------------------\n";
			}
		}

		void sortAnimalsByID() {
			std::sort(animals.begin(), animals.end(),
				[](const std::shared_ptr<Animal>& a, const std::shared_ptr<Animal>& b) {
					return a->getID() < b->getID();
				});
		}
	};
}


int main() {
	using namespace Zoo;

	ZooManager manager;
	int choice;

	while (true) {
		std::cout << "\n--- Zoo Manager Menu ---\n";
		std::cout << "1. Add Animal\n";
		std::cout << "2.Show All Animals\n";
		std::cout << "3.Show All sorted Animals\n";
		std::cout << "4.Exit\n";
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input. Please enter a number.\n";
			continue;
		}


		if (choice == 1) {
			std::string type, name, food;
			int age, id;

			std::cout << "Enter animal type (mammal, bird, reptile): ";
			std::cin >> type;

			std::cout << "Enter name: ";
			std::cin >> name;

			std::cout << "Enter age: ";
			std::cin >> age;

			std::cout << "Enter food: ";
			std::cin >> food;

			std::cout << "Enter ID: ";
			std::cin >> id;

			if (type == "mammal") {
				manager.addAnimal(std::make_shared<Mammal>(name, age, food, id));
			}
			else if (type == "bird") {
				manager.addAnimal(std::make_shared<Bird>(name, age, food, id));
			}
			else if (type == "reptile") {
				manager.addAnimal(std::make_shared<Reptile>(name, age, food, id));
			}
			else {
				std::cout << "Invalid type. Please enter these followings: 'Mammal', 'Bird' or 'Reptile'.\n";
			}
		}
		else if (choice == 2) {
			manager.showAllAnimals();
		}
		else if (choice == 3) {
			manager.sortAnimalsByID();
			std::cout << "Animals sorted by ID.\n";
		}
		else if (choice == 4) {
			std::cout << "Exiting Zoo Manager.\n";
			break;
		}
		else {
			std::cout << "Invalid choice. Please try again.\n";
		}
	}
	
	return 0;
}