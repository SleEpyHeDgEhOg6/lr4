#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>

using namespace std;

class Book {
public:
    string author;
    string title;
    string publish;
    int year;
    int pages;
 
    Book(string a, string t, string p, int y, int pg)// конструктор
        : author(a), title(t), publish(p), year(y), pages(pg) {
    }

    bool operator<(const Book& other) const {//сравниваем два объекта(возвращает true если первый объект должен стоять перед объектом 2)
        return title < other.title;
    }

    void print(ostream& out) const {//выводит книги 
        out << author << ", " << title << ", " << publish
            << ", " << year << " год, " << pages << " стр.";
    }
};

ostream& operator<<(ostream& out, const Book& book) {//перегрузка(ostream& out - ссылка на выходной поток)
    book.print(out);
    return out;
}

int main() {
    ifstream in("input.txt");//исходный файл
    ofstream out("output.txt");//для результата 

    vector<Book> books;
    string author, title, publish;
    int year, pages;

    while (getline(in, author) && getline(in, title) &&//считываем файл
        getline(in, publish) && in >> year >> pages) {
        in.ignore(); //пропускаем символ перевода строки
        books.push_back(Book(author, title, publish, year, pages));
    }

    out << "Исходный список книг:\n";//выводим список книг без сортировки 
    for (const auto& book : books) {
        out << book << "\n";
    }

    sort(books.begin(), books.end());//сортируем 

    out << "\nСписок после сортировки по названию:\n";
    for (const auto& book : books) {
        out << book << "\n";
    }

    deque<Book> bookdeq;//создаем пустой 
    copy(books.begin(), books.end(), back_inserter(bookdeq));

    
    out << "\nСкопированный список в deque:\n";
    for (const auto& book : bookdeq) {
        out << book << "\n";
    }

    in.close();
    out.close();
    return 0;
}
