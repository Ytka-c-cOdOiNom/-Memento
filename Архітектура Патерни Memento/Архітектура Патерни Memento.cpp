#include <iostream>
#include <vector>
#include <windows.h>
using namespace std;

// Клас Memento для зберігання стану
class Memento {
private:
    int health;
    int experience;

public:
    Memento(int health, int experience) : health(health), experience(experience) {}

    int getHealth() const { return health; }
    int getExperience() const { return experience; }
};

// Клас Originator для збереження і відновлення стану
class Originator {
private:
    int health;
    int experience;

public:
    Originator(int health, int experience) : health(health), experience(experience) {}

    void setHealth(int health) { this->health = health; }
    void setExperience(int experience) { this->experience = experience; }

    int getHealth() const { return health; }
    int getExperience() const { return experience; }

    // Створює знімок поточного стану
    Memento* createMemento() {
        return new Memento(health, experience);
    }

    // Відновлює стан з знімка
    void restoreFromMemento(Memento* memento) {
        health = memento->getHealth();
        experience = memento->getExperience();
    }
};

// Клас Caretaker для збереження знімків
class Caretaker {
private:
    vector<Memento*> mementoList;

public:
    // Додає знімок до списку
    void addMemento(Memento* memento) {
        mementoList.push_back(memento);
    }

    // Отримує знімок за індексом
    Memento* getMemento(int index) {
        return mementoList.at(index);
    }

    ~Caretaker() {
        for (auto memento : mementoList) {
            delete memento;
        }
    }
};


int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Створення об'єкта Originator
    Originator* player = new Originator(100, 1);

    // Створення Caretaker
    Caretaker* caretaker = new Caretaker();

    // Збереження стану гравця
    caretaker->addMemento(player->createMemento());
    cout << "Початковий стан гравця: Здоров'я = " << player->getHealth() << ", Досвід = " << player->getExperience() << endl;

    // Зміни стану гравця
    player->setHealth(80);
    player->setExperience(2);
    cout << "Новий стан гравця: Здоров'я = " << player->getHealth() << ", Досвід = " << player->getExperience() << endl;

    // Відновлення стану з знімка
    player->restoreFromMemento(caretaker->getMemento(0));
    cout << "Відновлений стан гравця: Здоров'я = " << player->getHealth() << ", Досвід = " << player->getExperience() << endl;


    delete player;
    delete caretaker;

}

