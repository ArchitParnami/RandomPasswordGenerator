#ifndef RPG_H
#define RPG_H

#include <QWidget>

namespace Ui {
class RPG;
}

class RPG : public QWidget
{
    Q_OBJECT
    
public:
    explicit RPG(QWidget *parent = 0);
    ~RPG();
    void setVariables();
    enum autoGen{autoGenLowerCaseCharacters,autoGenUpperCaseCharacters,
                autoGenNumbers,autoGenSpecialCharacters};
    bool checkRange();
private:
    Ui::RPG *ui;
    int passwordLength;
    int numOfUpperCaseLetters;
    int numOfLowerCaseLetters;
    int numOfDigits;
    int numOfSpecialCharacters;

public slots:
    void lowerCaseEnabler(bool val);
    void upperCaseEnabler(bool val);
    void digitEnabler(bool val);
    void specialCharacterEnabler(bool val);

    void generatePassword();

};

#endif // RPG_H
