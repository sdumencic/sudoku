#include "grid.h"
#include <fstream>
#include <iostream>
#include <qDebug>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

grid::grid(QObject *parent)
    : QObject(parent)
{
    // Provjera ako postoji spremljena igra
    check_saved_file();
    // Inicijalizacija mreze
    initGrid();
}

// Inicijalizacija
void grid::initGrid()
{
    //  Sadrzaj svake celije
    listCases.fill(QString(), 81);
    // Tip celije - false - obicna celija, true - predefinirana celija, ne moze se mijenjati
    listTypeCases.fill(false, 81);
    // Lista boja
    listColors.fill("#fff", 81);
}

// Citanje csv filea
void grid::initGrid_with_csv(int i)
{
    l = i;
    listCases.clear();
    listTypeCases.clear();
    listColors.clear();

    listColors.resize(81, "#fff");

    string inputFileName = "./mreze/" + to_string(i) + ".csv";
    ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        cerr << "Error while loading file " << inputFileName << "\n";
        __throw_invalid_argument("File not found.");
    }

    string line;
    int lineCount = 0;

    // Citanje svakog reda iz csv
    while (getline(inputFile, line)) {
        lineCount++;
        if (line[0] == '#')
            continue;

        istringstream ss(line);
        string cell;

        // Odvajanje prema celijama iz csv datoteke na temelju '|'
        // . - prazno polje
        // broj - predefinirano polje
        // - - u spremljenim datotekama oznacava da nije predefinirani broj
        while (getline(ss, cell, '|')) {
            try {
                if (cell == ".") {
                    listCases.push_back(QString());
                    listTypeCases.push_back(false);
                } else if (line.substr(0, 1) == "-") {
                    listCases.push_back(QString::fromStdString(line.substr(1, 2)));
                    listTypeCases.push_back(false);
                } else {
                    listCases.push_back(QString::fromStdString(cell));
                    listTypeCases.push_back(true);
                }
            } catch (const std::invalid_argument &e) {
                cout << "NaN found in file " << inputFileName << " line " << lineCount << endl;
                e.what();
            }
        }
    }

    inputFile.close();
    emit caseChanged();
}

// Updatenjae vrijednosti na odredenom indexu s novim inputom
void grid::upListCases(int index, int txt)
{
    upListColors(index, true);
    listCases[index] = txt == 0 ? QString() : QString::number(txt);

    emit caseChanged();
}

// Koordinate
QList<int> grid::get_cord(int index)
{
    return {index % 9, index / 9};
}

// Indexi elemenata u istom sub-kvadratu
QList<QList<int>> grid::get_list_index(QList<int> cord)
{
    QList<int> neighbors_x;
    QList<int> neighbors_y;

    int x = cord[0];
    int y = cord[1];

    int x_start = x - (x % 3);
    int y_start = y - (y % 3);

    for (int i = 0; i < 3; i++) {
        neighbors_x.push_back(x_start + i);
        neighbors_y.push_back(y_start + i);
    }

    QList<QList<int>> neighbors;
    neighbors.push_back(neighbors_x);
    neighbors.push_back(neighbors_y);
    return neighbors;
}

// Updateanje boje
void grid::upListColors(int index, bool focus)
{
    if (!focus) {
        return;
    }

    // Resetiranje boje
    std::fill(listColors.begin(), listColors.end(), QString("#fff"));
    QList<int> cord = get_cord(index);

    // Dohvacanje indexa celija u istom sub-kvadratu
    QList<QList<int>> neighbors = get_list_index(cord);
    QList<int> neighbors_x = neighbors[0];
    QList<int> neighbors_y = neighbors[1];

    // Oznacavanje istog sub-kvadrata, u kojem se nalazi celija na koju se kliknulo, sa sivom bojom
    for (int i = 0; i < 3; i++) {
        int x = neighbors_x[i];
        int y_start = neighbors_y[0];

        int ind1 = 9 * (y_start + 0) + x;
        int ind2 = 9 * (y_start + 1) + x;
        int ind3 = 9 * (y_start + 2) + x;

        listColors[ind1] = QString("#e2e7ed");
        listColors[ind2] = QString("#e2e7ed");
        listColors[ind3] = QString("#e2e7ed");
    }

    int x_start = cord[0];
    int y_start = cord[1];

    // Oznacavanje istog retka i stupca, u kojem je celija na koju se kliknulo, sa sivom bojom
    for (int i = 0; i < 9; i++) {
        int ind1 = 9 * i + x_start;
        int ind2 = 9 * y_start + i;

        listColors[ind1] = QString("#e2e7ed");
        listColors[ind2] = QString("#e2e7ed");
    }

    listColors[index] = QString("#d0d0d0");

    emit caseChanged();
}

// Provjera progressa
void grid::check(bool b)
{
    QList<int> neighbors_x;
    QList<int> neighbors_y;
    QList<QList<int>> neighbors;
    QList<int> cord;
    int x;
    int y;
    bool a = true;
    int index;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            index = i + j * 9;
            cord = get_cord(index);
            neighbors = get_list_index(cord);

            neighbors_x = neighbors[0];
            neighbors_y = neighbors[1];

            int ind;
            for (int k = 0; k < 3; k++) {
                x = neighbors_x[k];
                for (int l = 0; l < 3; l++) {
                    y = neighbors_y[l];
                    ind = 9 * y + x;
                    if (listCases[ind] == listCases[index]) {
                        if (index != ind) {
                            if (b) {
                                listColors[ind] = QString("#EF9A9A");
                                listColors[index] = QString("#EF9A9A");
                                a = false;
                            }
                            if (!b) {
                                a = false;
                            }
                        }
                        if (listCases[ind] == QString()) {
                            if (b) {
                                listColors[ind] = QString("#EF9A9A");
                                a = false;
                            }
                            if (!b) {
                                a = false;
                            }
                        }
                    }
                }
            }

            for (int k = 0; k < 9; k++) {
                ind = 9 * k + cord[0];
                if (index != ind) {
                    if (listCases[ind] == listCases[index]) {
                        if (b) {
                            listColors[ind] = QString("#EF9A9A");
                            listColors[index] = QString("#EF9A9A");
                            a = false;
                        }
                        if (!b) {
                            a = false;
                        }
                    }
                    if (listCases[ind] == QString()) {
                        if (b) {
                            listColors[ind] = QString("#EF9A9A");
                            a = false;
                        }
                        if (!b) {
                            a = false;
                        }
                    }
                }
            }

            for (int k = 0; k < 9; k++) {
                ind = 9 * cord[1] + k;
                if (index != ind) {
                    if (listCases[ind] == listCases[index]) {
                        for (int i = 0; i < 81; i++) {
                            if (b) {
                                listColors[index] = QString("#EF9A9A");
                                a = false;
                            }
                            if (!b) {
                                a = false;
                            }
                            if (listCases[ind] == QString()) {
                                if (b) {
                                    listColors[ind] = QString("#EF9A9A");
                                    a = false;
                                }
                                if (!b) {
                                    a = false;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (a) {
        for (int i = 0; i < 81; i++) {
            listColors[i] = QString("#C5E1A5");
        }
    }

    emit caseChanged();
}

// Provjera ako postoji spremljena igra
void grid::check_saved_file()
{
    show_save = std::ifstream("./mreze/5.csv").good();
}

// Spremanje igre
void grid::save()
{
    std::ofstream myfile;
    myfile.open("./mreze/5.csv");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int index = j + 9 * i;
            if (listCases[index] != QString()) {
                if (listTypeCases[index] == false) {
                    myfile << "-" + (listCases[index].toStdString());
                } else {
                    myfile << listCases[index].toStdString();
                }
                myfile << "|";
            } else {
                myfile << ".";
                myfile << "|";
            }
        }
        myfile << "\n";
    }

    myfile.close();
}
