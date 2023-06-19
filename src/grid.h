#ifndef GRID_H
#define GRID_H
#include <QObject>
#include <string>

using namespace std;

class grid : public QObject
{
    Q_OBJECT

public:
    explicit grid(QObject *parent = nullptr);

    void initGrid();

    QList<int> get_coordinates(int index);
    QList<QList<int>> get_list_index(QList<int> coordinates);    

    Q_PROPERTY(QList<QString> cells MEMBER listCells NOTIFY cellChanged)
    Q_PROPERTY(int level MEMBER m_level NOTIFY cellChanged)
    Q_PROPERTY(bool show_save_game MEMBER show_save NOTIFY cellChanged)
    Q_PROPERTY(QList<bool> type MEMBER listCellTypes NOTIFY cellChanged)
    Q_PROPERTY(QList<QString> colors MEMBER listColors NOTIFY cellChanged)

    Q_INVOKABLE void initGrid_file_txt(int inputFileNumber);
    Q_INVOKABLE void save();
    Q_INVOKABLE void updateListCells(int index, int txt);
    Q_INVOKABLE void updateListColors(int index, bool focus);
    Q_INVOKABLE void check(bool b);
    Q_INVOKABLE void help();
    Q_INVOKABLE void check_saved_file();
    Q_INVOKABLE void changeIsLight(bool isLight);
    void check_elements(int index);

signals:
    void cellChanged();

private:
    QList<bool> listCellTypes;
    QList<QString> listCells;
    QList<QString> listColors;
    QList<QString> listSolutionCells;
    int m_level;
    bool show_save;
};

#endif // GRID_H
