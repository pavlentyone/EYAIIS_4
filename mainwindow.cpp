#include "mainwindow.h"
#include "ui_mainwindow.h"

const string StemmerPorter::const1 = "АЕИОУЫЭИЮЯ";
const string StemmerPorter::EMPTY = "";
const string StemmerPorter::S1 = "$1";
const string StemmerPorter::S13 = "$1$3";
const string StemmerPorter::SN = "Н";
const regex StemmerPorter::PERFECTIVEGROUND = regex("(ИВ|ИВШИ|ИВШИСЬ|ЫВ|ЫВШИ|ЫВШИСЬ|ВШИ|ВШИСЬ)$");
const regex StemmerPorter::REFLEXIVE = regex("(СЯ|СЬ)$");
const regex StemmerPorter::ADJECTIVE = regex("(ЕЕ|ИЕ|ЫЕ|ОЕ|ИМИ|ЫМИ|ЕЙ|ИЙ|ЫЙ|ОЙ|ЕМ|ИМ|ЫМ|ОМ|ЕГО|ОГО|ЕМУ|ОМУ|ИХ|ЫХ|УЮ|ЮЮ|АЯ|ЯЯ|ОЮ|ЕЮ)$");
const regex StemmerPorter::PARTICIPLE = regex("(.*)(ИВШ|ЫВШ|УЮЩ)$|([АЯ])(ЕМ|НН|ВШ|ЮЩ|Щ)$");
const regex StemmerPorter::VERB = regex("(.*)(ИЛА|ЫЛА|ЕНА|ЕЙТЕ|УЙТЕ|ИТЕ|ИЛИ|ЫЛИ|ЕЙ|УЙ|ИЛ|ЫЛ|ИМ|ЫМ|ЕН|ИЛО|ЫЛО|ЕНО|ЯТ|УЕТ|УЮТ|ИТ|ЫТ|ЕНЫ|ИТЬ|ЫТЬ|ИШЬ|УЮ|Ю)$|([АЯ])(ЛА|НА|ЕТЕ|ЙТЕ|ЛИ|Й|Л|ЕМ|Н|ЛО|НО|ЕТ|ЮТ|НЫ|ТЬ|ЕШЬ|ННО)$");
const regex StemmerPorter::NOUN = regex("(А|ЕВ|ОВ|ИЕ|ЬЕ|Е|ИЯМИ|ЯМИ|АМИ|ЕИ|ИИ|И|ИЕЙ|ЕЙ|ОЙ|ИЙ|Й|ИЯМ|ЯМ|ИЕМ|ЕМ|АМ|ОМ|О|У|АХ|ИЯХ|ЯХ|Ы|Ь|ИЮ|ЬЮ|Ю|ИЯ|ЬЯ|Я)$");
const regex StemmerPorter::I = regex("И$");
const regex StemmerPorter::P = regex("Ь$");
const regex StemmerPorter::NN = regex("НН$");
const regex StemmerPorter::DERIVATIONAL = regex(".*[^АЕИОУЫЭЮЯ]+[АЕИОУЫЭЮЯ].*ОСТЬ?$");
const regex StemmerPorter::DER = regex("ОСТЬ?$");
const regex StemmerPorter::SUPERLATIVE = regex("(ЕЙШЕ|ЕЙШ)$");

StemmerPorter::StemmerPorter(){
// setlocale(0,"");
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("CP1251"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("CP1251"));
    //QTextCodec::setCodecForTr(QTextCodec::codecForName("CP1251"));
}
string StemmerPorter::get(string s){
 transform(s.begin(), s.end(), s.begin(), ::toupper);
 replace( s.begin(), s.end(), 'Ё', 'Е');
 size_t pos = s.find_first_of(const1, 0);
 if(pos != string::npos){
  string pre = s.substr(0,pos+1);
  string rv = s.substr(pos+1);
  string temp = regex_replace(rv, PERFECTIVEGROUND, EMPTY);
  if(rv.size()!=temp.size()){
   rv=temp;
  }
  else{
   rv = regex_replace(rv, REFLEXIVE, EMPTY);
            temp = regex_replace(rv, ADJECTIVE, EMPTY);
   if(rv.size()!=temp.size()){
    rv = temp;
    rv = regex_replace(rv, PARTICIPLE, S13);
   }
   else{
    temp = regex_replace(rv, VERB, S13);
    if(rv.size()!=temp.size()){
     rv=temp;
    }
    else{
     rv=regex_replace(temp, NOUN, EMPTY);
    }
   }
  }
  rv=regex_replace(rv, I, EMPTY);
  if(regex_match(rv, DERIVATIONAL)){
   rv = regex_replace(rv, DER, EMPTY);
  }
  temp = regex_replace(rv, P, EMPTY);
  if(temp.length()!=rv.length()){
   rv=temp;
  }
  else{
   rv=regex_replace(rv, SUPERLATIVE, EMPTY);
   rv=regex_replace(rv, NN, SN);
  }
  s=pre+rv;
 }
 transform(s.begin(), s.end(), s.begin(), ::tolower);
 return s;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->label->setText(QString::fromStdString(sp.get(ui->lineEdit->text().toStdString())));
}
