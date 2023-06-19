#include "grid.h"
#include <QDebug>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Boja za oznacenu celiju - tirkizna
const QString COLOR_SELECTED = "#80CBC4";

// Boja za isti redak, stupac i sub-kvadrat u kojem se nalazi oznacena celija - svijetlo tirkizna
const QString COLOR_SELECTED_RCS = "#C7E2E7";

// Boja za neispravno ispunjene celije - svijetlo crvena
const QString COLOR_FALSE = "#EF9A9A";

// Boja za oznacavanje gotove igre - svijetlo zelena
const QString COLOR_CORRECT = "#C5E1A5";

// Boja za tamnu temu
const QString COLOR_DARK = "#3C3C3C";

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
    // Tip celije - false - obicna celija, true - predefinirana celija, ne moze se mijenjati
    listCellTypes.fill(false, 81);

    // Sadrzaj svake celije
    listCells.fill(QString(), 81);

    // Lista boja
    listColors.fill("white", 81);

    // Lista celija rijesene mreze
    listSolutionCells.fill(QString(), 81);
}

// Citanje txt filea
void grid::initGrid_file_txt(int i)
{
    m_level = i;

    // Postavljanje cistog pocetnog stanja
    listCells.clear();
    listCellTypes.clear();
    listColors.clear();
    listSolutionCells.clear();
    listColors.resize(81, "white");

    // Postavljanje datoteke za citanje iz direktorija mreze
    string inputFileName = "./mreze/" + to_string(i) + ".txt";
    ifstream inputFile(inputFileName);

    if (!inputFile.is_open()) {
        cerr << "Error while loading file " << inputFileName << "\n";
        __throw_invalid_argument("File not found.");
    }

    string line;
    int lineCount = 0;

    // Citanje svakog reda iz txt
    while (getline(inputFile, line)) {
        lineCount++;

        istringstream ss(line);
        string cell;

        // Odvajanje prema celijama iz txt datoteke na temelju '|'
        // . - prazno polje
        // Broj - predefinirano polje
        // - - u spremljenim datotekama oznacava da nije predefinirani broj
        while (getline(ss, cell, '|')) {
            try {
                if (cell == ".") {
                    listCells.push_back(QString());
                    listCellTypes.push_back(false);
                } else if (cell.substr(0, 1) == "-") {
                    listCells.push_back(QString::fromStdString(cell.substr(1, 2)));
                    listCellTypes.push_back(false);
                } else {
                    listCells.push_back(QString::fromStdString(cell));
                    listCellTypes.push_back(true);
                }
            } catch (const std::invalid_argument &e) {
                cout << "NaN found in file " << inputFileName << " line " << lineCount << endl;
            }
        }
    }

    inputFile.close();

    // Ucitavanje mreze za rjesenje
    string inputSolutionFileName = "./mreze/" + to_string(i) + "rjesenje.txt";
    ifstream inputSolutionFile(inputSolutionFileName);

    if (!inputSolutionFile.is_open()) {
        cerr << "Error while loading file " << inputSolutionFileName << "\n";
        __throw_invalid_argument("File not found.");
    }

    lineCount = 0;

    // Citanje svakog reda iz txt
    while (getline(inputSolutionFile, line)) {
        lineCount++;

        istringstream ss(line);
        string cell;

        while (getline(ss, cell, '|')) {
            try {
                listSolutionCells.push_back(QString::fromStdString(cell));
            } catch (const std::invalid_argument &e) {
                cout << "NaN found in file " << inputSolutionFileName << " line " << lineCount
                     << endl;
            }
        }
    }

    inputSolutionFile.close();

    emit cellChanged();
}

// Spremanje igre
void grid::save()
{
    std::ofstream myfile;
    myfile.open("./mreze/saved.txt");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int index = j + 9 * i;
            if (listCells[index] != QString()) {
                if (listCellTypes[index] == false) {
                    myfile << "-" + (listCells[index].toStdString());
                } else {
                    myfile << listCells[index].toStdString();
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

    myfile.open("./mreze/savedrjesenje.txt");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int index = j + 9 * i;
            if (listSolutionCells[index] != QString()) {
                myfile << listSolutionCells[index].toStdString();
                myfile << "|";
            }
        }

        myfile << "\n";
    }

    myfile.close();
}

void grid::changeIsLight(bool isLight)
{
    qDebug() << isLight;
    for (int i = 0; i < listColors.size(); ++i) {
        if (!isLight && listColors[i] == "white") {
            listColors[i] = COLOR_DARK;
        } else if (isLight && listColors[i] == COLOR_DARK) {
            listColors[i] = "white";
        }
    }

    emit cellChanged();
}

// Rijesi jednu nasumicnu celiju
void grid::help()
{
    QString searchString = "";
    QList<int> indices;

    for (int i = 0; i < listCells.size(); ++i) {
        if (listCells[i] == searchString) {
            indices.append(i);
        }
    }

    if (!indices.isEmpty()) {
        int randomIndex = std::rand() % indices.size();
        int randomElement = indices[randomIndex];
        listCells[randomElement] = listSolutionCells[randomElement];
    }

    check(false);

    emit cellChanged();
}

// Koordinate
QList<int> grid::get_coordinates(int index)
{
    return {index % 9, index / 9};
}

// Indexi elemenata u istom sub-kvadratu
QList<QList<int>> grid::get_list_index(QList<int> coordinates)
{
    QList<int> neighbours_x;
    QList<int> neighbours_y;

    int x = coordinates[0];
    int y = coordinates[1];

    int x_start = x - (x % 3);
    int y_start = y - (y % 3);

    for (int i = 0; i < 3; i++) {
        neighbours_x.push_back(x_start + i);
        neighbours_y.push_back(y_start + i);
    }

    QList<QList<int>> neighbours;
    neighbours.push_back(neighbours_x);
    neighbours.push_back(neighbours_y);
    return neighbours;
}

// Updateanje vrijednosti na odredenom indexu s novim inputom
void grid::updateListCells(int index, int txt)
{
    updateListColors(index, true);
    listCells[index] = txt == 0 ? QString() : QString::number(txt);

    emit cellChanged();
}

// Updateanje boje
void grid::updateListColors(int index, bool focus)
{
    if (!focus) {
        return;
    }

    std::fill(listColors.begin(), listColors.end(), QString("white"));
    QList<int> coordinates = get_coordinates(index);

    QList<QList<int>> neighbours = get_list_index(coordinates);
    QList<int> neighbours_x = neighbours[0];
    QList<int> neighbours_y = neighbours[1];

    for (int i = 0; i < 3; i++) {
        int x = neighbours_x[i];
        int y_start = neighbours_y[0];

        const int ind1 = 9 * (y_start + 0) + x;
        const int ind2 = 9 * (y_start + 1) + x;
        const int ind3 = 9 * (y_start + 2) + x;

        listColors[ind1] = COLOR_SELECTED_RCS;
        listColors[ind2] = COLOR_SELECTED_RCS;
        listColors[ind3] = COLOR_SELECTED_RCS;
    }

    int x_start = coordinates[0];
    int y_start = coordinates[1];

    for (int i = 0; i < 9; i++) {
        const int ind1 = 9 * i + x_start;
        const int ind2 = 9 * y_start + i;

        listColors[ind1] = COLOR_SELECTED_RCS;
        listColors[ind2] = COLOR_SELECTED_RCS;
    }

    listColors[index] = COLOR_SELECTED;

    emit cellChanged();
}

// Provjera stanja
void grid::check(bool b)
{
    bool a = true;
    int index;
    for (index = 0; index < 81; index++) {
        QList<int> coordinates = get_coordinates(index);
        QList<QList<int>> neighbours = get_list_index(coordinates);
        QList<int> neighbours_x = neighbours[0];
        QList<int> neighbours_y = neighbours[1];

        for (int i = 0; i < 3; i++) {
            const int x = neighbours_x[i];
            for (int j = 0; j < 3; j++) {
                const int y = neighbours_y[j];
                const int ind = 9 * y + x;
                if (ind != index && listCells[ind] == listCells[index]) {
                    if (b) {
                        listColors[ind] = COLOR_FALSE;
                        listColors[index] = COLOR_FALSE;
                        a = false;
                    } else {
                        a = false;
                    }
                }
                if (listCells[ind].isEmpty()) {
                    if (b) {
                        listColors[ind] = COLOR_FALSE;
                        a = false;
                    } else {
                        a = false;
                    }
                }
            }
        }

        for (int k = 0; k < 9; k++) {
            const int ind = 9 * coordinates[1] + k;
            if (ind != index && listCells[ind] == listCells[index]) {
                if (b) {
                    listColors[ind] = COLOR_FALSE;
                    listColors[index] = COLOR_FALSE;
                    a = false;
                } else {
                    a = false;
                }
            }
            if (listCells[ind].isEmpty()) {
                if (b) {
                    listColors[ind] = COLOR_FALSE;
                    a = false;
                } else {
                    a = false;
                }
            }
        }

        for (int k = 0; k < 9; k++) {
            const int ind = 9 * k + coordinates[0];
            if (ind != index && listCells[ind] == listCells[index]) {
                if (b) {
                    listColors[ind] = COLOR_FALSE;
                    listColors[index] = COLOR_FALSE;
                    a = false;
                } else {
                    a = false;
                }
            }
            if (listCells[ind].isEmpty()) {
                if (b) {
                    listColors[ind] = COLOR_FALSE;
                    a = false;
                } else {
                    a = false;
                }
            }
        }
    }

    if (a) {
        std::fill(listColors.begin(), listColors.end(), COLOR_CORRECT);
    }

    emit cellChanged();
}

// Provjera ako postoji spremljena igra
void grid::check_saved_file()
{
    show_save = std::ifstream("./mreze/saved.txt").good();

    emit cellChanged();
}
