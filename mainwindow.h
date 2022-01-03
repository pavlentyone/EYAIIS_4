#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <regex>
#include <string>
#include <iterator>
#include <list>
#include <algorithm>
#include <QTextCodec>

using namespace std;

class StemmerPorter{
private:
 static const string EMPTY;
 static const string S1;
 static const string S13;
 static const string SN;
 static const string const1;
 static const regex PERFECTIVEGROUND;
 static const regex REFLEXIVE;
 static const regex ADJECTIVE;
 static const regex PARTICIPLE;
 static const regex VERB;
 static const regex NOUN;
 static const regex I;
 static const regex P;
 static const regex NN;
 static const regex DERIVATIONAL;
 static const regex DER;
 static const regex SUPERLATIVE;

public:
 StemmerPorter();
 string get(string s);
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    StemmerPorter sp;
};

#endif // MAINWINDOW_H
