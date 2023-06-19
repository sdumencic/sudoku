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
    //    listCells.clear();
    listCellTypes.clear();
    listColors.clear();
    //    listSolutionCells.clear();
    listColors.resize(81, "white");

    for (int coord_x = 0; coord_x < 9; coord_x++) {
        for (int coord_y = 0; coord_y < 9; coord_y++) {
            int index = coord_x * 9 + coord_y;
            listCells[index] = QString::number(this->array[coord_x][coord_y]);
        }
    }

    listSolutionCells = listCells;

    int numOfBlanks;

    switch (m_level) {
    case 1:
        numOfBlanks = 10;
        break;
    case 2:
        numOfBlanks = 15;
        break;
    case 3:
        numOfBlanks = 20;
        break;
    }

    for (int i = 0; i < numOfBlanks; ++i) {
        int randomIndex = std::rand() % listCells.size();
        listCells[randomIndex] = "";
    }

    for (int i = 0; i < listCells.size(); ++i) {
        if (listCells[i] != "") {
            listCellTypes.push_back(true);
        } else {
            listCellTypes.push_back(false);
        }
    }

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

////////////////////////////////////

const int numbers1to9[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

bool grid::uniqueCheck(int coord_x, int coord_y, int number)
{
    //checks, if there are any contradictions with sudoku logic
    for (int inner_y = 0; inner_y < 9; inner_y++) //string checker
        if (this->array[coord_x][inner_y] == number)
            return false;
    //if number already exists in string returns false;

    for (int inner_x = 0; inner_x < 9; inner_x++) //string checker
        if (this->array[inner_x][coord_y] == number)
            return false;
    //if number already exists in column returns false;

    {                                                     //square checker
        int sq_coord_x = coord_x - coord_x % 3;           //parse 0 or 3 or 6 from input coord X
        int sq_coord_y = coord_y - coord_y % 3;           //parse 0 or 3 or 6 from input coord Y
        for (int inner_x = 0; inner_x < 3; inner_x++)     //three times right from sq_coord_x
            for (int inner_y = 0; inner_y < 3; inner_y++) //three times down from sq_coord_y
                if (number != 0)                          //why we need to check 0?
                    if (this->array[sq_coord_x + inner_x][sq_coord_y + inner_y] == number)
                        return false;
    }
    return true;
}
bool grid::generateSquare3x3(int sq_coord_x, int sq_coord_y)
{
    for (int inner_x = 0; inner_x < 3; inner_x++) //inner square coordinates
        for (int inner_y = 0; inner_y < 3;) {
            int coord_x = sq_coord_x + inner_x;
            int coord_y = sq_coord_y + inner_y;

            if (this->generationFailureCheck(coord_x, coord_y))
                return false; //generation failed

            int temp_rand = rand() % 9 + 1;
            if (this->uniqueCheck(coord_x, coord_y, temp_rand)) {
                this->array[coord_x][coord_y] = temp_rand;
                inner_y++;
            }
        }
    return true; //generation successful
}
bool grid::generator()
{
    //this function generates field by squares
    for (int coord_x = 0; coord_x < 9; coord_x++)
        for (int coord_y = 0; coord_y < 9; coord_y++)
            this->array[coord_x][coord_y] = 0; // inits field with zeros

    //outer coords for 3*3 squares, inner coords for numbers inside, 3*3 too
    for (int outer_x = 0; outer_x < 3; outer_x++)
        for (int outer_y = 0; outer_y < 3; outer_y++)
            if (!this->generateSquare3x3(outer_x * 3, outer_y * 3))
                //if statement starts generate3x3 function, and if it returns false generator stops
                return false;
    return true;
}

bool grid::generationFailureCheck(int coord_x, int coord_y)
{
    //returns true, if there is no numbers we can place in that coords
    bool failure = false;
    for (int i = 0; i < 9; i++) {
        failure = failure | this->uniqueCheck(coord_x, coord_y, numbers1to9[i]);
        //if there is no number in 1..9 that we can place, failure variable doesn't change and function returns !failure -> true
        if (failure)
            break; //if we found at least 1 number in 1..9, stop loop and return false
    }
    return !failure;
}
