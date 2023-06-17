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

    QList<int> get_cord(int index);
    QList<QList<int>> get_list_index(QList<int> cord);

    Q_INVOKABLE void upListCases(int index, int txt);
    Q_INVOKABLE void upListColors(int index, bool focus);
    Q_INVOKABLE void check(bool b);
    Q_INVOKABLE void initGrid_file_txt(int inputFileNumber);
    Q_INVOKABLE void save();
    void check_saved_file();

    Q_PROPERTY(QList<QString> cases MEMBER listCases NOTIFY caseChanged)
    Q_PROPERTY(bool show_save_btn MEMBER show_save NOTIFY caseChanged)
    Q_PROPERTY(QList<bool> type MEMBER listTypeCases NOTIFY caseChanged)
    Q_PROPERTY(QList<QString> colors MEMBER listColors NOTIFY caseChanged)
    Q_PROPERTY(int level MEMBER l NOTIFY caseChanged)

signals:
    void caseChanged();

private:
    QList<QString> listCases;
    QList<bool> listTypeCases;
    QList<QString> listColors;
    int l;
    bool show_save;
};

#endif // GRID_H
